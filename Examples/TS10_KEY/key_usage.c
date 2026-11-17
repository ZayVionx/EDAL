/* 外部调用示例。选择结构化读取或兼容字节读取，不要同时消费队列。 */
#include "key_edal.h"
#include <stdio.h>

bool TS10_KeyExample_Init(void)
{
    if (!bsp_key_init()) {
        return false;
    }

    /* 可选：为加、减键开启长按连发；其它键仍使用默认的三个事件。 */
    if (bsp_key_add_event(KEY_3, EDAL_KEY_EVENT_LONG_PRESS_REPEAT) != EDAL_DEVICE_OK ||
        bsp_key_add_event(KEY_4, EDAL_KEY_EVENT_LONG_PRESS_REPEAT) != EDAL_DEVICE_OK) {
        (void)bsp_key_uninit();
        return false;
    }
    return true;
}

/* 在现有 SysTick_Handler 内每 1 ms 调用一次，替换原 emb_btn_scan 那一行。 */
void TS10_KeyExample_OnSysTick1ms(void)
{
    TS10_KEY_Scan1ms();
}

/* 方式一：前台主循环调用，直接取得编号、业务键值和事件。 */
void TS10_KeyExample_Poll(void)
{
    bsp_key_event_t key;
    while (bsp_key_get_event(&key)) {
        printf("按键编号=%u，业务键值=%u，事件=0x%02lx\n",
               (unsigned)key.key_id, (unsigned)key.key_value, (unsigned long)key.event);

        if (key.key_value == BSP_KEY_VALUE_SET && key.event == EDAL_KEY_EVENT_CLICKED) {
            printf("设置键单击\n");
        } else if (key.key_value == BSP_KEY_VALUE_BACK && key.event == EDAL_KEY_EVENT_LONG_PRESS) {
            printf("返回键长按\n");
        } else if (key.key_value == BSP_KEY_VALUE_ADD &&
                   (key.event & (EDAL_KEY_EVENT_CLICKED | EDAL_KEY_EVENT_LONG_PRESS_REPEAT)) != 0U) {
            printf("加一次\n");
        } else if (key.key_value == BSP_KEY_VALUE_SUB &&
                   (key.event & (EDAL_KEY_EVENT_CLICKED | EDAL_KEY_EVENT_LONG_PRESS_REPEAT)) != 0U) {
            printf("减一次\n");
        }
    }
}

/* 方式二：供原来的 GUI 编码映射使用；不与上面的 Poll 同时调用。 */
bool TS10_KeyExample_ReadLegacy(KEY_ID *key_id, uint8_t *event_type)
{
    uint8_t code;
    if (key_id == NULL || event_type == NULL) {
        return false;
    }
    code = bsp_key_get_value();
    if (code == BSP_KEY_NONE) {
        return false;
    }
    *key_id = (KEY_ID)(code & 0x0FU);
    *event_type = (uint8_t)(code >> 4U);
    return true;
}

/* 按键处于空闲时设置；按下、去抖中、等待双击时会返回 BUSY。 */
int32_t TS10_KeyExample_SetLongPress(KEY_ID key_id, uint32_t milliseconds)
{
    if ((uint32_t)key_id >= TS10_KEY_COUNT) {
        return EDAL_DEVICE_ERROR_PARAMETER;
    }
    return TS10_KEY_Devices[key_id]->Control(EDAL_KEY_SET_LONG_PRESS_TIME, milliseconds);
}

/* 这是当前按下状态查询；GetStatus 同时读清该实例的其它事件锁存位。 */
bool TS10_KeyExample_IsPressed(KEY_ID key_id)
{
    EDAL_KEY_STATUS status;
    if ((uint32_t)key_id >= TS10_KEY_COUNT) {
        return false;
    }
    status = TS10_KEY_Devices[key_id]->GetStatus();
    return status.press != 0U;
}
