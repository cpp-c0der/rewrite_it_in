#ifndef MENU_H
#define MENU_H

#include "core/mode.h"

#include <stdint.h>

namespace game::scene
{

class menu
{
public:
    void draw();
    game::core::mode get_scene() const;

private:
    void process_key_press();

private:
    static inline constexpr uint8_t text_size = 1;
    static inline constexpr uint8_t char_width = 5;
    static inline constexpr uint8_t char_height = 8;
    static inline constexpr char start[] = "start";
    static inline constexpr char scores[] = "scores";

    game::core::mode current_scene = core::mode::menu;
    game::core::mode current_highlight = core::mode::game;
};

} // namespace game::scene

#endif
