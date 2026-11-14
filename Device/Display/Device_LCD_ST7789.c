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
#include "Device_LCD_Generic.h"

/*============================ MACROS ========================================*/
#define EDAL_LCD_DRV_VERSION    EDAL_VERSION_MAJOR_MINOR(1, 0)  /* driver version */


#define CMD_FRMCTR1     0xB1
#define CMD_FRMCTR2     0xB2
#define CMD_FRMCTR3     0xB3
#define CMD_INVCTR      0xB4
#define CMD_DFUNCTR     0xB6
#define CMD_ETMOD       0xB7
#define CMD_PWCTR1      0xC0
#define CMD_PWCTR2      0xC1
#define CMD_PWCTR3      0xC2
#define CMD_PWCTR4      0xC3
#define CMD_PWCTR5      0xC4
#define CMD_VMCTR       0xC5
#define CMD_GMCTRP1     0xE0
#define CMD_GMCTRN1     0xE1
#define CMD_DOCA        0xE8
#define CMD_CSCON       0xF0

#define CMD_RAMCTRL     0xB0
#define CMD_PORCTRL     0xB2    /* Porch control */
#define CMD_GCTRL       0xB7    /* Gate control */
#define CMD_VCOMS       0xBB    /* VCOMS setting */
#define CMD_LCMCTRL     0xC0    /* LCM control */
#define CMD_VDVVRHEN    0xC2    /* VDV and VRH command enable */
#define CMD_VRHS        0xC3    /* VRH set */
#define CMD_VDVSET      0xC4    /* VDV setting */
#define CMD_FRCTR2      0xC6    /* FR Control 2 */
#define CMD_PWCTRL1     0xD0    /* Power control 1 */
#define CMD_PVGAMCTRL   0xE0    /* Positive Gamma Correction */
#define CMD_NVGAMCTRL   0xE1    /* Negative Gamma Correction */

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
    0,      /* screen width  */
    0,      /* screen height */
    0x7789, /* IC model */
    0,      /* screen orientation */
    0,      /* Scanning direction */
    0,      /* Pixel format */
    0       /* Reserved (must be zero) */
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

/* init commands based on LovyanGFX ST7789 driver */
static const uint8_t init_cmd_list[] = {
    CMD_GCTRL,      1,  0x44,       /* GCTRL -- panel dependent */
    CMD_VCOMS,      1,  0x24,       /* VCOMS -- panel dependent */
    CMD_VRHS,       1,  0x13,       /* VRHS  -- panel dependent */
    CMD_PWCTRL1,    2,  0xa4, 0xa1,
    CMD_RAMCTRL,    2,  0x00, 0xC0, /* controls mapping of RGB565 to RGB666 */
    CMD_PVGAMCTRL,  14, 0xd0, 0x00, 0x02, 0x07, 0x0a, 0x28, 0x32, 0x44, 0x42, 0x06, 0x0e, 0x12, 0x14, 0x17,
    CMD_NVGAMCTRL,  14, 0xd0, 0x00, 0x02, 0x07, 0x0a, 0x28, 0x31, 0x54, 0x47, 0x0e, 0x1c, 0x17, 0x1b, 0x1e,
    EDAL_LCD_CMD_SET_GAMMA_CURVE, 1, 0x01,
    EDAL_LCD_CMD_DELAY_MS, EDAL_LCD_CMD_EOF
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
