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
#include "Device_LCD.h"

/*============================ MACROS ========================================*/
#define EDAL_LCD_DRV_VERSION    EDAL_VERSION_MAJOR_MINOR(1, 0)  /* driver version */


/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/* Device Version */
static const EDAL_VERSION DeviceVersion = {
    EDAL_LCD_API_VERSION,
    EDAL_LCD_DRV_VERSION
};

/* LCD Information */
static EDAL_LCD_INFO DeviceInfo = {
    0,  /* screen width  */
    0,  /* screen height */
    0,  /* IC model */
    0,  /* screen orientation */
    0,  /* Scanning direction */
    0,  /* Pixel format */
    0   /* Reserved (must be zero) */
};

/* Device Capabilities */
static const EDAL_LCD_CAPABILITIES DeviceCapabilities = {
    0,  /* Controller register/status readback */
    0,  /* Display memory readback */
    0,  /* Supported rotations: 0/90/180/270 */
    0,  /* Horizontal mirroring */
    0,  /* Vertical mirroring */
    0,  /* RGB565 pixel input */
    0,  /* RGB666 pixel input */
    0,  /* RGB888 pixel input */
    0,  /* Controller-based vertical scrolling */
    0,  /* Partial display mode */
    0,  /* Display color inversion control */
    0,  /* Tearing-effect synchronization event */
    0   /* Reserved (must be zero) */
};

/*============================ IMPLEMENTATION ================================*/
static EDAL_VERSION EDAL_LCD_GetVersion(void)
{
    return DeviceVersion;
}

static EDAL_LCD_CAPABILITIES EDAL_LCD_GetCapabilities(void)
{
    return DeviceCapabilities;
}

static int32_t EDAL_LCD_Initialize(EDAL_LCD_SignalEvent_t cb_event)
{
}

static int32_t EDAL_LCD_Uninitialize(void)
{
}

static int32_t EDAL_LCD_PowerControl(EDAL_POWER_STATE state)
{
    switch(state)
    {
        case EDAL_POWER_OFF:
            break;

        case EDAL_POWER_LOW:
            break;

        case EDAL_POWER_FULL:
            break;
    }
    return EDAL_DEVICE_OK;
}

static int32_t EDAL_LCD_SendCommand(uint32_t cmd)
{
}

static int32_t EDAL_LCD_WriteData(const void *data, uint32_t num_bytes)
{
}

static int32_t EDAL_LCD_ReadData(void *data, uint32_t num_bytes)
{
}

static int32_t EDAL_LCD_Control(uint32_t control, uint32_t arg)
{
}

static EDAL_LCD_INFO EDAL_LCD_GetInfo(void)
{
    return DeviceInfo;
}

static EDAL_LCD_STATUS EDAL_LCD_GetStatus(void)
{
}

static void EDAL_LCD_SignalEvent(uint32_t event)
{
    // function body
}

/*============================ PROTOTYPES ====================================*/
extern EDAL_DEVICE_LCD EDAL_Device_LCD_(0);
EDAL_DEVICE_LCD EDAL_Device_LCD_(0) = {
    EDAL_LCD_GetVersion,
    EDAL_LCD_GetCapabilities,
    EDAL_LCD_Initialize,
    EDAL_LCD_Uninitialize,
    EDAL_LCD_PowerControl,
    EDAL_LCD_SendCommand,
    EDAL_LCD_WriteData,
    EDAL_LCD_ReadData,
    EDAL_LCD_Control,
    EDAL_LCD_GetInfo,
    EDAL_LCD_GetStatus,
};

/*============================ END ===========================================*/
