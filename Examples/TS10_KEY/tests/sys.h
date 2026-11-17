#ifndef TS10_KEY_TEST_SYS_H
#define TS10_KEY_TEST_SYS_H

#include <stdbool.h>
#include <stdint.h>

/* 仅模拟电平、GPIO 配置和临界区；按键状态机使用真实 emb_btn.c。 */
typedef struct { uint32_t unused; } GPIO_Module;
typedef struct {
    uint32_t Pin;
    uint32_t GPIO_Mode;
    uint32_t GPIO_Speed;
} GPIO_InitType;

#define GPIOE                       ((GPIO_Module *)0x40011800UL)
#define GPIO_PIN_0                  (1UL << 0)
#define GPIO_PIN_1                  (1UL << 1)
#define GPIO_PIN_2                  (1UL << 2)
#define GPIO_PIN_3                  (1UL << 3)
#define GPIO_PIN_4                  (1UL << 4)
#define GPIO_Mode_IPD               0U
#define GPIO_Speed_50MHz            50U
#define RCC_APB2_PERIPH_GPIOE       1U
#define ENABLE                     1U

extern volatile uint32_t test_gpio_levels;
extern volatile uint32_t test_gpio_init_count;
extern volatile uint32_t test_primask;
extern volatile uint32_t test_ipsr;

static inline uint32_t GPIO_ReadInputDataBit(GPIO_Module *port, uint32_t pin)
{
    (void)port;
    return (test_gpio_levels & pin) != 0U;
}

static inline void RCC_EnableAPB2PeriphClk(uint32_t peripheral, uint32_t enable)
{
    (void)peripheral;
    (void)enable;
}

static inline void GPIO_InitPeripheral(GPIO_Module *port, GPIO_InitType *config)
{
    (void)port;
    (void)config;
    test_gpio_init_count++;
}

static inline uint32_t __get_PRIMASK(void) { return test_primask; }
static inline void __disable_irq(void) { test_primask = 1U; }
static inline void __set_PRIMASK(uint32_t value) { test_primask = value; }
static inline uint32_t __get_IPSR(void) { return test_ipsr; }
static inline void __DMB(void) { }

#endif /* TS10_KEY_TEST_SYS_H */
