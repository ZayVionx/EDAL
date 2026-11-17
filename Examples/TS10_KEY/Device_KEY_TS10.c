#include "Device_KEY_TS10.h"
#include "sys.h"
#include "emb_btn.h"

#if EMB_CFG_BTN_SCAN_PERIOD_MS != 1U
#error "TS10_KEY_Scan1ms requires EMB_CFG_BTN_SCAN_PERIOD_MS == 1"
#endif

typedef struct {
    emb_btn_t button;
    EDAL_KEY_SignalEvent_t callback;
    volatile EDAL_KEY_STATUS status;
    volatile uint32_t event_mask;
    volatile bool initialized;
    volatile bool powered;
} TS10_KEY_CONTEXT;

static TS10_KEY_CONTEXT s_keys[TS10_KEY_COUNT];
static uint8_t s_engine_event_buffer[128];
static uint32_t s_registered_count;
static bool s_engine_ready;

static const EDAL_VERSION s_version = {
    EDAL_KEY_API_VERSION,
    EDAL_VERSION_MAJOR_MINOR(1, 0)
};

static const EDAL_KEY_CAPABILITIES s_capabilities = {
    .event_press = 1,
    .event_release = 1,
    .event_clicked = 1,
    .event_double_click = 1,
    .event_long_press = 1,
    .event_long_press_release = 1,
    .event_long_press_repeat = 1,
    .debounce = 1,
    .timing_config = 1,
    .wakeup = 0,
    .reserved = 0
};

static const uint16_t s_pins[TS10_KEY_COUNT] = {
    GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4
};

static uint32_t Key_Lock(void)
{
    uint32_t saved = __get_PRIMASK();
    __disable_irq();
    return saved;
}

static void Key_Unlock(uint32_t saved)
{
    __set_PRIMASK(saved);
}

static bool Key_ReadLevel(uint32_t id)
{
    /* 停用节点仍留在 emb_btn 链表中，但始终向引擎提供未按下电平。 */
    if (!s_keys[id].initialized || !s_keys[id].powered) {
        return true;
    }
    return GPIO_ReadInputDataBit(GPIOE, s_pins[id]) != 0;
}

#define KEY_LEVEL_READER(n) \
    static bool Key##n##_ReadLevel(void) { return Key_ReadLevel(n); }
KEY_LEVEL_READER(0)
KEY_LEVEL_READER(1)
KEY_LEVEL_READER(2)
KEY_LEVEL_READER(3)
KEY_LEVEL_READER(4)
#undef KEY_LEVEL_READER

static bool (*const s_readers[TS10_KEY_COUNT])(void) = {
    Key0_ReadLevel, Key1_ReadLevel, Key2_ReadLevel, Key3_ReadLevel, Key4_ReadLevel
};

static void Key_OnEngineEvent(uint8_t engine_id, emb_btn_event_t event)
{
    uint32_t id;
    uint32_t notification;
    TS10_KEY_CONTEXT *key;
    static const uint32_t events[] = {
        EDAL_KEY_EVENT_PRESS, EDAL_KEY_EVENT_RELEASE, EDAL_KEY_EVENT_CLICKED,
        EDAL_KEY_EVENT_DOUBLE_CLICK, EDAL_KEY_EVENT_LONG_PRESS,
        EDAL_KEY_EVENT_LONG_PRESS_RELEASE, EDAL_KEY_EVENT_LONG_PRESS_REPEAT
    };

    if ((uint32_t)event >= sizeof(events) / sizeof(events[0])) {
        return;
    }
    /* 使用引擎实际分配的 ID，EDAL 实例编号不依赖注册调用顺序。 */
    for (id = 0; id < s_registered_count; ++id) {
        if (s_keys[id].button.u8Id == engine_id) {
            break;
        }
    }
    if (id == s_registered_count) {
        return;
    }
    key = &s_keys[id];
    if (!key->initialized || !key->powered) {
        return;
    }

    switch (event) {
        case EMB_BTN_EVT_PRESS:              key->status.press = 1; break;
        case EMB_BTN_EVT_RELEASE:            key->status.press = 0; key->status.release = 1; break;
        case EMB_BTN_EVT_CLICKED:            key->status.clicked = 1; break;
        case EMB_BTN_EVT_DOUBLE_CLICK:       key->status.double_click = 1; break;
        case EMB_BTN_EVT_LONG_PRESS:         key->status.long_press = 1; break;
        case EMB_BTN_EVT_LONG_PRESS_RELEASE: key->status.long_press_release = 1; break;
        case EMB_BTN_EVT_LONG_PRESS_REPEAT:  key->status.long_press_repeat = 1; break;
        default: return;
    }

    notification = events[event] & key->event_mask;
    if (notification != 0U && key->callback != NULL) {
        /* 与 emb_btn_scan 同一上下文。SysTick 调用时，用户回调只做入队。 */
        key->callback(notification);
    }
}

