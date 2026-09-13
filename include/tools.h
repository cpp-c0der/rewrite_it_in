#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>

namespace game::tools
{

template <typename T1, typename T2>
struct pair
{
    T1 first;
    T2 second;
};

uint32_t seconds_to_frame_count(uint32_t seconds);

pair<uint8_t, uint8_t> get_center();
uint8_t get_number_count(uint32_t num);
bool any_key_pressed();

} // namespace game::tools

#endif
