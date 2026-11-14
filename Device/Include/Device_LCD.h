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

#ifndef __DEVICE_LCD_H__
#define __DEVICE_LCD_H__

/*============================ INCLUDES ======================================*/
#include "EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_LCD_API_VERSION    EDAL_VERSION_MAJOR_MINOR(1, 0)  /* API version */

#define _EDAL_Device_LCD_(n)          Device_LCD##n
#define  EDAL_Device_LCD_(n)    _EDAL_Device_LCD_(n)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/**
 * \brief LCD Information
 */
typedef struct _EDAL_LCD_INFO {
    uint32_t width;
    uint32_t height;
    uint32_t id;
    uint32_t Orientation;
    uint32_t scan_direction;
    uint32_t pixel_format;
    uint32_t reserved;
} EDAL_LCD_INFO;

/**
 * \brief LCD Status
 */
typedef struct _EDAL_LCD_STATUS {
    uint32_t busy     : 1;          //!< Operation in progress
    uint32_t error    : 1;          //!< Operation execution failed
    uint32_t reserved : 30;         //!< Reserved (must be zero)
} EDAL_LCD_STATUS;


// Function documentation
/**
 * \fn          EDAL_VERSION EDAL_LCD_GetVersion (void)
 * \brief       Get device version.
 * \return      \ref EDAL_VERSION
 * 
 * \fn          EDAL_LCD_CAPABILITIES EDAL_LCD_GetCapabilities (void)
 * \brief       Get device capabilities.
 * \return      \ref EDAL_LCD_CAPABILITIES
 * 
 * \fn          int32_t EDAL_LCD_Initialize (EDAL_LCD_SignalEvent_t cb_event)
 * \brief       Initialize LCD Interface.
 * \param[in]   cb_event  Pointer to \ref EDAL_LCD_SignalEvent
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_LCD_Uninitialize (void)
 * \brief       De-initialize LCD Interface.
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_LCD_PowerControl (EDAL_POWER_STATE state)
 * \brief       Control LCD Interface Power.
 * \param[in]   state  Power state
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_LCD_SendCommand (uint32_t cmd)
 * \brief       Send Command to LCD device.
 * \param[in]   cmd  Command
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_LCD_WriteData (const void *data, uint32_t num_bytes)
 * \brief       Write data to LCD device.
 * \param[in]   data       Pointer to buffer with data to write to LCD device
 * \param[in]   num_bytes  Number of bytes to write to the LCD device
 * \return      number of data items written or \ref execution_status
 * 
 * \fn          int32_t EDAL_LCD_ReadData (void *data, uint32_t num_bytes)
 * \brief       Read data from LCD device.
 * \param[out]  data       Pointer to buffer for data to read from LCD device
 * \param[in]   num_bytes  Number of bytess to read from the LCD device
 * \return      number of data items read or \ref execution_status
 * 
 * \fn          int32_t EDAL_LCD_Control (uint32_t control, uint32_t arg)
 * \brief       Control LCD Interface.
 * \param[in]   control  Operation
 * \param[in]   arg      Argument of operation (optional)
 * \return      common \ref execution_status and device specific \ref lcd_execution_status
 * 
 * \fn          EDAL_LCD_INFO EDAL_LCD_GetInfo (void)
 * \brief       Get LCD Information.
 * \return      LCD Info \ref EDAL_LCD_INFO
 * 
 * \fn          EDAL_LCD_STATUS EDAL_LCD_GetStatus (void)
 * \brief       Get LCD status.
 * \return      LCD status \ref EDAL_LCD_STATUS
 * 
 * \fn          void EDAL_LCD_SignalEvent (uint32_t event)
 * \brief       Signal LCD Events.
 * \param[in]   event \ref LCD_events notification mask
 */

typedef void (*EDAL_LCD_SignalEvent_t) (uint32_t event);


/**
 * \brief LCD Device Capabilities. 
 */
typedef struct _EDAL_LCD_CAPABILITIES {
    uint32_t read_register   : 1;       //!< Controller register/status readback
    uint32_t read_gram       : 1;       //!< Display memory readback
    uint32_t rotation_mask   : 4;       //!< Supported rotations: 0/90/180/270
    uint32_t mirror_x        : 1;       //!< Horizontal mirroring
    uint32_t mirror_y        : 1;       //!< Vertical mirroring
    uint32_t write_rgb565    : 1;       //!< RGB565 pixel input
    uint32_t write_rgb666    : 1;       //!< RGB666 pixel input
    uint32_t write_rgb888    : 1;       //!< RGB888 pixel input
    uint32_t vertical_scroll : 1;       //!< Controller-based vertical scrolling
    uint32_t partial_display : 1;       //!< Partial display mode
    uint32_t inversion       : 1;       //!< Display color inversion control
    uint32_t event_te        : 1;       //!< Tearing-effect synchronization event
    uint32_t reserved        : 17;      //!< Reserved (must be zero)
} EDAL_LCD_CAPABILITIES;


/**
 * \brief Access structure of the LCD Device.
 */
typedef struct _EDAL_DEVICE_LCD {
    EDAL_VERSION            (*GetVersion)       (void);
    EDAL_LCD_CAPABILITIES   (*GetCapabilities)  (void);
    int32_t                 (*Initialize)       (EDAL_LCD_SignalEvent_t cb_event);
    int32_t                 (*Uninitialize)     (void);
    int32_t                 (*PowerControl)     (EDAL_POWER_STATE state);
    int32_t                 (*SendCommand)      (uint32_t cmd);
    int32_t                 (*WriteData)        (const void *data, uint32_t num_bytes);
    int32_t                 (*ReadData)         (      void *data, uint32_t num_bytes);
    int32_t                 (*Control)          (uint32_t control, uint32_t arg);
    EDAL_LCD_INFO           (*GetInfo)          (void);
    EDAL_LCD_STATUS         (*GetStatus)        (void);
} const EDAL_DEVICE_LCD;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DEVICE_LCD_H__ */
