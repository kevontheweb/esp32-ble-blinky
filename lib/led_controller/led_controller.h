#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "color_utils.h"
#include <vector>
#include <string>

class LedController {
public:
    LedController(uint8_t pin);
    void setup();
    void update();
    void set_color(const ColorUtils::RgbColor& color);
    void set_color(const ColorUtils::HslColor& color);
    void set_colors(const std::vector<ColorUtils::RgbColor>& colors);
    void set_colors(const std::vector<ColorUtils::HslColor>& colors);

private:
    uint8_t pin;
    std::vector<ColorUtils::RgbColor> colors;
    std::vector<std::string> color_names;
    ColorUtils::RgbColor black;
    size_t current_index;
    unsigned long last_update_time;
    unsigned long update_interval;

    enum AnimationState {
        IDLE,
        ANIMATING
    } animation_state;

    float animation_progress;
    size_t animation_start_index;
    size_t animation_end_index;

    void write_color(const ColorUtils::RgbColor& color);
    void write_color(const ColorUtils::HslColor& color);
    void start_animation(size_t start_index, size_t end_index);
    void update_animation();
};

#endif // LED_CONTROLLER_H