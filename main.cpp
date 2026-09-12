#include "core/arduboy.h"
#include "core/state.h"
#include "scene/game_over.h"
#include "scene/level.h"

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
    {
        state.set_current_scene(game::core::mode::menu);
        break;
    }
    case game::core::mode::level:
    {
        auto level = game::scene::level(state.get_gameplay().get_level());
        level.draw();
        state.set_current_scene(level.get_scene());
        break;
    }
    case game::core::mode::end:
    {
        auto& gameplay = state.get_gameplay();
        auto game_over = game::scene::game_over(gameplay.get_score());
        gameplay = game::scene::gameplay();
        game_over.draw();
        state.set_current_scene(game_over.get_scene());
        break;
    }
    }

    arduboy.display();
}
