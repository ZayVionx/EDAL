#ifndef KEY_EDAL_H
#define KEY_EDAL_H

#include "Device_KEY_TS10.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_KEY_NUM                  TS10_KEY_COUNT
#define BSP_KEY_PRESSED              0U
#define BSP_KEY_LONG_PRESSED         1U
#define BSP_KEY_DOUBLE_CLICK         2U
#define BSP_KEY_NONE                 0xFFU
#define BSP_KEY_EVENT_QUEUE_SIZE     64U

typedef enum {
    KEY_0 = 0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_ALL
} KEY_ID;

/* 业务键值，由应用定义；不写入公共 Device_KEY.h。 */
typedef enum {
    BSP_KEY_VALUE_SET = 1,
    BSP_KEY_VALUE_BACK,
    BSP_KEY_VALUE_MID,
    BSP_KEY_VALUE_ADD,
    BSP_KEY_VALUE_SUB
} bsp_key_value_t;

typedef struct {
    KEY_ID          key_id;       /* 物理按键编号 KEY_0 至 KEY_4。 */
    bsp_key_value_t key_value;    /* 对应的业务键值。 */
    uint32_t        event;        /* EDAL_KEY_EVENT_xxx。 */
} bsp_key_event_t;

/* 以下管理接口仅从同一主循环/任务调用，不能在回调中重入。 */
bool bsp_key_init(void);
int32_t bsp_key_uninit(void);

/* 两种读取接口消费同一个队列，一个应用选择其中一种即可。
 * 在前台消费单击、双击或首次长按时蜂鸣；长按连发不蜂鸣。
 */
bool bsp_key_get_event(bsp_key_event_t *event);
uint8_t bsp_key_get_value(void);

/* 使用 EDAL 事件掩码；KEY_ALL 对所有按键应用相同的增删操作。
 * 保留未选中的事件位；修改通知掩码不改变双击识别过程。
 * 本层保存当前掩码，初始化后请统一通过这两个接口修改通知掩码。
 */
int32_t bsp_key_add_event(KEY_ID key_id, uint32_t event_mask);
int32_t bsp_key_remove_event(KEY_ID key_id, uint32_t event_mask);

/* 队列满时丢弃新事件；计数在初始化或卸载时清零。 */
uint32_t bsp_key_get_overflow_count(void);

#ifdef __cplusplus
}
#endif

#endif /* KEY_EDAL_H */
