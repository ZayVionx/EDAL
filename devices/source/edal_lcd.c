/*============================ INCLUDES ======================================*/
#include "edal_lcd.h"
#include <stddef.h>

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
static uint8_t LCD_Device_IsValid(const LCD_Device_t *device)
{
    return (   device                    != NULL 
            && device->drv               != NULL
            && device->drv->Init         != NULL 
            && device->drv->DeInit       != NULL
            && device->drv->DisplayOn    != NULL 
            && device->drv->DisplayOff   != NULL
            && device->drv->DisplayDir   != NULL
            && device->drv->SetBacklight != NULL
            && device->drv->DisplayClear != NULL 
            && device->drv->DisplayDraw  != NULL );
}

/*============================ IMPLEMENTATION ================================*/
/**
 * LCD_Init - initialize an LCD device
 * @device: device instance to initialize
 *
 * Repeated calls on a ready device succeed without reinitializing the driver.
 * The device becomes ready only after the driver initializes successfully.
 *
 * @retval: EDAL_STATUS_OK on success,
 *          otherwise an error code.
 */
EDAL_Status_t LCD_Init(LCD_Device_t *device)
{
    EDAL_Status_t status;

    if (!LCD_Device_IsValid(device)) {
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
 * LCD_DeInit - turn off and deinitialize an LCD device
 * @device: device instance to deinitialize
 *
 * An uninitialized device requires no action. If turning off the display or
 * deinitializing the driver fails, the device state is left unchanged.
 *
 * @retval: EDAL_STATUS_OK on success,
 *          otherwise an error code.
 */
EDAL_Status_t LCD_DeInit(LCD_Device_t *device)
{
    EDAL_Status_t status;

    if (!LCD_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state == EDAL_DEVICE_UNINITIALIZED) {
        return EDAL_STATUS_OK;
    }

    status = device->drv->DisplayOff(device->context);
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
 * LCD_DisplayOn - turn on the LCD display
 * @device: LCD device instance
 *
 * @retval: EDAL_STATUS_OK on success,
 *          EDAL_STATUS_NOT_READY if the device is not initialized,
 *          otherwise an error code.
 */
EDAL_Status_t LCD_DisplayOn(LCD_Device_t *device)
{
    if (!LCD_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state != EDAL_DEVICE_READY) {
        return EDAL_STATUS_NOT_READY;
    }
    return device->drv->DisplayOn(device->context);
}

/**
 * LCD_DisplayOff - turn off the display without deinitializing the device
 * @device: LCD device instance
 *
 * @retval: EDAL_STATUS_OK on success,
 *          EDAL_STATUS_NOT_READY if the device is not initialized,
 *          otherwise an error code.
 */
EDAL_Status_t LCD_DisplayOff(LCD_Device_t *device)
{
    if (!LCD_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state != EDAL_DEVICE_READY) {
        return EDAL_STATUS_NOT_READY;
    }
    return device->drv->DisplayOff(device->context);
}

/**
 * LCD_SetDirection - set the LCD display direction
 * @device: LCD device instance
 * @direction: direction value defined and validated by the driver
 *
 * @retval: EDAL_STATUS_OK on success,
 *          EDAL_STATUS_NOT_READY if the device is not initialized,
 *          otherwise an error code.
 */
EDAL_Status_t LCD_SetDirection(LCD_Device_t *device, uint8_t direction)
{
    if (!LCD_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state != EDAL_DEVICE_READY) {
        return EDAL_STATUS_NOT_READY;
    }
    return device->drv->SetDirection(device->context, direction);
}

/**
 * LCD_SetBacklight - set the LCD backlight brightness
 * @device: LCD device instance
 * @brightness: brightness level defined and validated by the driver
 *
 * @retval: EDAL_STATUS_OK on success,
 *          EDAL_STATUS_NOT_READY if the device is not initialized,
 *          otherwise an error code.
 */
EDAL_Status_t LCD_SetBacklight(LCD_Device_t *device, uint8_t brightness)
{
    if (!LCD_Device_IsValid(device)) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state != EDAL_DEVICE_READY) {
        return EDAL_STATUS_NOT_READY;
    }
    return device->drv->SetBacklight(device->context, brightness);
}

/**
 * LCD_DisplayClear - fill the LCD display with a color
 * @device: LCD device instance
 * @color: non-NULL color data in the format required by the driver
 *
 * @retval: EDAL_STATUS_OK on success,
 *          EDAL_STATUS_INVALID_ARG for an invalid device or NULL color,
 *          EDAL_STATUS_NOT_READY if the device is not initialized,
 *          otherwise an error code from the driver.
 */
EDAL_Status_t LCD_DisplayClear(LCD_Device_t *device, void *color)
{
    if (!LCD_Device_IsValid(device) || color == NULL) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state != EDAL_DEVICE_READY) {
        return EDAL_STATUS_NOT_READY;
    }
    return device->drv->DisplayClear(device->context, color);
}

/**
 * LCD_DisplayDraw - draw color data in an LCD region
 * @device: LCD device instance
 * @x_start: starting horizontal coordinate, no greater than x_end
 * @y_start: starting vertical coordinate, no greater than y_end
 * @x_end: ending horizontal coordinate
 * @y_end: ending vertical coordinate
 * @color: non-NULL color data in the format and size required by the driver
 *
 * The driver defines whether end coordinates are inclusive and validates the
 * region against the current display dimensions.
 *
 * @retval: EDAL_STATUS_OK on success,
 *          EDAL_STATUS_INVALID_ARG for an invalid device, NULL color or
 *          reversed coordinates,
 *          EDAL_STATUS_NOT_READY if the device is not initialized,
 *          otherwise an error code from the driver.
 */
EDAL_Status_t LCD_DisplayDraw(LCD_Device_t *device, uint16_t x_start,
                                                     uint16_t y_start, 
                                                     uint16_t x_end, 
                                                     uint16_t y_end,
                                                     void *color)
{
    if (   !LCD_Device_IsValid(device) || color == NULL
        || x_start > x_end || y_start > y_end) {
        return EDAL_STATUS_INVALID_ARG;
    }
    if (device->state != EDAL_DEVICE_READY) {
        return EDAL_STATUS_NOT_READY;
    }
    return device->drv->DisplayDraw(device->context, x_start, y_start,
                                    x_end, y_end, color);
}

/*============================ END ===========================================*/
