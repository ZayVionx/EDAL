#include "key_edal.h"
#include "sys.h"
#include "beep.h"

#define BSP_KEY_DEFAULT_EVENTS       (EDAL_KEY_EVENT_CLICKED      | \
                                      EDAL_KEY_EVENT_DOUBLE_CLICK | \
                                      EDAL_KEY_EVENT_LONG_PRESS)

/* 只有 SysTick 内的五个设备回调写入队列，前台读取时短暂屏蔽中断。 */
static bsp_key_event_t s_tEventQueue[BSP_KEY_EVENT_QUEUE_SIZE];
static volatile uint8_t s_chHead;
static volatile uint8_t s_chTail;
static volatile uint8_t s_chCount;
static volatile uint32_t s_wOverflowCount;
static volatile bool s_bInitialized;
static uint32_t s_wEventMasks[TS10_KEY_COUNT];

static const bsp_key_value_t s_tKeyValues[TS10_KEY_COUNT] = {
    BSP_KEY_VALUE_SET,
    BSP_KEY_VALUE_BACK,
    BSP_KEY_VALUE_MID,
    BSP_KEY_VALUE_ADD,
    BSP_KEY_VALUE_SUB
};

static uint32_t bsp_key_enter_critical(void)
{
    uint32_t wPrimask = __get_PRIMASK();
    __disable_irq();
    return wPrimask;
}

static void bsp_key_exit_critical(uint32_t primask)
{
    __set_PRIMASK(primask);
}

static void bsp_key_clear_queue(void)
{
    uint32_t wPrimask = bsp_key_enter_critical();
    s_chHead = 0U;
    s_chTail = 0U;
    s_chCount = 0U;
    s_wOverflowCount = 0U;
    bsp_key_exit_critical(wPrimask);
}

static void bsp_key_on_event(KEY_ID key_id, uint32_t event)
{
    bsp_key_event_t *ptEvent;

    if (!s_bInitialized) {
        return;
    }
    if (s_chCount == BSP_KEY_EVENT_QUEUE_SIZE) {
        if (s_wOverflowCount != UINT32_MAX) {
            s_wOverflowCount++;
        }
        return;
    }

    ptEvent = &s_tEventQueue[s_chHead];
    ptEvent->key_id = key_id;
    ptEvent->key_value = s_tKeyValues[key_id];
    ptEvent->event = event;
    s_chHead = (uint8_t)((s_chHead + 1U) % BSP_KEY_EVENT_QUEUE_SIZE);
    s_chCount++;
}

/* 固定 EDAL 回调没有 key_id，通过各实例注册的薄回调绑定编号。 */
static void bsp_key0_on_event(uint32_t event) { bsp_key_on_event(KEY_0, event); }
static void bsp_key1_on_event(uint32_t event) { bsp_key_on_event(KEY_1, event); }
static void bsp_key2_on_event(uint32_t event) { bsp_key_on_event(KEY_2, event); }
static void bsp_key3_on_event(uint32_t event) { bsp_key_on_event(KEY_3, event); }
static void bsp_key4_on_event(uint32_t event) { bsp_key_on_event(KEY_4, event); }

static const EDAL_KEY_SignalEvent_t s_pfnCallbacks[TS10_KEY_COUNT] = {
    bsp_key0_on_event,
    bsp_key1_on_event,
    bsp_key2_on_event,
    bsp_key3_on_event,
    bsp_key4_on_event
};

bool bsp_key_init(void)
{
    uint32_t wInitializedCount = 0U;
    uint32_t wIndex;

    if (s_bInitialized) {
        return true;
    }
    bsp_key_clear_queue();

    for (wIndex = 0U; wIndex < TS10_KEY_COUNT; wIndex++) {
        if (TS10_KEY_Devices[wIndex]->Initialize(s_pfnCallbacks[wIndex]) != EDAL_DEVICE_OK) {
            goto init_failed;
        }
        wInitializedCount++;

        if (TS10_KEY_Devices[wIndex]->PowerControl(EDAL_POWER_FULL) != EDAL_DEVICE_OK) {
            goto init_failed;
        }
        if (TS10_KEY_Devices[wIndex]->Control(EDAL_KEY_SET_EVENT_MASK,
                                             BSP_KEY_DEFAULT_EVENTS) != EDAL_DEVICE_OK) {
            goto init_failed;
        }
        s_wEventMasks[wIndex] = BSP_KEY_DEFAULT_EVENTS;
    }

    s_bInitialized = true;
    return true;

init_failed:
    while (wInitializedCount != 0U) {
        wInitializedCount--;
        (void)TS10_KEY_Devices[wInitializedCount]->PowerControl(EDAL_POWER_OFF);
        (void)TS10_KEY_Devices[wInitializedCount]->Uninitialize();
    }
    for (wIndex = 0U; wIndex < TS10_KEY_COUNT; wIndex++) {
        s_wEventMasks[wIndex] = 0U;
    }
    bsp_key_clear_queue();
    return false;
}

