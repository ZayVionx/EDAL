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

#ifndef __DEVICE_KEY_H__
#define __DEVICE_KEY_H__

/*============================ INCLUDES ======================================*/
#include "EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_KEY_API_VERSION    EDAL_VERSION_MAJOR_MINOR(1, 0)  /* API version */


#define _EDAL_Device_KEY_(n)          Device_KEY##n
#define  EDAL_Device_KEY_(n)    _EDAL_Device_KEY_(n)


/****** KEY Control Codes *****/

#define EDAL_KEY_CONTROL_Pos                 0
#define EDAL_KEY_CONTROL_Msk                (0xFFUL << EDAL_KEY_CONTROL_Pos)

/*----- KEY Control Codes: Event Notification and Wakeup -----*/
#define EDAL_KEY_ADD_EVENT_MASK             (0x01UL << EDAL_KEY_CONTROL_Pos) //!< arg = callback event mask; 0 disables callbacks only
#define EDAL_KEY_DEL_EVENT_MASK             (0x02UL << EDAL_KEY_CONTROL_Pos) //!< arg = callback event mask; 0 disables callbacks only
#define EDAL_KEY_CONTROL_WAKEUP             (0x03UL << EDAL_KEY_CONTROL_Pos) //!< arg = EDAL_KEY_DISABLE / EDAL_KEY_ENABLE

/*----- KEY Control Codes: Recognition Timing (milliseconds) -----*/
#define EDAL_KEY_SET_DEBOUNCE_TIME          (0x10UL << EDAL_KEY_CONTROL_Pos) //!< arg = debounce time; 0 disables debounce
#define EDAL_KEY_SET_DOUBLE_CLICK_TIME      (0x11UL << EDAL_KEY_CONTROL_Pos) //!< arg > 0; maximum time from first release to second press
#define EDAL_KEY_SET_LONG_PRESS_TIME        (0x12UL << EDAL_KEY_CONTROL_Pos) //!< arg > 0; time from debounced press to long-press event
#define EDAL_KEY_SET_REPEAT_PERIOD          (0x13UL << EDAL_KEY_CONTROL_Pos) //!< arg > 0; repeat interval after long-press event

/*----- KEY Control Arguments -----*/
#define EDAL_KEY_DISABLE                     0UL
#define EDAL_KEY_ENABLE                      1UL


/****** KEY specific error codes *****/


/****** KEY Event *****/

#define EDAL_KEY_EVENT_PRESS                 (1UL << 0)
#define EDAL_KEY_EVENT_RELEASE               (1UL << 1)
#define EDAL_KEY_EVENT_CLICKED               (1UL << 2)
#define EDAL_KEY_EVENT_DOUBLE_CLICK          (1UL << 3)
#define EDAL_KEY_EVENT_LONG_PRESS            (1UL << 4)
#define EDAL_KEY_EVENT_LONG_PRESS_RELEASE    (1UL << 5)
#define EDAL_KEY_EVENT_LONG_PRESS_REPEAT     (1UL << 6)
#define EDAL_KEY_EVENT_ALL                   (EDAL_KEY_EVENT_PRESS              | \
                                             EDAL_KEY_EVENT_RELEASE            | \
                                             EDAL_KEY_EVENT_CLICKED            | \
                                             EDAL_KEY_EVENT_DOUBLE_CLICK       | \
                                             EDAL_KEY_EVENT_LONG_PRESS         | \
                                             EDAL_KEY_EVENT_LONG_PRESS_RELEASE | \
                                             EDAL_KEY_EVENT_LONG_PRESS_REPEAT)


/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/**
 * \brief KEY status
 */
typedef struct _EDAL_KEY_STATUSS {
    uint32_t key_info : 16;     //!< key id and key value
    uint32_t reserved : 16;     //!< Reserved (must be zero)
} EDAL_KEY_STATUS;


