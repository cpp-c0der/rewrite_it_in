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

} // namespace game::tools

#endif
