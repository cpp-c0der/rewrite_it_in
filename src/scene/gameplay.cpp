#include "scene/gameplay.h"

#include "core/arduboy.h"
#include "tools.h"

namespace game::scene
{

gameplay::gameplay() : hero(tools::get_center(), default_speed)
{
}

void gameplay::draw()
{
    constexpr uint8_t cpp_logo[] PROGMEM =
        {
            10, 10,

            0x3C, 0x00,
            0x7E, 0x00,
            0x42, 0x00,
            0x42, 0x00,
            0x76, 0x00,
            0x34, 0x00,
            0x00, 0x00,
            0x10, 0x00,
            0x7E, 0x00,
            0x10, 0x00};

    Sprites::drawSelfMasked(59, 27, cpp_logo, 0);
}

void gameplay::process_key_press()
{
    auto& arduboy = game::core::get_arduboy();
    arduboy.pollButtons();

    if (arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(DOWN_BUTTON))
    {
    }
}

} // namespace game::scene
