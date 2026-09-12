#include "scene/menu.h"

#include "core/arduboy.h"
#include "core/state.h"
#include "tools.h"

#include <stdint.h>

namespace game::scene
{

namespace
{

auto print_arrow(const auto pos)
{
    auto& arduboy = game::core::get_arduboy();

    arduboy.drawLine(pos.first, pos.second, pos.first + 4, pos.second + 4, WHITE);
    arduboy.drawLine(pos.first + 4, pos.second + 4, pos.first, pos.second + 8, WHITE);
    arduboy.drawLine(pos.first - 6, pos.second + 4, pos.first + 2, pos.second + 4, WHITE);
}

auto print_text(const auto pos, const auto text, const auto text_size, const auto is_highlight)
{
    auto& arduboy = game::core::get_arduboy();

    if (is_highlight)
        print_arrow(tools::pair{pos.first - 7, pos.second});

    arduboy.setCursor(pos.first, pos.second);
    arduboy.print(text);
}

} // unnamed namespace

menu::menu()
{
    game::core::get_arduboy().setTextSize(text_size);
}

void menu::draw()
{
    auto& arduboy = game::core::get_arduboy();
    const auto text_size = arduboy.getTextSize();
    const auto center = game::tools::get_center();

    auto pos = tools::pair{static_cast<uint8_t>(center.first - char_width * text_size * sizeof(start) / 2), center.second};
    print_text(pos, start, text_size, current_highlight == game::core::mode::level);

    pos = tools::pair{static_cast<uint8_t>(center.first - char_width * text_size * sizeof(scores) / 2), static_cast<uint8_t>(center.second + char_height + uint8_t(2))};
    print_text(pos, scores, text_size, current_highlight == game::core::mode::scores);

    process_key_press();
}

void menu::process_key_press()
{
    auto& arduboy = game::core::get_arduboy();
    arduboy.pollButtons();

    if (arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(DOWN_BUTTON))
    {
        if (current_highlight == game::core::mode::level)
            current_highlight = game::core::mode::scores;
        else
            current_highlight = game::core::mode::level;
    }
    else if (arduboy.justPressed(A_BUTTON))
        game::core::get_state().set_current_scene(current_highlight);
}

void menu::reset()
{
}

} // namespace game::scene