// Function documentation
/**
 * \fn          EDAL_VERSION EDAL_KEY_GetVersion (void)
 * \brief       Get device version.
 * \return      \ref EDAL_VERSION
 * 
 * \fn          EDAL_KEY_CAPABILITIES EDAL_KEY_GetCapabilities (void)
 * \brief       Get device capabilities.
 * \return      \ref EDAL_KEY_CAPABILITIES
 * 
 * \fn          int32_t EDAL_KEY_Initialize (EDAL_KEY_SignalEvent_t cb_event)
 * \brief       Initialize KEY Interface.
 * \param[in]   cb_event  Pointer to \ref EDAL_KEY_SignalEvent
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_KEY_Uninitialize (void)
 * \brief       De-Initialize KEY Interface.
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_KEY_PowerControl (EDAL_POWER_STATE state)
 * \brief       Control KEY Interface Power.
 * \param[in]   state  Power state
 * \return      \ref execution_status
 * 
 * \fn          int32_t EDAL_KEY_Control (uint32_t control, uint32_t arg)
 * \brief       Control KEY Interface.
 * \param[in]   control  Operation  
 * \param[in]   arg      Argument of operation (optional)
 * \return      common \ref execution_status and device specific \ref key_execution_status
 * \note        Control codes are mutually exclusive; reserved control bits must be zero.
 * \note        Initialize enables notification of all events supported by the driver.
 *              SET_EVENT_MASK replaces the callback mask; recognition and status updates continue.
 *              Unknown event bits are invalid; known but unsupported events are not supported.
 *              EDAL_KEY_EVENT_ALL contains all API events, not only those supported by a driver.
 * \note        CONTROL_WAKEUP selects wakeup in EDAL_POWER_LOW independently of the callback mask.
 *              Wakeup is disabled after Initialize; use PowerControl to enter low-power mode.
 * \note        Timing commands require timing_config and the corresponding recognition capability.
 *              SET_DEBOUNCE_TIME requires debounce; repeat uses event_long_press_repeat.
 *              Timing changes during an active press/click recognition sequence return EDAL_DEVICE_ERROR_BUSY.
 * \note        Unsupported commands/features return EDAL_DEVICE_ERROR_UNSUPPORTED;
 *              invalid arguments return EDAL_DEVICE_ERROR_PARAMETER. Failed commands leave settings unchanged.
 * 
 * \fn          EDAL_KEY_STATUS EDAL_KEY_GetStatus (void)
 * \brief       Get KEY status.
 * \return      KEY status \ref EDAL_KEY_STATUS
 * 
 * \fn          void EDAL_KEY_SignalEvent (uint32_t event)
 * \brief       Signal KEY Event.
 * \param[in]   event  \ref KEY_Events notification mask
 * \return      none 
 */

typedef void (*EDAL_KEY_SignalEvent_t) (uint32_t event);



/**
 * \brief KEY Device Capabilities. 
 */
typedef struct _EDAL_KEY_CAPABILITIES {
    uint32_t event_press                : 1;
    uint32_t event_release              : 1;
    uint32_t event_clicked              : 1;
    uint32_t event_double_click         : 1;
    uint32_t event_long_press           : 1;
    uint32_t event_long_press_release   : 1;
    uint32_t event_long_press_repeat    : 1;
    uint32_t debounce                   : 1;
    uint32_t timing_config              : 1;
    uint32_t wakeup                     : 1;
    uint32_t reserved                   : 22;     //!< Reserved (must be zero)
} EDAL_KEY_CAPABILITIES;


/**
 * \brief Access structure of the KEY Driver.
 */
typedef struct _EDAL_DEVICE_KEY {
    EDAL_VERSION            (*GetVersion)       (void);
    EDAL_KEY_CAPABILITIES   (*GetCapabilities)  (void);
    int32_t                 (*Initialize)       (EDAL_KEY_SignalEvent_t cb_event);
    int32_t                 (*Uninitialize)     (void);
    int32_t                 (*PowerControl)     (EDAL_POWER_STATE state);
    int32_t                 (*Control)          (uint32_t id, uint32_t control, uint32_t arg);
    EDAL_KEY_STATUS         (*GetStatus)        (void);
} const EDAL_DEVICE_KEY;


/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DEVICE_KEY_H__ */