static void Key_ResetRuntime(TS10_KEY_CONTEXT *key)
{
    EDAL_KEY_STATUS empty = {0};
    /* 不清整个 button，必须保留 ptNext、u8Id 和 tCfg。0 是所用库的 IDLE。 */
    key->button.u8State = 0;
    key->button.u16Tick = 0;
    key->button.u8ClickCount = 0;
    key->button.u16Integrator = 0;
    key->button.bPinLevel = true;
    key->status = empty;
}

static bool Key_PrepareEngine(void)
{
    GPIO_InitType gpio;
    if (s_engine_ready) {
        return true;
    }

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
    gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;
    gpio.GPIO_Mode = GPIO_Mode_IPD; /* 沿用原 key.c 的板级配置。 */
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(GPIOE, &gpio);

    if (!emb_btn_init(s_engine_event_buffer, sizeof(s_engine_event_buffer))) {
        return false;
    }
    /* emb_btn 没有 unregister；各节点整个程序只注册一次。 */
    while (s_registered_count < TS10_KEY_COUNT) {
        emb_btn_cfg_t config = {
            .bActiveLevel = false,
            .pfGetLevel = s_readers[s_registered_count],
            .pfCallback = Key_OnEngineEvent,
            .u16DebounceMs = 20,
            .u16DoubleClickMs = 150,
            .u16LongPressMs = 500,
            .u16RepeatIntervalMs = 100
        };
        emb_btn_t *button = &s_keys[s_registered_count].button;
        if (!emb_btn_register(button, &config)) {
            return false;
        }
        /* 引擎掩码还影响双击识别，不能用它实现 EDAL 的回调过滤。 */
        emb_btn_set_event_enable(button, (uint8_t)(
            EMB_BTN_MASK_PRESS | EMB_BTN_MASK_RELEASE | EMB_BTN_MASK_CLICKED |
            EMB_BTN_MASK_DOUBLE_CLICK | EMB_BTN_MASK_LONG_PRESS |
            EMB_BTN_MASK_LONG_PRESS_RELEASE | EMB_BTN_MASK_LONG_PRESS_REPEAT));
        ++s_registered_count;
    }
    s_engine_ready = true;
    return true;
}

static int32_t Key_Initialize(uint32_t id, EDAL_KEY_SignalEvent_t callback)
{
    TS10_KEY_CONTEXT *key = &s_keys[id];
    uint32_t saved = Key_Lock();
    int32_t result = EDAL_DEVICE_OK;
    if (key->initialized) {
        result = key->callback == callback ? EDAL_DEVICE_OK : EDAL_DEVICE_ERROR_BUSY;
    } else if (!Key_PrepareEngine()) {
        result = EDAL_DEVICE_ERROR;
    } else {
        key->callback = callback;
        key->event_mask = EDAL_KEY_EVENT_ALL;
        key->powered = false;
        /* 此示例明确只支持 1 ms 扫描，库配置字段此时存放扫描次数。 */
        key->button.tCfg.u16DebounceMs = 20;
        key->button.tCfg.u16DoubleClickMs = 150;
        key->button.tCfg.u16LongPressMs = 500;
        key->button.tCfg.u16RepeatIntervalMs = 100;
        Key_ResetRuntime(key);
        key->initialized = true;
    }
    Key_Unlock(saved);
    return result;
}

static int32_t Key_Uninitialize(uint32_t id)
{
    TS10_KEY_CONTEXT *key = &s_keys[id];
    uint32_t saved = Key_Lock();
    key->powered = false;
    key->initialized = false;
    key->callback = NULL;
    key->event_mask = 0;
    Key_ResetRuntime(key);
    Key_Unlock(saved);
    return EDAL_DEVICE_OK;
}

static int32_t Key_PowerControl(uint32_t id, EDAL_POWER_STATE state)
{
    TS10_KEY_CONTEXT *key = &s_keys[id];
    uint32_t saved = Key_Lock();
    int32_t result = EDAL_DEVICE_OK;
    if (!key->initialized) {
        result = EDAL_DEVICE_ERROR;
    } else if (state == EDAL_POWER_OFF) {
        key->powered = false;
        Key_ResetRuntime(key);
    } else if (state == EDAL_POWER_FULL) {
        if (!key->powered) {
            Key_ResetRuntime(key);
            key->powered = true;
        }
    } else if (state == EDAL_POWER_LOW) {
        result = EDAL_DEVICE_ERROR_UNSUPPORTED;
    } else {
        result = EDAL_DEVICE_ERROR_PARAMETER;
    }
    Key_Unlock(saved);
    return result;
}

