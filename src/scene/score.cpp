#include "scene/score.h"

#include "core/arduboy.h"
#include "core/mode.h"
#include "core/state.h"
#include "scene/base.h"
#include "tools.h"

namespace game::scene
{

void score::draw()
{
    const auto center = tools::get_center();
    static constexpr auto text_length = static_cast<uint8_t>(sizeof(top_text));

    const auto x = center.first - text_length / 2 * scene::base::char_width;
    const auto y = scene::base::char_height;

    auto& arduboy = game::core::get_arduboy();

    arduboy.setCursor(x, y);
    arduboy.print(top_text);

    const auto& storage = game::core::get_state().get_storage();
    const auto& tops = storage.get_top();

    for (uint8_t i = 0; i < storage.count; ++i)
    {
        arduboy.setCursor(x, y + scene::base::char_height * (i + 1));
        arduboy.print(i);
        arduboy.print(". ");
        arduboy.print(tops[i]);
    }

    process_key_press();
}

void score::process_key_press()
{
    if (tools::any_key_pressed())
        game::core::get_state().set_current_scene(game::core::mode::menu);
}

} // namespace game::scene
