#include "tools.h"

#include "arduboy.h"

namespace game::tools
{

uint32_t seconds_to_frame_count(uint32_t seconds)
{
    return game::core::fps * seconds;
}

} // namespace game::tools
