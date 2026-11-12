#ifndef __EDAL_KEY_H__
#define __EDAL_KEY_H__

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
 * @brief Key driver operations shared by multiple instances.
 */
typedef struct {
    EDAL_Status_t (*Init       )(void);
    EDAL_Status_t (*DeInit     )(void);
    uint8_t       (*GetValue   )(void);
    EDAL_Status_t (*AddEvent   )(uint8_t chKeyID, uint8_t chEventMask);
    EDAL_Status_t (*RemoveEvent)(uint8_t chKeyID, uint8_t chEventMask);
} Key_DrvType_t;

/**
 * @brief Key device instance.
 * @note context holds hardware configuration and private data for this instance.
 *       state is managed by KEY_Init and KEY_DeInit.
 */
typedef struct {
    Key_DrvType_t drv;
    EDAL_DeviceState_t state;
    void *context;
} Key_Device_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
EDAL_Status_t Key_Init          (Key_Device_t *device);
EDAL_Status_t Key_DeInit        (Key_Device_t *device);
uint8_t       Key_Get_Value     (Key_Device_t *device);
EDAL_Status_t Key_Add_Event     (Key_Device_t *device, uint8_t chKeyID, uint8_t chEventMask);
EDAL_Status_t Key_Remove_Event  (Key_Device_t *device, uint8_t chKeyID, uint8_t chEventMask);

/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __EDAL_KEY_H__ */
