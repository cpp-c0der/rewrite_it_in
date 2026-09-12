#ifndef ENTITY_OBJECT_H
#define ENTITY_OBJECT_H

#include "tools.h"

#include <stdint.h>

namespace game::entity
{

class object
{
protected:
    using point = tools::pair<uint8_t, uint8_t>;

public:
    object(const point position);
    point get_position() const;

protected:
    point position;
    uint8_t width;
    uint8_t height;
};

} // namespace game::entity

#endif
