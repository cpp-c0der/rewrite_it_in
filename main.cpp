#include "core/arduboy.h"
#include "core/state.h"

void setup()
{
    game::core::init();
}

void loop()
{
    auto& arduboy = game::core::get_arduboy();
    auto& beep1 = game::core::get_beep_pin1();
    beep1.timer();

    if (!(arduboy.nextFrame()))
        return;

    arduboy.clear();

    auto& state = game::core::get_state();
    const auto scene = state.get_current_scene();

    switch (scene)
    {
    case game::core::mode::menu:
    {
        auto& menu = state.get_menu();
        menu.draw();
        state.set_current_scene(menu.get_scene());
        menu.reset();
        break;
    }
    case game::core::mode::game:
    {
        auto& gameplay = state.get_gameplay();
        gameplay.draw();
        state.set_current_scene(gameplay.get_scene());
        gameplay.reset();
        break;
    }
    case game::core::mode::scores:
        break;
    }

    arduboy.display();
}
