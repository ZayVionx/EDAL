#ifndef TS10_KEY_TEST_BEEP_H
#define TS10_KEY_TEST_BEEP_H

#include <stdint.h>

void test_beep(uint32_t duration_ms);
#define BEEP_DIDIDIDI(duration_ms) test_beep(duration_ms)

#endif /* TS10_KEY_TEST_BEEP_H */
