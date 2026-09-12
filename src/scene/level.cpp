#include "scene/level.h"

#include "core/arduboy.h"
#include "tools.h"

namespace game::scene
{

level::level(const uint32_t level_number) : scene::base(game::core::mode::level), level_number(level_number)
{
}

void level::draw()
{
    static constexpr auto text_length = static_cast<uint8_t>(sizeof(text));
    const auto number_count = game::tools::get_number_count(level_number);
    const auto center = game::tools::get_center();
    const auto x = static_cast<uint8_t>(center.first - text_length / 2 * char_width);
    const auto y = static_cast<uint8_t>(center.second - char_height / 2);

    auto& arduboy = game::core::get_arduboy();
    arduboy.setCursor(x, y);
    arduboy.print(text);
    arduboy.print(level_number);

    process_key_press();
}

void level::process_key_press()
{
    auto& arduboy = game::core::get_arduboy();
    arduboy.pollButtons();

    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
        current_scene = game::core::mode::game;
}

} // namespace game::scene
