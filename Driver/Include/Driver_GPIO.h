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

#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__

/*============================ INCLUDES ======================================*/
#include "../../EDAL_Common.h"

#ifdef   __cplusplus
extern "C" {
#endif
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/**
 * \brief GPIO Pin
 */
typedef uint32_t EDAL_GPIO_Pin_t;

/**
 * \brief GPIO Direction
 */
typedef enum {
    EDAL_GPIO_INPUT,                    //!< Input
    EDAL_GPIO_OUTPUT                    //!< Output
} EDAL_GPIO_DIRECTION;

/**
 * \brief GPIO Output Mode
 */
typedef enum {
    EDAL_GPIO_PUSH_PULL,                //!< Push-pull
    EDAL_GPIO_OPEN_DRAIN                //!< Open-drain
} EDAL_GPIO_OUTPUT_MODE;

/**
 * \brief GPIO Pull Resistor
 */
typedef enum {
    EDAL_GPIO_PULL_NONE,                //!< None
    EDAL_GPIO_PULL_UP,                  //!< Pull-up
    EDAL_GPIO_PULL_DOWN                 //!< Pull-down
} EDAL_GPIO_PULL_RESISTOR;

/**
 * \brief GPIO Event Trigger
 */
typedef enum {
    EDAL_GPIO_TRIGGER_NONE,             //!< None
    EDAL_GPIO_TRIGGER_RISING_EDGE,      //!< Rising-edge
    EDAL_GPIO_TRIGGER_FALLING_EDGE,     //!< Falling-edge
    EDAL_GPIO_TRIGGER_EITHER_EDGE       //!< Either edge (rising and falling)
} EDAL_GPIO_EVENT_TRIGGER;

#define EDAL_GPIO_EVENT_RISING_EDGE     (1UL << 0)
#define EDAL_GPIO_EVENT_FALLING_EDGE    (1UL << 1)
#define EDAL_GPIO_EVENT_EITHER_EDGE     (1UL << 2)


/****** GPIO specific error codes *****/
#define EDAL_GPIO_ERROR_PIN             (EDAL_DRIVER_ERROR_SPECIFIC - 1) //!< Specified Pin not available 


/****** Pointer to EDAL_GPIO_SignalEvent : Signal GPIO Event *****/
typedef void (*EDAL_GPIO_SignalEvent_t)(EDAL_GPIO_Pin_t pin, uint32_t event);



/**
 * \brief Access structure of the GPIO Driver.
 */
typedef struct _EDAL_DRIVER_GPIO {
    int32_t  (*Setup)           (EDAL_GPIO_Pin_t pin, EDAL_GPIO_SignalEvent_t cb_event);
    int32_t  (*SetDirection)    (EDAL_GPIO_Pin_t pin, EDAL_GPIO_DIRECTION direction);
    int32_t  (*SetOutputMode)   (EDAL_GPIO_Pin_t pin, EDAL_GPIO_OUTPUT_MODE mode);
    int32_t  (*SetPullResistor) (EDAL_GPIO_Pin_t pin, EDAL_GPIO_PULL_RESISTOR resistor);
    int32_t  (*SerEventTrigger) (EDAL_GPIO_Pin_t pin, EDAL_GPIO_EVENT_TRIGGER trigger);
    void     (*SetOutput)       (EDAL_GPIO_Pin_t pin, uint32_t val);
    uint32_t (*SetInput)        (EDAL_GPIO_Pin_t pin);
} EDAL_DRIVER_GPIO;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*============================ END ===========================================*/
#ifdef   __cplusplus
}
#endif
#endif /* __DRIVER_GPIO_H__ */
