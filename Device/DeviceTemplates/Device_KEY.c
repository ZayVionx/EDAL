/****************************************************************************
*  Copyright 2026 ZJY <Email:zhujinyuan818@gmail.com>                       *
*                                                                           *
*  Licensed under the Apache License, Version 2.0 (the "License");          *
*  you may not use this file except in compliance with the License.         *
*  You may obtain a copy of the License at                                  *
*                                                                           *
*     http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                           *
*
*  Unless required by applicable law or agreed to in writing, software      *
*  distributed under the License is distributed on an "AS IS" BASIS,        *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
*  See the License for the specific language governing permissions and      *
*  limitations under the License.                                           *
*                                                                           *
****************************************************************************/

/*============================ INCLUDES ======================================*/
#include "Device_KEY.h"

/*============================ MACROS ========================================*/
#define EDAL_KEY_DRV_VERSION    EDAL_VERSION_MAJOR_MINOR(1, 0)  /* driver version */

/*============================ MACROFIED FUNCTIONS ===========================*/

#if 0   /* USER: change to 1 to enable this block */

/*----------------------------------------------------------------------------
 *                             USER CONFIGURATION   
 *----------------------------------------------------------------------------*/

 /* USER: set the total number of keys. */
#define EDAL_KEY_COUNT                      ( 2 )

/* USER: configure one GPIO port and pin for each key. */
#define EDAL_KEY0_GPIO_PORT                 ( NULL )
#define EDAL_KEY0_GPIO_PIN                  ( NULL )

#define EDAL_KEY1_GPIO_PORT                 ( NULL )
#define EDAL_KEY1_GPIO_PIN                  ( NULL )

/* USER: replace this with the platform GPIO input function. */
#define EDAL_KEY_GPIO_ReadInputDataBit      ( NULL )

/*----------------------------------------------------------------------------
 *                             USER CONFIGURATION 
 *----------------------------------------------------------------------------*/

 /* Do not modify this section. */
#define EDAL_KEY_DEFINE_LEVEL_READ(n)                                           \
    static bool EDAL_KEY##n##_ReadLevel(void)                                   \
    {                                                                           \
        return (EDAL_KEY_GPIO_ReadInputDataBit( EDAL_KEY##n##_GPIO_PORT,        \
                                                EDAL_KEY##n##_GPIO_PIN   ));    \
    }

/* USER: add one line for each key, in ascending order. */
EDAL_KEY_DEFINE_LEVEL_READ(0)
EDAL_KEY_DEFINE_LEVEL_READ(1)

#undef EDAL_KEY_DEFINE_LEVEL_READ

/* USER: add one reader for each key, using the same order. */
static bool (*const edal_key_get_level[])(void) = {
    EDAL_KEY0_ReadLevel,
    EDAL_KEY1_ReadLevel,
};

#endif

/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/* Device Version */
static const EDAL_VERSION DeviceVersion = {
    EDAL_KEY_API_VERSION,
    EDAL_KEY_DRV_VERSION
};

/* Device Capabilities */
static const EDAL_KEY_CAPABILITIES DeviceCapabilities = {
    0,  /* Supports key press events */
    0,  /* Supports key release events */
    0,  /* Supports single-click events */
    0,  /* Supports double-click events */
    0,  /* Supports long-press events */
    0,  /* Supports release events after a long press */
    0,  /* Supports periodic repeat events while held after a long press */
    0,  /* Supports key debouncing */
    0,  /* Supports runtime configuration of recognition timing */
    0,  /* Supports wakeup from EDAL_POWER_LOW */
    0   /* Reserved (must be zero) */
};

/*============================ IMPLEMENTATION ================================*/
static EDAL_VERSION EDAL_KEY_GetVersion(void)
{
    return DeviceVersion;
}

static EDAL_KEY_CAPABILITIES EDAL_KEY_GetCapabilities(void)
{
    return DeviceCapabilities;
}

static int32_t EDAL_KEY_Initialize(EDAL_KEY_SignalEvent_t cb_event)
{
}

static int32_t EDAL_KEY_Uninitialize(void)
{
}

static int32_t EDAL_KEY_PowerControl(EDAL_POWER_STATE state)
{
    switch(state)
    {
        case EDAL_POWER_FULL:
            break;

        case EDAL_POWER_LOW:
            break;

        case EDAL_POWER_OFF:
            break;
    }
    return EDAL_DEVICE_OK;
}

static int32_t EDAL_KEY_Control(uint32_t id, uint32_t control, uint32_t arg)
{
    switch(control)
    {
        /* SET TIME */
        case EDAL_KEY_SET_DEBOUNCE_TIME:
            break;

        case EDAL_KEY_SET_DOUBLE_CLICK_TIME:
            break;

        case EDAL_KEY_SET_LONG_PRESS_TIME:
            break;

        case EDAL_KEY_SET_REPEAT_PERIOD:
            break;

        /* SET EVENT */
        case EDAL_KEY_ADD_EVENT_MASK:
            break;

        case EDAL_KEY_DEL_EVENT_MASK:
            break;
    }
}

static EDAL_KEY_STATUS EDAL_KEY_GetStatus(void)
{
}

void EDAL_KEY_SignalEvent(uint32_t event)
{
}

/*============================ PROTOTYPES ====================================*/
extern 
EDAL_DEVICE_KEY EDAL_Device_KEY_(0);
EDAL_DEVICE_KEY EDAL_Device_KEY_(0) = {
    EDAL_KEY_GetVersion,
    EDAL_KEY_GetCapabilities,
    EDAL_KEY_Initialize,
    EDAL_KEY_Uninitialize,
    EDAL_KEY_PowerControl,
    EDAL_KEY_Control,
    EDAL_KEY_GetStatus
};

/*============================ END ===========================================*/
