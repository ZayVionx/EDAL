/*============================ INCLUDES ======================================*/
#include "beep_drv.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/** Initialize the beep0 driver.
  * @return EDAL_STATUS_OK on success.
  *         otherwise an error code.
  */
EDAL_Status_t beep0_drv_init(void *context)
{

    return EDAL_STATUS_OK;
}

EDAL_Status_t beep0_drv_deinit(void *context)
{
    
    return EDAL_STATUS_OK;
}

EDAL_Status_t beep0_drv_play(void *context, uint32_t count, uint32_t duration_ms)
{
    
    return EDAL_STATUS_OK;
}

EDAL_Status_t beep0_drv_stop(void *context)
{
    
    return EDAL_STATUS_OK;
}

EDAL_Status_t beep0_drv_set_vol(void *context, uint32_t volume)
{
    
    return EDAL_STATUS_OK;
}

uint32_t beep0_drv_get_vol(void *context)
{
    
    return 0;
}       

static Beep_DrvType_t beep_ops[BEEP_DRV_NUM] = {
    [0] = {
        .Init   = beep0_drv_init,
        .DeInit = beep0_drv_deinit,
        .Play   = beep0_drv_play,
        .Stop   = beep0_drv_stop,
        .SetVol = beep0_drv_set_vol,
        .GetVol = beep0_drv_get_vol,
    },
};

/** 
  * @brief Array of beep devices with their respective driver functions.
  */
Beep_Device_t beep_dev[BEEP_DRV_NUM] = {
    [0] = { .drv = &beep_ops[0], },
};

/** example usage of the beep driver array
  * @code
  * Beep_Init(&beep_dev[0]);
  * Beep_Play(&beep_dev[0], 1, 100); // Request three beeps, 100 ms each
  * Beep_Stop(&beep_dev[0]);
  * Beep_DeInit(&beep_dev[0]);
  * @endcode
  */

/*============================ END ===========================================*/
