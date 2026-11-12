/*============================ INCLUDES ======================================*/
#include "edal_key.h"
#include <stddef.h>

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
static uint8_t Key_Device_IsValid(const Key_Device_t *device)
{
    return (   device                    != NULL 
            && device->drv               != NULL
            && device->drv.Init          != NULL 
            && device->drv.DeInit        != NULL
            && device->drv.GetValue      != NULL 
            && device->drv.AddEvent      != NULL
            && device->drv.RemoveEvent   != NULL );
}

/*============================ IMPLEMENTATION ================================*/
/**
 * Key_Init - initialize an Key device
 * @device: device instance to initialize
 * 
 * @retval: EDAL_STATUS_OK on success,
 *          otherwise an error code.
 */
EDAL_Status_t Key_Init(Key_Device_t *device)
{
    EDAL_Status_t status;

    if (!Key_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state == EDAL_DEVICE_READY) {
        return EDAL_STATUS_OK;
    }

    status = device->drv.Init();
    if (status == EDAL_STATUS_OK) {
        device->state = EDAL_DEVICE_READY;
    }
    return status;
}

/**
 * 
 */
EDAL_Status_t Key_DeInit(Key_Device_t *device)
{

}

/**
 * 
 */
uint8_t Key_Get_Value(Key_Device_t *device)
{

}

/**
 * 
 */
EDAL_Status_t Key_Add_Event(Key_Device_t *device, uint8_t chKeyID, uint8_t chEventMask)
{

}

/**
 * 
 */
EDAL_Status_t Key_Remove_Event(Key_Device_t *device, uint8_t chKeyID, uint8_t chEventMask)
{

}



/*============================ END ===========================================*/
