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

static int32_t EDAL_KEY_Control(uint32_t control, uint32_t arg)
{
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
