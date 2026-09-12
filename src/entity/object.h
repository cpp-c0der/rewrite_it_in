#ifndef ENTITY_OBJECT_H
#define ENTITY_OBJECT_H

#include "geometry.h"
#include "tools.h"

#include <stdint.h>

namespace game::entity
{

class object
{
protected:
    using size = tools::pair<uint8_t, uint8_t>;

public:
    object(const game::geometry::point position, const size hitbox);
    game::geometry::point get_position() const;
    void set_position(const game::geometry::point position);
    size get_hitbox() const;
    bool is_intersect(const object& obj) const;
    void hide();
    void show();
    bool is_hide() const;

protected:
    geometry::point position;
    size hitbox;
    bool is_visible = true;
};

} // namespace game::entity

#endif
