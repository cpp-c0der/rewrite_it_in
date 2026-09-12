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

} // namespace game::tools
