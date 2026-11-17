#ifndef DEVICE_KEY_TS10_H
#define DEVICE_KEY_TS10_H

#include "Device_KEY.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TS10_KEY_COUNT 5U

/* 板级实例声明；公共 Device_KEY.h 无需添加这些内容。 */
extern EDAL_DEVICE_KEY EDAL_Device_KEY_(0);
extern EDAL_DEVICE_KEY EDAL_Device_KEY_(1);
extern EDAL_DEVICE_KEY EDAL_Device_KEY_(2);
extern EDAL_DEVICE_KEY EDAL_Device_KEY_(3);
extern EDAL_DEVICE_KEY EDAL_Device_KEY_(4);
extern EDAL_DEVICE_KEY *const TS10_KEY_Devices[TS10_KEY_COUNT];

/* 每 1 ms 调用一次。替代直接 emb_btn_scan()，不能两者各扫描一次。 */
void TS10_KEY_Scan1ms(void);

#ifdef __cplusplus
}
#endif
#endif
