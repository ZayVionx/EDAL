#include "key_edal.h"
#include "sys.h"
#include <stddef.h>

volatile uint32_t test_gpio_levels = 0x1FU;
volatile uint32_t test_gpio_init_count;
volatile uint32_t test_primask;
volatile uint32_t test_ipsr;
volatile uint32_t test_failed_line;
volatile uint32_t test_checks;
volatile uint32_t test_stage;
volatile uint32_t test_beep_count;

/* 裸机测试无需启动文件；Python 根据这两个符号结束仿真。 */
__attribute__((noinline)) void test_failure(void) { for (;;) { } }
__attribute__((noinline)) void test_finish(void) { for (;;) { } }

#define CHECK(condition) do {                           \
    test_checks++;                                     \
    if (!(condition)) {                                \
        test_failed_line = __LINE__;                    \
        test_failure();                                \
    }                                                  \
} while (0)

/* 避免链接宿主 C 运行库；真实 FIFO 仍使用 memcpy 实现。 */
void *memcpy(void *destination, const void *source, size_t length)
{
    size_t index;
    uint8_t *out = destination;
    const uint8_t *in = source;
    for (index = 0U; index < length; index++) { out[index] = in[index]; }
    return destination;
}

void *memset(void *destination, int value, size_t length)
{
    size_t index;
    uint8_t *out = destination;
    for (index = 0U; index < length; index++) { out[index] = (uint8_t)value; }
    return destination;
}

void __aeabi_memcpy(void *destination, const void *source, size_t length)
{
    (void)memcpy(destination, source, length);
}

void __aeabi_memcpy4(void *destination, const void *source, size_t length)
{
    (void)memcpy(destination, source, length);
}

void __aeabi_memclr(void *destination, size_t length)
{
    (void)memset(destination, 0, length);
}

void __aeabi_memclr4(void *destination, size_t length)
{
    (void)memset(destination, 0, length);
}

void test_beep(uint32_t duration_ms)
{
    CHECK(duration_ms == 100U);
    CHECK(test_ipsr == 0U);
    test_beep_count++;
}

static void advance_ms(uint32_t duration_ms)
{
    uint32_t index;
    for (index = 0U; index < duration_ms; index++) { TS10_KEY_Scan1ms(); }
}

static void set_pressed(uint32_t key_id, bool pressed)
{
    if (pressed) { test_gpio_levels &= ~(1UL << key_id); }
    else { test_gpio_levels |= 1UL << key_id; }
}

static void click(uint32_t key_id)
{
    set_pressed(key_id, true);
    advance_ms(50U);
    set_pressed(key_id, false);
    advance_ms(250U);
}

static void double_click(uint32_t key_id)
{
    set_pressed(key_id, true);
    advance_ms(50U);
    set_pressed(key_id, false);
    advance_ms(50U);
    set_pressed(key_id, true);
    advance_ms(50U);
    set_pressed(key_id, false);
    advance_ms(250U);
}

static void restart(void)
{
    CHECK(bsp_key_uninit() == EDAL_DEVICE_OK);
    test_gpio_levels = 0x1FU;
    advance_ms(30U);
    CHECK(bsp_key_init());
    advance_ms(30U);
}

static void check_empty(void)
{
    bsp_key_event_t event;
    CHECK(!bsp_key_get_event(&event));
    CHECK(bsp_key_get_value() == BSP_KEY_NONE);
}

static bsp_key_event_t read_event(uint32_t key_id, uint32_t event_mask)
{
    bsp_key_event_t event;
    CHECK(bsp_key_get_event(&event));
    CHECK((uint32_t)event.key_id == key_id);
    CHECK((uint32_t)event.key_value == key_id + 1U);
    CHECK(event.event == event_mask);
    return event;
}

static void test_mapping_and_compatibility(void)
{
    uint32_t index;
    uint32_t beep_count;
    CHECK(bsp_key_init());
    CHECK(bsp_key_init());
    CHECK(!bsp_key_get_event(NULL));
    advance_ms(100U);
    check_empty();

    for (index = 0U; index < TS10_KEY_COUNT; index++) {
        beep_count = test_beep_count;
        click(index);
        CHECK(test_beep_count == beep_count);
        (void)read_event(index, EDAL_KEY_EVENT_CLICKED);
        CHECK(test_beep_count == beep_count + 1U);
        check_empty();
    }
    click(0U);
    CHECK(bsp_key_get_value() == 0x00U);
    check_empty();
    double_click(4U);
    CHECK(bsp_key_get_value() == 0x24U);
    check_empty();
}

