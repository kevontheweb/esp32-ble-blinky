#include "led_controller.h"
#include "esp32-hal-rgb-led.h"
#include <HardwareSerial.h>
#include <iostream>

#define colorSaturation 128

LedController::LedController(uint8_t pin) :
  pin(pin),
  black(0),
  current_index(0),
  last_update_time(0),
  update_interval(50),
  animation_state(IDLE),
  animation_progress(0.0f),
  animation_start_index(0),
  animation_end_index(1) {
  colors = {
    ColorUtils::RgbColor(colorSaturation, 0, 0),
    ColorUtils::RgbColor(0, colorSaturation, 0),
    ColorUtils::RgbColor(0, 0, colorSaturation),
    ColorUtils::RgbColor(colorSaturation) };
  color_names = { "Red", "Green", "Blue", "White" };
}

void LedController::setup() {
  Serial.begin(115200);
  std::cout << "Hello, world!" << std::endl;
}

void LedController::update() {
  unsigned long current_time = millis();
  if (current_time - last_update_time >= update_interval) {
    last_update_time = current_time;

    if (animation_state == IDLE) {
      current_index = current_index % colors.size();
      std::cout << "Color: " << color_names[current_index] << std::endl;
      write_color(colors[current_index++]);
      delay(50);
      std::cout << "Off" << std::endl;
      write_color(black);
      start_animation(0, 1); // Start animation from first to second color
    } else if (animation_state == ANIMATING) {
      update_animation();
    }
  }
}

void LedController::set_color(const ColorUtils::RgbColor& color) {
  write_color(color);
}

void LedController::set_color(const ColorUtils::HslColor& color) {
  write_color(color);
}

void LedController::set_colors(const std::vector<ColorUtils::RgbColor>& colors) {
  this->colors = colors;
}

void LedController::set_colors(const std::vector<ColorUtils::HslColor>& colors) {
  this->colors.clear();
  for (const auto& color : colors) {
    this->colors.push_back(ColorUtils::hsl_to_rgb(color));
  }
}

void LedController::write_color(const ColorUtils::RgbColor& color) {
  neopixelWrite(pin, color.r, color.g, color.b);
}

void LedController::write_color(const ColorUtils::HslColor& color) {
  ColorUtils::RgbColor rgb_color = ColorUtils::hsl_to_rgb(color);
  neopixelWrite(pin, rgb_color.r, rgb_color.g, rgb_color.b);
}

void LedController::start_animation(size_t start_index, size_t end_index) {
  animation_state = ANIMATING;
  animation_progress = 0.0f;
  animation_start_index = start_index;
  animation_end_index = end_index;
}

void LedController::update_animation() {
  animation_progress += 0.01f;
  if (animation_progress >= 1.0f) {
    animation_progress = 0.0f;
    animation_start_index = animation_end_index;
    animation_end_index = (animation_end_index + 1) % colors.size();
  }

  ColorUtils::HslColor start_color = ColorUtils::rgb_to_hsl(colors[animation_start_index]);
  ColorUtils::HslColor end_color = ColorUtils::rgb_to_hsl(colors[animation_end_index]);
  ColorUtils::HslColor blended_color = ColorUtils::HslColor::linear_blend(start_color, end_color, animation_progress);
  write_color(blended_color);
}