int32_t bsp_key_uninit(void)
{
    int32_t nResult = EDAL_DEVICE_OK;
    int32_t nStatus;
    uint32_t wIndex;
    uint32_t wPrimask = bsp_key_enter_critical();

    s_bInitialized = false;
    bsp_key_exit_critical(wPrimask);

    for (wIndex = 0U; wIndex < TS10_KEY_COUNT; wIndex++) {
        nStatus = TS10_KEY_Devices[wIndex]->PowerControl(EDAL_POWER_OFF);
        if (nResult == EDAL_DEVICE_OK && nStatus != EDAL_DEVICE_OK) {
            nResult = nStatus;
        }
        nStatus = TS10_KEY_Devices[wIndex]->Uninitialize();
        if (nResult == EDAL_DEVICE_OK && nStatus != EDAL_DEVICE_OK) {
            nResult = nStatus;
        }
        s_wEventMasks[wIndex] = 0U;
    }

    bsp_key_clear_queue();
    return nResult;
}

bool bsp_key_get_event(bsp_key_event_t *event)
{
    uint32_t wPrimask;

    if (event == NULL) {
        return false;
    }

    wPrimask = bsp_key_enter_critical();
    if (s_chCount == 0U) {
        bsp_key_exit_critical(wPrimask);
        return false;
    }
    *event = s_tEventQueue[s_chTail];
    s_chTail = (uint8_t)((s_chTail + 1U) % BSP_KEY_EVENT_QUEUE_SIZE);
    s_chCount--;
    bsp_key_exit_critical(wPrimask);

    if ((event->event & (EDAL_KEY_EVENT_CLICKED | EDAL_KEY_EVENT_DOUBLE_CLICK |
                         EDAL_KEY_EVENT_LONG_PRESS)) != 0U) {
        BEEP_DIDIDIDI(100);
    }
    return true;
}

uint8_t bsp_key_get_value(void)
{
    bsp_key_event_t tEvent;
    uint8_t chType;

    while (bsp_key_get_event(&tEvent)) {
        if ((tEvent.event & EDAL_KEY_EVENT_CLICKED) != 0U) {
            chType = BSP_KEY_PRESSED;
        } else if ((tEvent.event & EDAL_KEY_EVENT_DOUBLE_CLICK) != 0U) {
            chType = BSP_KEY_DOUBLE_CLICK;
        } else if ((tEvent.event & (EDAL_KEY_EVENT_LONG_PRESS |
                                   EDAL_KEY_EVENT_LONG_PRESS_REPEAT)) != 0U) {
            chType = BSP_KEY_LONG_PRESSED;
        } else {
            /* 兼容字节编码没有按下、释放、长按释放的编码，继续取下一项。 */
            continue;
        }
        return (uint8_t)((chType << 4U) | (uint8_t)tEvent.key_id);
    }
    return BSP_KEY_NONE;
}

static int32_t bsp_key_change_events(KEY_ID key_id, uint32_t event_mask, bool add)
{
    uint32_t wFirst;
    uint32_t wEnd;
    uint32_t wIndex;
    uint32_t wRollback;
    uint32_t wNewMask;
    uint32_t wOldMasks[TS10_KEY_COUNT];
    uint32_t wPrimask;
    int32_t nStatus;

    if ((uint32_t)key_id > (uint32_t)KEY_ALL ||
        (event_mask & ~EDAL_KEY_EVENT_ALL) != 0U) {
        return EDAL_DEVICE_ERROR_PARAMETER;
    }

    wFirst = (key_id == KEY_ALL) ? 0U : (uint32_t)key_id;
    wEnd = (key_id == KEY_ALL) ? TS10_KEY_COUNT : wFirst + 1U;
    wPrimask = bsp_key_enter_critical();
    if (!s_bInitialized) {
        bsp_key_exit_critical(wPrimask);
        return EDAL_DEVICE_ERROR;
    }

    for (wIndex = wFirst; wIndex < wEnd; wIndex++) {
        wOldMasks[wIndex] = s_wEventMasks[wIndex];
        wNewMask = add ? (wOldMasks[wIndex] | event_mask)
                       : (wOldMasks[wIndex] & ~event_mask);
        nStatus = TS10_KEY_Devices[wIndex]->Control(EDAL_KEY_SET_EVENT_MASK, wNewMask);
        if (nStatus != EDAL_DEVICE_OK) {
            /* 旧掩码由之前成功的 Control 保存，批量失败时恢复已修改的实例。 */
            for (wRollback = wFirst; wRollback < wIndex; wRollback++) {
                (void)TS10_KEY_Devices[wRollback]->Control(EDAL_KEY_SET_EVENT_MASK,
                                                         wOldMasks[wRollback]);
                s_wEventMasks[wRollback] = wOldMasks[wRollback];
            }
            bsp_key_exit_critical(wPrimask);
            return nStatus;
        }
        s_wEventMasks[wIndex] = wNewMask;
    }
    bsp_key_exit_critical(wPrimask);
    return EDAL_DEVICE_OK;
}

int32_t bsp_key_add_event(KEY_ID key_id, uint32_t event_mask)
{
    return bsp_key_change_events(key_id, event_mask, true);
}

int32_t bsp_key_remove_event(KEY_ID key_id, uint32_t event_mask)
{
    return bsp_key_change_events(key_id, event_mask, false);
}

uint32_t bsp_key_get_overflow_count(void)
{
    uint32_t wPrimask = bsp_key_enter_critical();
    uint32_t wCount = s_wOverflowCount;
    bsp_key_exit_critical(wPrimask);
    return wCount;
}
