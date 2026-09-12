#include "scene/gameplay.h"

#include "core/arduboy.h"
#include "tools.h"

namespace game::scene
{

namespace
{

constexpr uint8_t entity_width = 8;
constexpr uint8_t entity_height = 8;

constexpr uint8_t c_icon[] PROGMEM =
    {
        entity_width, entity_height,
        0x3C, // ..#####.
        0x42, // .#......
        0x81, // #.......
        0x81, // #.......
        0x81, // #.......
        0x81, // #.......
        0x81, // .#......
        0x00  // ..#####.

};

constexpr uint8_t rust_icon[] PROGMEM =
    {
        entity_width, entity_height,
        0xFF, // ######..
        0x0F, // #.....#.
        0x09, // #.....#.
        0x19, // ######..
        0x29, // #...#...
        0x49, // #....#..
        0x8F, // #.....#.
        0x00  // #.....#.
};

constexpr uint8_t project_icon[] PROGMEM =
    {
        entity_width, entity_height,
        0x24, // ..#..#..
        0x24, // ..#..#..
        0x7E, // .######.
        0x24, // ..#..#..
        0x24, // ..#..#..
        0x7E, // .######.
        0x24, // ..#..#..
        0x24  // ..#..#..
};

auto get_center_position()
{
    const auto center = tools::get_center();
    const auto x = static_cast<uint8_t>(center.first - entity_width / 2);
    const auto y = static_cast<uint8_t>(center.second - entity_height / 2);

    return game::geometry::point{x, y};
}

auto get_random_position()
{
    auto& arduboy = game::core::get_arduboy();
    const auto x = static_cast<uint8_t>(random(0, arduboy.width() - entity_width));
    const auto y = static_cast<uint8_t>(random(0, arduboy.height() - entity_height));

    return game::geometry::point{x, y};
}

} // namespace

gameplay::gameplay() : hero(get_center_position(), {entity_width, entity_height}, default_speed),
                       project(get_random_position(), {entity_width, entity_height})
{
}

void gameplay::draw()
{
    auto& arduboy = game::core::get_arduboy();
    const auto hero_pos = hero.get_position();
    const auto project_pos = project.get_position();

    Sprites::drawOverwrite(hero_pos.x, hero_pos.y, c_icon, 0);
    Sprites::drawOverwrite(project_pos.x, project_pos.y, project_icon, 0);
    process_key_press();

    if (hero.is_intersect(project))
        project.set_position(get_random_position());

    static const game::geometry::rectangle border{{0, 0}, {arduboy.width(), arduboy.height()}};

    if (arduboy.everyXFrames(4))
        hero.move(border);
}

void gameplay::process_key_press()
{
    auto& arduboy = game::core::get_arduboy();
    arduboy.pollButtons();

    if (arduboy.justPressed(UP_BUTTON))
        hero.set_direction(entity::direction::up);
    else if (arduboy.justPressed(DOWN_BUTTON))
        hero.set_direction(entity::direction::down);
    else if (arduboy.justPressed(LEFT_BUTTON))
        hero.set_direction(entity::direction::left);
    else if (arduboy.justPressed(RIGHT_BUTTON))
        hero.set_direction(entity::direction::right);
}

} // namespace game::scene
