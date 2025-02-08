#include <iostream>
#include <vector>
#include "led_controller.h"
#include "ble_controller.h"

const uint8_t pixel_pin = 8;
LedController pixel(pixel_pin);
BLEController ble_controller;

void setup() {
  pixel.setup();
  ble_controller.setup();
}

void loop() {
  if (!ble_controller.is_animation_paused()) {
    pixel.update();
  }
}