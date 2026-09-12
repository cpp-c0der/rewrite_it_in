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

void init()
{
    get_arduboy().begin();
    get_beep_pin1().begin();
    get_beep_pin2().begin();

    get_arduboy().setFrameRate(fps);
    get_arduboy().initRandomSeed();
}

} // namespace game::core
