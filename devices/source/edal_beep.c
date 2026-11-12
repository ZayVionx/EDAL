/*============================ INCLUDES ======================================*/
#include "edal_beep.h"
#include <stddef.h>

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
static uint8_t Beep_Device_IsValid(const Beep_Device_t *device)
{
    return (   device               != NULL 
            && device->drv          != NULL
            && device->drv->Init    != NULL 
            && device->drv->DeInit  != NULL
            && device->drv->Play    != NULL 
            && device->drv->Stop    != NULL
            && device->drv->SetVol  != NULL
            && device->drv->GetVol  != NULL );
}

/*============================ IMPLEMENTATION ================================*/
/**
 * Beep_Init - initialize a beep device
 * @device: device instance to initialize
 *
 * @retval: EDAL_STATUS_OK on success, 
 *          otherwise an error code.
 */
EDAL_Status_t Beep_Init(Beep_Device_t *device)
{
    EDAL_Status_t status;

    if (!Beep_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state == EDAL_DEVICE_READY) {
        return EDAL_STATUS_OK;
    }

    status = device->drv->Init(device->context);
    if (status == EDAL_STATUS_OK) {
        device->state = EDAL_DEVICE_READY;
    }
    return status;
}

/**
 * Beep_DeInit - stop and deinitialize a beep device
 * @device: device instance to deinitialize
 *
 * @retval: EDAL_STATUS_OK on success, 
 *          otherwise an error code.
 */
EDAL_Status_t Beep_DeInit(Beep_Device_t *device)
{
    EDAL_Status_t status;

    if (!Beep_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state == EDAL_DEVICE_UNINITIALIZED) {
        return EDAL_STATUS_OK;
    }

    status = device->drv->Stop(device->context);
    if (status != EDAL_STATUS_OK) {
        return status;
    }
    status = device->drv->DeInit(device->context);
    if (status == EDAL_STATUS_OK) {
        device->state = EDAL_DEVICE_UNINITIALIZED;
    }
    return status;
}

/**
 * Beep_Play - request a sequence of beeps
 * @device: Beep device instance
 * @count: number of beeps, greater than 0
 * @duration_ms: duration of each beep in ms, greater than 0
 *
 * @retval: EDAL_STATUS_OK on success, 
 *          otherwise an error code.
 */
EDAL_Status_t Beep_Play(Beep_Device_t *device, uint32_t count, uint32_t duration_ms)
{
    if (!Beep_Device_IsValid(device) || count == 0 || duration_ms == 0) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state != EDAL_DEVICE_READY) {
        return EDAL_STATUS_NOT_READY;
    }
    return device->drv->Play(device->context, count, duration_ms);
}

/**
 * Beep_Stop - stop beep output without deinitializing the device
 * @device: Beep device instance
 *
 * @retval: EDAL_STATUS_OK on success, 
 *          otherwise an error code.
 */
EDAL_Status_t Beep_Stop(Beep_Device_t *device)
{
    if (!Beep_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state != EDAL_DEVICE_READY) {
        return EDAL_STATUS_NOT_READY;
    }
    return device->drv->Stop(device->context);
}

/**
 * Beep_SetVol - set the beep volume
 * @device: Beep device instance
 * @volume: volume level to set
 *
 * @retval: EDAL_STATUS_OK on success,
 *          otherwise an error code.
 */
EDAL_Status_t Beep_SetVol(Beep_Device_t *device, uint32_t volume)
{
    if (!Beep_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state != EDAL_DEVICE_READY) {
        return EDAL_STATUS_NOT_READY;
    }
    if (device->drv->SetVol == NULL) {
        return EDAL_STATUS_NOT_SUPPORTED;
    }
    return device->drv->SetVol(device->context, volume);
}

/**
 * Beep_GetVol - get the beep volume
 * @device: Beep device instance
 *
 * @retval: volume level on success,
 *          0 otherwise.
 */
uint32_t Beep_GetVol(Beep_Device_t *device)
{
    if (   !Beep_Device_IsValid(device) 
        || device->state != EDAL_DEVICE_READY
        || device->drv->GetVol == NULL  ) 
    {
        return 0;
    }
    return device->drv->GetVol(device->context);
}


/*============================ END ===========================================*/
