#include <Arduino.h>
#include <unity.h>
#include "led_controller.h"

const uint8_t PixelPin = 8;
LedController pixel(PixelPin);

void test_led_setup() {
  pixel.setup();
  TEST_ASSERT_TRUE(true); // Replace with actual checks
}

void test_led_update() {
  pixel.update();
  TEST_ASSERT_TRUE(true); // Replace with actual checks
}

// todo: add ble tests (qemu stuff maybe?)

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_led_setup);
  RUN_TEST(test_led_update);
  UNITY_END();
}

void loop() {
  // Empty loop
}