static void test_long_and_repeat(void)
{
    uint32_t beep_count;
    restart();
    CHECK(bsp_key_add_event(KEY_2, EDAL_KEY_EVENT_LONG_PRESS_REPEAT) == EDAL_DEVICE_OK);
    set_pressed(2U, true);
    advance_ms(550U);
    (void)read_event(2U, EDAL_KEY_EVENT_LONG_PRESS);
    check_empty();
    beep_count = test_beep_count;
    advance_ms(100U);
    (void)read_event(2U, EDAL_KEY_EVENT_LONG_PRESS_REPEAT);
    CHECK(test_beep_count == beep_count);
    check_empty();
    set_pressed(2U, false);
    advance_ms(250U);
    check_empty();

    set_pressed(2U, true);
    advance_ms(550U);
    CHECK(bsp_key_get_value() == 0x12U);
    advance_ms(100U);
    CHECK(bsp_key_get_value() == 0x12U);
    set_pressed(2U, false);
    advance_ms(250U);
    check_empty();
}

static void test_masks_and_status(void)
{
    EDAL_KEY_STATUS status;
    restart();
    CHECK(bsp_key_remove_event(KEY_1, EDAL_KEY_EVENT_DOUBLE_CLICK) == EDAL_DEVICE_OK);
    double_click(1U);
    check_empty();
    status = Device_KEY1.GetStatus();
    CHECK(status.double_click == 1U);
    CHECK(status.press == 0U);
    CHECK(Device_KEY1.GetStatus().double_click == 0U);
    click(1U);
    (void)read_event(1U, EDAL_KEY_EVENT_CLICKED);
    check_empty();

    CHECK(bsp_key_remove_event(KEY_ALL, EDAL_KEY_EVENT_ALL) == EDAL_DEVICE_OK);
    set_pressed(0U, true);
    advance_ms(50U);
    CHECK(Device_KEY0.GetStatus().press == 1U);
    CHECK(Device_KEY0.GetStatus().press == 1U);
    set_pressed(0U, false);
    advance_ms(250U);
    status = Device_KEY0.GetStatus();
    CHECK(status.press == 0U);
    CHECK(status.clicked == 1U);
    check_empty();
    CHECK(bsp_key_add_event(KEY_ALL, EDAL_KEY_EVENT_CLICKED) == EDAL_DEVICE_OK);
    click(4U);
    (void)read_event(4U, EDAL_KEY_EVENT_CLICKED);
    check_empty();
}

static void test_control_and_per_key_timing(void)
{
    EDAL_KEY_CAPABILITIES capabilities;
    restart();
    capabilities = Device_KEY0.GetCapabilities();
    CHECK(capabilities.event_press && capabilities.event_release);
    CHECK(capabilities.event_clicked && capabilities.event_double_click);
    CHECK(capabilities.event_long_press && capabilities.event_long_press_release);
    CHECK(capabilities.event_long_press_repeat && capabilities.debounce);
    CHECK(capabilities.timing_config && !capabilities.wakeup);
    CHECK(capabilities.reserved == 0U);
    CHECK(Device_KEY0.GetVersion().api == EDAL_KEY_API_VERSION);
    CHECK(Device_KEY0.Control(0x100U | EDAL_KEY_SET_EVENT_MASK, 0U) == EDAL_DEVICE_ERROR_PARAMETER);
    CHECK(Device_KEY0.Control(0xFEU, 0U) == EDAL_DEVICE_ERROR_UNSUPPORTED);
    CHECK(Device_KEY0.Control(EDAL_KEY_SET_EVENT_MASK, 0x80000000UL) == EDAL_DEVICE_ERROR_PARAMETER);
    CHECK(Device_KEY0.Control(EDAL_KEY_SET_LONG_PRESS_TIME, 0U) == EDAL_DEVICE_ERROR_PARAMETER);
    CHECK(Device_KEY0.Control(EDAL_KEY_SET_DOUBLE_CLICK_TIME, 0U) == EDAL_DEVICE_ERROR_PARAMETER);
    CHECK(Device_KEY0.Control(EDAL_KEY_SET_REPEAT_PERIOD, 0U) == EDAL_DEVICE_ERROR_PARAMETER);
    CHECK(Device_KEY0.Control(EDAL_KEY_SET_LONG_PRESS_TIME, UINT32_MAX) == EDAL_DEVICE_ERROR_PARAMETER);
    CHECK(Device_KEY0.Control(EDAL_KEY_CONTROL_WAKEUP, EDAL_KEY_ENABLE) == EDAL_DEVICE_ERROR_UNSUPPORTED);
    CHECK(Device_KEY0.PowerControl(EDAL_POWER_LOW) == EDAL_DEVICE_ERROR_UNSUPPORTED);
    CHECK(Device_KEY0.PowerControl((EDAL_POWER_STATE)99) == EDAL_DEVICE_ERROR_PARAMETER);
    CHECK(bsp_key_add_event((KEY_ID)-1, EDAL_KEY_EVENT_CLICKED) == EDAL_DEVICE_ERROR_PARAMETER);
    CHECK(bsp_key_remove_event(KEY_0, 0x80000000UL) == EDAL_DEVICE_ERROR_PARAMETER);

    CHECK(Device_KEY0.Control(EDAL_KEY_SET_LONG_PRESS_TIME, 200U) == EDAL_DEVICE_OK);
    CHECK(Device_KEY1.Control(EDAL_KEY_SET_LONG_PRESS_TIME, 800U) == EDAL_DEVICE_OK);
    set_pressed(0U, true);
    set_pressed(1U, true);
    advance_ms(50U);
    CHECK(Device_KEY0.Control(EDAL_KEY_SET_LONG_PRESS_TIME, 1000U) == EDAL_DEVICE_ERROR_BUSY);
    advance_ms(500U);
    (void)read_event(0U, EDAL_KEY_EVENT_LONG_PRESS);
    check_empty();
    set_pressed(0U, false);
    set_pressed(1U, false);
    advance_ms(250U);
    (void)read_event(1U, EDAL_KEY_EVENT_CLICKED);
    check_empty();

    CHECK(Device_KEY0.Control(EDAL_KEY_SET_DEBOUNCE_TIME, 0U) == EDAL_DEVICE_OK);
    advance_ms(500U);
    check_empty();
    click(0U);
    (void)read_event(0U, EDAL_KEY_EVENT_CLICKED);
    check_empty();
}

