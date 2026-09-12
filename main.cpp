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
        break;
    }
    case game::core::mode::game:
    {
        auto& gameplay = state.get_gameplay();
        gameplay.draw();
        break;
    }
    case game::core::mode::scores:
    {
        state.set_current_scene(game::core::mode::menu);
        break;
    }
    case game::core::mode::level:
    {
        auto& level = state.get_level();
        level.set_level(state.get_next_level());
        level.draw();

        break;
    }
    case game::core::mode::end:
    {
        auto& game_over = state.get_game_over();
        game_over.set_score(state.get_last_score());
        game_over.draw();
        break;
    }
    }

    arduboy.display();
}
