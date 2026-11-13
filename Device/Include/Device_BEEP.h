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

#ifndef __DEVICE_BEEP_H__
#define __DEVICE_BEEP_H__

/*============================ INCLUDES ======================================*/
#include "EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
#define EDAL_BEEP_API_VERSION   EDAL_VERSION_MAJOR_MINOR(0, 0)  /* API version */

#define _EDAL_Device_BEEP_(n)         Device_BEEP##n
#define  EDAL_Device_BEEP_(n)   _EDAL_Device_BEEP_(n)


/******  BEEP Control Codes *****/

#define EDAL_BEEP_CONTROL_Pos                0
#define EDAL_BEEP_CONTROL_Msk               (0xFFUL << EDAL_BEEP_CONTROL_Pos)

/*-----  BEEP Control Codes: Tone -----*/
#define EDAL_BEEP_TONE_INACTIVE             (0x00UL << EDAL_BEEP_CONTROL_Pos)
#define EDAL_BEEP_TONE_FREQUENCY            (0x01UL << EDAL_BEEP_CONTROL_Pos)
#define EDAL_BEEP_TONE_VOLUME               (0x02UL << EDAL_BEEP_CONTROL_Pos)
#define EDAL_BEEP_TONE_DUTY_CYCLE           (0x03UL << EDAL_BEEP_CONTROL_Pos)
#define EDAL_BEEP_TONE_INTERVAL             (0x04UL << EDAL_BEEP_CONTROL_Pos)

/*-----  BEEP Control Codes: Tone Parameters: Frequency -----*/
#define EDAL_BEEP_FREQUENCY_Pos              8
#define EDAL_BEEP_FREQUENCY_Msk             (3UL << EDAL_BEEP_FREQUENCY_Pos)
#define EDAL_BEEP_FREQUENCY_SET             (0UL << EDAL_BEEP_FREQUENCY_Pos)
#define EDAL_BEEP_FREQUENCY_GET_MIN         (1UL << EDAL_BEEP_FREQUENCY_Pos)
#define EDAL_BEEP_FREQUENCY_GET_MAX         (2UL << EDAL_BEEP_FREQUENCY_Pos)

/*-----  BEEP Control Codes: Tone Parameters: Volume -----*/
#define EDAL_BEEP_VOLUME_Pos                 10
#define EDAL_BEEP_VOLUME_Msk                (3UL << EDAL_BEEP_VOLUME_Pos)
#define EDAL_BEEP_VOLUME_SET                (0UL << EDAL_BEEP_VOLUME_Pos)
#define EDAL_BEEP_VOLUME_GET_MIN            (1UL << EDAL_BEEP_VOLUME_Pos)
#define EDAL_BEEP_VOLUME_GET_MAX            (2UL << EDAL_BEEP_VOLUME_Pos)

/*-----  BEEP Control Codes: Tone Parameters: Duty Cycle -----*/
#define EDAL_BEEP_DUTY_CYCLE_Pos             12
#define EDAL_BEEP_DUTY_CYCLE_Msk            (3UL << EDAL_BEEP_DUTY_CYCLE_Pos)
#define EDAL_BEEP_DUTY_CYCLE_SET            (0UL << EDAL_BEEP_DUTY_CYCLE_Pos)
#define EDAL_BEEP_DUTY_CYCLE_GET_MIN        (1UL << EDAL_BEEP_DUTY_CYCLE_Pos)
#define EDAL_BEEP_DUTY_CYCLE_GET_MAX        (2UL << EDAL_BEEP_DUTY_CYCLE_Pos)

/*-----  BEEP Control Codes: Tone Parameters: Interval -----*/
#define EDAL_BEEP_INTERVAL_Pos               14
#define EDAL_BEEP_INTERVAL_Msk              (3UL << EDAL_BEEP_INTERVAL_Pos)
#define EDAL_BEEP_INTERVAL_SET              (0UL << EDAL_BEEP_INTERVAL_Pos)
#define EDAL_BEEP_INTERVAL_GET_MIN          (1UL << EDAL_BEEP_INTERVAL_Pos)
#define EDAL_BEEP_INTERVAL_GET_MAX          (2UL << EDAL_BEEP_INTERVAL_Pos)


/****** BEEP specific error codes *****/
#define EDAL_BEEP_ERROR_TONE                (EDAL_DEVICE_ERROR_SPECIFIC - 1)
#define EDAL_BEEP_ERROR_FREQUENCY           (EDAL_DEVICE_ERROR_SPECIFIC - 2)
#define EDAL_BEEP_ERROR_VOLUME              (EDAL_DEVICE_ERROR_SPECIFIC - 3)
#define EDAL_BEEP_ERROR_DUTY_CYCLE          (EDAL_DEVICE_ERROR_SPECIFIC - 4)
#define EDAL_BEEP_ERROR_INTERVAL            (EDAL_DEVICE_ERROR_SPECIFIC - 5)

/****** BEEP Event *****/
#define EDAL_BEEP_EVENT_BEEP_COMPLETE       (1UL << 0)
#define EDAL_BEEP_EVENT_PATTERN_COMPLETE    (1UL << 1)
#define EDAL_BEEP_EVENT_MELODY_COMPLETE     (1UL << 2)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/**
 * \brief BEEP Status
 */
typedef struct _EDAL_BEEP_STATUS {
    uint32_t active   : 1;          //!< Is making a sound
    uint32_t busy     : 1;          //!< Currently playing (pattern/melody)
    uint32_t channel  : 4;          //!< 
    uint32_t reserved : 26;         //!< 
} EDAL_BEEP_STATUS;

typedef void (*EDAL_BEEP_SignalEvent_t) (uint32_t event);


/**
 * \brief BEEP Device Capabilities. 
 */
typedef struct _EDAL_BEEP_CAPABILITIES {
    uint32_t hw_pwm      : 1;       //!< driven by hardware PWM
    uint32_t freq_ctrl   : 1;       //!< support setting the chirping frequency
    uint32_t volume      : 1;       //!< support duty cycle/volume adjustment
    uint32_t pattern     : 1;       //!< supports automatic sound-stop rhythm driving
    uint32_t melody      : 1;       //!< support sequential playback of frequencies
    uint32_t channel_num : 2;       //!< number of channels (0 indicates a single channel)
    uint32_t reserved    : 25;      //!< Reserved (must be zero)
} EDAL_BEEP_CAPABILITIES;


/**
 * \brief Access structure of the BEEP Device.
 */
typedef struct _EDAL_DEVICE_BEEP {
    EDAL_VERSION            (*GetVersion)       (void);
    EDAL_BEEP_CAPABILITIES  (*GetCapabilities)  (void);
    int32_t                 (*Initialize)       (EDAL_BEEP_SignalEvent_t cb_event);
    int32_t                 (*Uninitialize)     (void);
    int32_t                 (*PowerControl)     (EDAL_POWER_STATE state);
    int32_t                 (*Play)             (uint32_t count, uint32_t ms);
    int32_t                 (*Control)          (uint32_t control, uint32_t arg);
    EDAL_BEEP_STATUS        (*GetStatus)        (void);
} const EDAL_DEVICE_BEEP;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DEVICE_BEEP_H__ */
