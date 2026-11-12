#ifndef __EDAL_BEEP_H__
#define __EDAL_BEEP_H__

/*============================ INCLUDES ======================================*/
#include <stdint.h>
#include "../edal_types.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/**
 * @brief Beep driver operations shared by multiple instances.
 */
typedef struct {
    EDAL_Status_t (*Init   )(void *context);
    EDAL_Status_t (*DeInit )(void *context);
    EDAL_Status_t (*Play   )(void *context, uint32_t count, uint32_t duration_ms);
    EDAL_Status_t (*Stop   )(void *context);
    EDAL_Status_t (*SetVol )(void *context, uint32_t volume);
    uint32_t      (*GetVol )(void *context);
} Beep_DrvType_t;

/**
 * @brief Beep device instance.
 * @note context holds hardware configuration and private data for this instance.
 *       state is managed by Beep_Init and Beep_DeInit.
 */
typedef struct {
    const Beep_DrvType_t *drv;
    void *context;
    EDAL_DeviceState_t state;
} Beep_Device_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
EDAL_Status_t Beep_Init  (Beep_Device_t *device);
EDAL_Status_t Beep_DeInit(Beep_Device_t *device);
EDAL_Status_t Beep_Play  (Beep_Device_t *device, uint32_t count, uint32_t duration_ms);
EDAL_Status_t Beep_Stop  (Beep_Device_t *device);
EDAL_Status_t Beep_SetVol(Beep_Device_t *device, uint32_t volume);
uint32_t      Beep_GetVol(Beep_Device_t *device);

/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __EDAL_BEEP_H__ */
