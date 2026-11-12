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
#include "../Include/Driver_GPIO.h"

/*============================ MACROS ========================================*/
#define GPIO_MAX_PINS               (64U)
#define PIN_IS_AVAILABLE(n)         ((n) < GPIO_MAX_PINS)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ IMPLEMENTATION ================================*/

static int32_t GPIO_Setup(EDAL_GPIO_Pin_t pin, EDAL_GPIO_SignalEvent_t cb_event)
{
    int32_t result = EDAL_DRIVER_OK;

    if(!PIN_IS_AVAILABLE(pin))
    {
        result = EDAL_GPIO_ERROR_PIN;
    }

    return result;
}

static int32_t GPIO_SetDirection(EDAL_GPIO_Pin_t pin, EDAL_GPIO_DIRECTION direction)
{
    int32_t result = EDAL_DRIVER_OK;

    if(PIN_IS_AVAILABLE(pin))
    {
        switch(direction)
        {
            case EDAL_GPIO_INPUT:
                break;

            case EDAL_GPIO_OUTPUT:
                break;

            default:
                result = EDAL_DRIVER_ERROR_PARAMETER;
                break;
        }
    }
    else
    {
        result = EDAL_GPIO_ERROR_PIN;
    }

    return result;
}

static int32_t GPIO_SetOutputMode(EDAL_GPIO_Pin_t pin, EDAL_GPIO_OUTPUT_MODE mode)
{
    int32_t result = EDAL_DRIVER_OK;

    if(PIN_IS_AVAILABLE(pin))
    {
        switch (mode)
        {
            case EDAL_GPIO_PUSH_PULL:
                break;
        
            case EDAL_GPIO_OPEN_DRAIN:
                break;

            default:
                result = EDAL_DRIVER_ERROR_PARAMETER;
                break;
        }
    }
    else
    {
        result = EDAL_GPIO_ERROR_PIN;
    }

    return result;
}

static int32_t GPIO_SetPullResistor(EDAL_GPIO_Pin_t pin, EDAL_GPIO_PULL_RESISTOR resistor)
{
    int32_t result = EDAL_DRIVER_OK;

    if(PIN_IS_AVAILABLE(pin))
    {
        switch (resistor)
        {
            case EDAL_GPIO_PULL_NONE:
                break;
        
            case EDAL_GPIO_PULL_UP:
                break;

            case EDAL_GPIO_PULL_DOWN:
                break;

            default:
                result = EDAL_DRIVER_ERROR_PARAMETER;
                break;
        }
    }
    else
    {
        result = EDAL_GPIO_ERROR_PIN;
    }

    return result;
}

static int32_t GPIO_SetEventTrigger(EDAL_GPIO_Pin_t pin, EDAL_GPIO_EVENT_TRIGGER trigger)
{
    int32_t result = EDAL_DRIVER_OK;

    if(PIN_IS_AVAILABLE(pin))
    {
        switch (trigger)
        {
            case EDAL_GPIO_TRIGGER_NONE:
                break;
        
            case EDAL_GPIO_TRIGGER_RISING_EDGE:
                break;

            case EDAL_GPIO_TRIGGER_FALLING_EDGE:
                break;

            case EDAL_GPIO_TRIGGER_EITHER_EDGE:
                break;

            default:
                result = EDAL_DRIVER_ERROR_PARAMETER;
                break;
        }
    }
    else
    {
        result = EDAL_GPIO_ERROR_PIN;
    }

    return result;
}

void GPIO_SetOutput(EDAL_GPIO_Pin_t pin, uint32_t val)
{
    if(PIN_IS_AVAILABLE(pin))
    {
    }
}

uint32_t GPIO_SetInput(EDAL_GPIO_Pin_t pin)
{
    uint32_t val = 0U;

    if(PIN_IS_AVAILABLE(pin))
    {
    }

    return val;
}


/*============================ PROTOTYPES ====================================*/
EDAL_DRIVER_GPIO Driver_GPIO0 = {
    GPIO_Setup,
    GPIO_SetDirection,
    GPIO_SetOutputMode,
    GPIO_SetPullResistor,
    GPIO_SetEventTrigger,
    GPIO_SetOutput,
    GPIO_SetInput
}


/*============================ END ===========================================*/
