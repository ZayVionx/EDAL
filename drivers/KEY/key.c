/*============================ INCLUDES ======================================*/
#include "key.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/** Initialize the key0 driver.
  * @return EDAL_STATUS_OK on success.
  *         otherwise an error code.
  */
EDAL_Status_t key0_drv_init(void)
{

    return EDAL_STATUS_OK;
}

EDAL_Status_t key0_drv_deinit(void)
{
    
    return EDAL_STATUS_OK;
}

uint8_t key0_drv_get_value(void)
{
    
    return EDAL_STATUS_OK;
}

EDAL_Status_t key0_drv_add_event(uint8_t chKeyID, uint8_t chEventMask)
{
    
    return EDAL_STATUS_OK;
}

EDAL_Status_t key0_drv_remote_event(uint8_t chKeyID, uint8_t chEventMask)
{
    
    return EDAL_STATUS_OK;
}

static Key_DrvType_t key_ops[KEY_DRV_NUM] = {
    [0] = {
        .Init        = key0_drv_init,
        .DeInit      = key0_drv_deinit,
        .GetValue    = key0_drv_get_value,
        .AddEvent    = key0_drv_add_event,
        .RemoveEvent = key0_drv_remote_event,
    }
};

/** 
  * @brief Array of beep devices with their respective driver functions.
  */
Key_Device_t key[KEY_DRV_NUM] = {
    [0] = { .drv = &key_ops[0], },
};

/** example usage of the key driver array
  * @code
  * Key_Init(&key[0]);
  * Key_DeInit(&key[0]);
  * uint8_t value = Key_Get_Value(&key[0]);
  * Key_Add_Event(&key[0], 1, 长按掩码);
  * Key_Remove_Event(&key[0], 1, 长按掩码);
  * @endcode
  */

/*============================ END ===========================================*/
