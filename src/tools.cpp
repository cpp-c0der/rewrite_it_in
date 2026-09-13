#include "tools.h"

#include "core/arduboy.h"

namespace game::tools
{

uint32_t seconds_to_frame_count(uint32_t seconds)
{
    return game::core::fps * seconds;
}

pair<uint8_t, uint8_t> get_center()
{
    static constexpr uint8_t x = Arduboy2::width() / uint8_t(2);
    static constexpr uint8_t y = Arduboy2::height() / uint8_t(2);

    return pair{x, y};
}

uint8_t get_number_count(uint32_t num)
{
    uint8_t count = 0;

    if (!num)
        return 1;

    while (num)
    {
        ++count;
        num /= 10;
    }

    return count;
}

bool any_key_pressed()
{
    auto& arduboy = game::core::get_arduboy();
    arduboy.pollButtons();

    return arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(DOWN_BUTTON) || arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON) || arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON);
}

} // namespace game::tools
