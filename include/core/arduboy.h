#ifndef ARDUBOY_H
#define ARDUBOY_H

#include <Arduboy2.h>

#include <stdint.h>

namespace game::core
{

Arduboy2& get_arduboy();
BeepPin1& get_beep_pin1();
BeepPin2& get_beep_pin2();

void init();

inline constexpr auto fps = uint8_t(60);

} // namespace game::core

#endif