static int32_t Key_Control(uint32_t id, uint32_t control, uint32_t arg)
{
    TS10_KEY_CONTEXT *key = &s_keys[id];
    uint16_t *timing = NULL;
    int32_t result = EDAL_DEVICE_OK;
    uint32_t saved = Key_Lock();

    if (!key->initialized) {
        result = EDAL_DEVICE_ERROR;
    } else if ((control & ~EDAL_KEY_CONTROL_Msk) != 0U) {
        result = EDAL_DEVICE_ERROR_PARAMETER;
    } else {
        switch (control) {
            case EDAL_KEY_SET_EVENT_MASK:
                if ((arg & ~EDAL_KEY_EVENT_ALL) != 0U) {
                    result = EDAL_DEVICE_ERROR_PARAMETER;
                } else {
                    key->event_mask = arg;
                }
                break;
            case EDAL_KEY_CONTROL_WAKEUP:
                result = arg > EDAL_KEY_ENABLE ? EDAL_DEVICE_ERROR_PARAMETER :
                         arg == EDAL_KEY_ENABLE ? EDAL_DEVICE_ERROR_UNSUPPORTED : EDAL_DEVICE_OK;
                break;
            case EDAL_KEY_SET_DEBOUNCE_TIME:     timing = &key->button.tCfg.u16DebounceMs; break;
            case EDAL_KEY_SET_DOUBLE_CLICK_TIME: timing = &key->button.tCfg.u16DoubleClickMs; break;
            case EDAL_KEY_SET_LONG_PRESS_TIME:   timing = &key->button.tCfg.u16LongPressMs; break;
            case EDAL_KEY_SET_REPEAT_PERIOD:     timing = &key->button.tCfg.u16RepeatIntervalMs; break;
            default: result = EDAL_DEVICE_ERROR_UNSUPPORTED; break;
        }
        if (timing != NULL) {
            if (arg > UINT16_MAX || (arg == 0U && control != EDAL_KEY_SET_DEBOUNCE_TIME)) {
                result = EDAL_DEVICE_ERROR_PARAMETER;
            } else if (key->button.u8State != 0U || key->button.u16Integrator != 0U ||
                       !Key_ReadLevel(id)) {
                result = EDAL_DEVICE_ERROR_BUSY;
            } else {
                /* 阈值 0 会令原引擎误触发；1 tick 表示单次采样确认，无额外去抖。 */
                *timing = (uint16_t)(arg == 0U ? 1U : arg);
            }
        }
    }
    Key_Unlock(saved);
    return result;
}

static EDAL_KEY_STATUS Key_GetStatus(uint32_t id)
{
    EDAL_KEY_STATUS snapshot;
    EDAL_KEY_STATUS empty = {0};
    uint32_t saved = Key_Lock();
    snapshot = s_keys[id].status;
    /* press 保持当前稳定状态；其余位读清，只适合观察，不代替事件队列。 */
    empty.press = snapshot.press;
    s_keys[id].status = empty;
    Key_Unlock(saved);
    return snapshot;
}

static EDAL_VERSION Key_GetVersion(void) { return s_version; }
static EDAL_KEY_CAPABILITIES Key_GetCapabilities(void) { return s_capabilities; }

/* 五个实例只生成薄包装；GPIO、识别、生命周期和控制逻辑全部共用。 */
#define KEY_DEVICE(n) \
    static int32_t Key##n##_Initialize(EDAL_KEY_SignalEvent_t cb) { return Key_Initialize(n, cb); } \
    static int32_t Key##n##_Uninitialize(void) { return Key_Uninitialize(n); } \
    static int32_t Key##n##_PowerControl(EDAL_POWER_STATE state) { return Key_PowerControl(n, state); } \
    static int32_t Key##n##_Control(uint32_t control, uint32_t arg) { return Key_Control(n, control, arg); } \
    static EDAL_KEY_STATUS Key##n##_GetStatus(void) { return Key_GetStatus(n); } \
    EDAL_DEVICE_KEY EDAL_Device_KEY_(n) = { \
        Key_GetVersion, Key_GetCapabilities, Key##n##_Initialize, Key##n##_Uninitialize, \
        Key##n##_PowerControl, Key##n##_Control, Key##n##_GetStatus \
    };
KEY_DEVICE(0)
KEY_DEVICE(1)
KEY_DEVICE(2)
KEY_DEVICE(3)
KEY_DEVICE(4)
#undef KEY_DEVICE

EDAL_DEVICE_KEY *const TS10_KEY_Devices[TS10_KEY_COUNT] = {
    &Device_KEY0, &Device_KEY1, &Device_KEY2, &Device_KEY3, &Device_KEY4
};

void TS10_KEY_Scan1ms(void)
{
    uint8_t id;
    emb_btn_event_t event;
    emb_btn_scan();
    /* 引擎会同时回调和写内部队列；回调已分发，丢弃重复副本。 */
    while (emb_btn_get_event(&id, &event)) {
    }
}
