#include "core/arduboy.h"
#include "scene/menu.h"

void setup()
{
    game::core::init();
}

void loop()
{
    auto& arduboy = game::core::get_arduboy();
    if (!(arduboy.nextFrame()))
        return;

    auto& menu = game::core::get_menu();

    arduboy.clear();
    menu.draw();
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
