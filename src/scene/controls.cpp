#include "scene/controls.h"

#include "core/arduboy.h"
#include "core/state.h"
#include "tools.h"

namespace game::scene
{

void controls::draw()
{
    const auto center = game::tools::get_center();
    static constexpr auto movement_length = static_cast<uint8_t>(sizeof(movement_control));
    static constexpr auto acceleration_length = static_cast<uint8_t>(sizeof(acceleration_control));
    static constexpr auto menu_length = static_cast<uint8_t>(sizeof(menu_control));

    auto& arduboy = game::core::get_arduboy();

    static constexpr auto offset = uint8_t(7);
    arduboy.setCursor(center.first - movement_length / 2 * char_width - offset, char_height);
    arduboy.print(movement_control);

    arduboy.setCursor(center.first - acceleration_length / 2 * char_width - offset, char_height * 2 + 2);
    arduboy.print(acceleration_control);

    arduboy.setCursor(center.first - menu_length / 2 * char_width - offset, char_height * 3 + 4);
    arduboy.print(menu_control);

    process_key_press();
}

void controls::process_key_press()
{
    if (game::tools::any_key_pressed())
        game::core::get_state().set_current_scene(game::core::mode::menu);
}

} // namespace game::scene
