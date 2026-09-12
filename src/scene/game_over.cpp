#include "scene/game_over.h"

#include "core/arduboy.h"
#include "tools.h"

namespace game::scene
{

game_over::game_over(uint32_t score) : base(game::core::mode::end), score(score)
{
}

void game_over::draw()
{
    const auto pos = tools::get_center();
    static constexpr auto text_length = static_cast<uint8_t>(sizeof(text));
    static constexpr auto scores_length = static_cast<uint8_t>(sizeof(score_text));

    auto& arduboy = game::core::get_arduboy();
    arduboy.setCursor(pos.first - (text_length / 2) * char_width, pos.second - char_height / 2);
    arduboy.print(text);

    const auto number_count = tools::get_number_count(score);
    arduboy.setCursor(pos.first - (scores_length + number_count) / 2 * char_width, pos.second + char_height + 2);
    arduboy.print(score_text);
    arduboy.print(score);

    process_key_press();
}

void game_over::process_key_press()
{
    auto& arduboy = game::core::get_arduboy();
    arduboy.pollButtons();

    if (arduboy.justPressed(A_BUTTON))
        current_scene = game::core::mode::menu;
}

}; // namespace game::scene
