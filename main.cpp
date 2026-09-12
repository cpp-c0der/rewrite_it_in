#include "core/arduboy.h"
#include "core/state.h"

void setup()
{
    game::core::init();
}

void loop()
{
    auto& arduboy = game::core::get_arduboy();
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
        break;
    }
    case game::core::mode::game:
    {
        auto& gameplay = state.get_gameplay();
        gameplay.draw();
        break;
    }
    case game::core::mode::scores:
        break;
    }

    arduboy.display();

    // static constexpr auto width = 8;
    // static constexpr auto height = 8;
    // static constinit auto playerX = 64;
    // static constinit auto playerY = 32;
    // static constinit auto dirX = 1;
    // static constinit auto dirY = 1;
    //
    // auto& beep1 = game::core::get_beep_pin1();
    // auto& arduboy = game::core::get_arduboy();
    // beep1.timer();
    //
    // if (!(arduboy.nextFrame()))
    //     return;
    //
    // arduboy.pollButtons();
    //
    // if (arduboy.pressed(RIGHT_BUTTON))
    //     playerX += dirX;
    // else if (arduboy.pressed(LEFT_BUTTON))
    //     playerX -= dirX;
    // else if (arduboy.pressed(UP_BUTTON))
    //     playerY -= dirY;
    // else if (arduboy.pressed(DOWN_BUTTON))
    //     playerY += dirY;
    // else
    // {
    //     playerX += dirX;
    //     playerY += dirY;
    // }
    //
    // if (playerX < 0)
    //     playerX = 0;
    // else if (playerX > arduboy.width() - width)
    //     playerX = arduboy.width() - width;
    // if (playerY < 0)
    //     playerY = 0;
    // else if (playerY > arduboy.height() - height)
    //     playerY = arduboy.height() - height;
    //
    // if (playerX >= arduboy.width() - width || playerX <= 0)
    // {
    //     dirX = -dirX;
    //     beep1.tone(beep1.freq(1000), game::core::tools::seconds_to_frame_count(1));
    // }
    //
    // if (playerY >= arduboy.height() - height || playerY <= 0)
    // {
    //     dirY = -dirY;
    //     beep1.tone(beep1.freq(1000), game::core::tools::seconds_to_frame_count(1));
    // }
    //
    // arduboy.clear();
    //
    // arduboy.fillRect(playerX, playerY, width, height, WHITE);
    //
    // arduboy.setCursor(10, 10);
    // arduboy.print(F("Hello, Arduboy!"));
    //
    // arduboy.display();
}
