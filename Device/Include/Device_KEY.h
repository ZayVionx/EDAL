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
#include "../../EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_KEY_API_VERSION    EDAL_VERSION_MAJOR_MINOR(1, 0)  /* API version */


#define _EDAL_Device_KEY_(n)          Device_KEY##n
#define  EDAL_Device_KEY_(n)    _EDAL_Device_KEY_(n)


/****** KEY Control Codes *****/


/****** KEY specific error codes *****/


/****** KEY Event *****/


/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

typedef struct _EDAL_KEY_STATUSS {

    uint32_t reserved : 32;     //!< Reserved (must be zero)
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

    uint32_t reserved : 32;     //!< Reserved (must be zero)
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
    int32_t                 (*Control)          (uint32_t control, uint32_t arg);
    EDAL_KEY_STATUS         (*GetStatus)        (void)
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