static void test_lifecycle_and_overflow(void)
{
    uint32_t index;
    uint32_t count;
    bsp_key_event_t event;
    restart();
    for (index = 0U; index < 4U; index++) {
        CHECK(Device_KEY3.PowerControl(EDAL_POWER_OFF) == EDAL_DEVICE_OK);
        click(3U);
        check_empty();
        CHECK(Device_KEY3.PowerControl(EDAL_POWER_FULL) == EDAL_DEVICE_OK);
        click(3U);
        (void)read_event(3U, EDAL_KEY_EVENT_CLICKED);
        check_empty();
        restart();
    }

    CHECK(Device_KEY4.Control(EDAL_KEY_SET_LONG_PRESS_TIME, 100U) == EDAL_DEVICE_OK);
    CHECK(Device_KEY4.Control(EDAL_KEY_SET_REPEAT_PERIOD, 10U) == EDAL_DEVICE_OK);
    CHECK(bsp_key_add_event(KEY_4, EDAL_KEY_EVENT_LONG_PRESS_REPEAT) == EDAL_DEVICE_OK);
    set_pressed(4U, true);
    advance_ms(1000U);
    CHECK(bsp_key_get_overflow_count() > 0U);
    CHECK(bsp_key_get_event(&event));
    CHECK(event.key_id == KEY_4 && event.event == EDAL_KEY_EVENT_LONG_PRESS);
    count = 1U;
    while (bsp_key_get_event(&event)) {
        CHECK(event.key_id == KEY_4 && event.event == EDAL_KEY_EVENT_LONG_PRESS_REPEAT);
        count++;
    }
    CHECK(count == BSP_KEY_EVENT_QUEUE_SIZE);
    set_pressed(4U, false);
    advance_ms(250U);
    restart();
    CHECK(bsp_key_get_overflow_count() == 0U);
    CHECK(bsp_key_uninit() == EDAL_DEVICE_OK);
    CHECK(Device_KEY0.Control(EDAL_KEY_SET_EVENT_MASK, 0U) == EDAL_DEVICE_ERROR);
    CHECK(Device_KEY0.PowerControl(EDAL_POWER_FULL) == EDAL_DEVICE_ERROR);
    CHECK(bsp_key_add_event(KEY_0, EDAL_KEY_EVENT_CLICKED) == EDAL_DEVICE_ERROR);
    CHECK(test_primask == 0U);
}

void test_main(void)
{
    test_stage = 1U;
    test_mapping_and_compatibility();
    test_stage = 2U;
    test_long_and_repeat();
    test_stage = 3U;
    test_masks_and_status();
    test_stage = 4U;
    test_control_and_per_key_timing();
    test_stage = 5U;
    test_lifecycle_and_overflow();
    test_stage = 6U;
    test_finish();
}
