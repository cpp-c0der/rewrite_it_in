#include "core/arduboy.h"

namespace game::core
{

Arduboy2& get_arduboy()
{
    static Arduboy2 arduboy;

    return arduboy;
}

BeepPin1& get_beep_pin1()
{
    static BeepPin1 beep_pin;

    return beep_pin;
}

BeepPin2& get_beep_pin2()
{
    static BeepPin2 beep_pin;

    return beep_pin;
}

scene::menu& get_menu()
{
    static scene::menu menu(1);

    return menu;
}

scene::gameplay& get_gameplay()
{
    static scene::gameplay gameplay;

    return gameplay;
}

void init()
{
    get_arduboy().begin();
    get_beep_pin1().begin();
    get_beep_pin2().begin();

    get_arduboy().setFrameRate(fps);
}

} // namespace game::core
