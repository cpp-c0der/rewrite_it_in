#include "scene/gameplay.h"

#include "core/arduboy.h"
#include "core/mode.h"
#include "core/state.h"
#include "tools.h"

namespace game::scene
{

namespace
{

constexpr uint8_t entity_width = 8;
constexpr uint8_t entity_height = 8;

constexpr uint8_t c_icon[] PROGMEM =
    {
        entity_width,
        entity_height,

        0b00000000,
        0b00111000,
        0b01000100,
        0b01000100,
        0b01010100,
        0b00000000,
        0b00010000,
        0b00000000

        // 0x0, // 0x81,
        // 0x1C,
        // 0x22,
        // 0x22,
        // 0x2A,
        // 0x0,
        // 0x8,
        // 0x0 // 0x81
};

constexpr uint8_t rust_icon[] PROGMEM =
    {
        entity_width,
        entity_height,

        0b00011000,
        0b01111110,
        0b01000010,
        0b11101011,
        0b11101011,
        0b01010110,
        0b01111110,
        0b00011000 //
};

constexpr uint8_t go_icon[] PROGMEM =
    {
        entity_height, entity_width,

        0b11000011,
        0b10111101,
        0b10101101,
        0b11001111,
        0b11000011,
        0b10111101,
        0b10111101,
        0b11000011 //
};

constexpr uint8_t python_icon[] PROGMEM =
    {
        entity_width, entity_height,

        0b11000011,
        0b11000011,
        0b00000000,
        0b11100010,
        0b10100000,
        0b11111111,
        0b00111100,
        0b00111100 //
};

constexpr uint8_t python_icon2[] PROGMEM =
    {
        entity_width, entity_height,
        0b11000011,
        0b11000011,
        0b00000010,
        0b11100000,
        0b11100000,
        0b10111111,
        0b00111100,
        0b00111100 //
};

constexpr uint8_t project_icon[] PROGMEM =
    {
        entity_width, entity_height,

        0b00000010,
        0b11111011,
        0b10101000,
        0b10101111,
        0b10101011,
        0b10101011,
        0b11111111,
        0b00000000 //
};

constexpr uint8_t adrenaline_icon[] PROGMEM =
    {
        entity_width, entity_height,

        0b11111111,
        0b00000000,
        0b01010001,
        0b00111001,
        0b00010101,
        0b00000001,
        0b00000000,
        0b11111111 //
};

auto get_border(const auto offset)
{
    auto& arduboy = game::core::get_arduboy();
    static const game::geometry::rectangle border{{offset.x, offset.y}, {arduboy.width(), arduboy.height()}};

    return border;
}

auto get_center_position()
{
    const auto center = tools::get_center();
    const auto x = static_cast<uint8_t>(center.first - entity_width / 2);
    const auto y = static_cast<uint8_t>(center.second - entity_height / 2);

    return game::geometry::point{x, y};
}

auto get_random_position()
{
    static const auto border = get_border(geometry::point{0, scene::base::char_height});
    const auto x = static_cast<uint8_t>(random(border.left_up.x, border.right_down.x - entity_width));
    const auto y = static_cast<uint8_t>(random(border.left_up.y, border.right_down.y - entity_height));

    return game::geometry::point{x, y};
}

template <typename Object, typename... Objects>
void update_position(Object& obj, Objects&... objects)
{
    obj.set_position(get_random_position());

    while ((obj.is_intersect(objects) || ...))
        obj.set_position(get_random_position());
}

} // namespace

gameplay::gameplay() : hero(get_center_position(), {entity_width, entity_height}, hero_default_speed),
                       project(get_random_position(), {entity_width, entity_height}),
                       adrenaline({}, {entity_width, entity_height}),
                       enemy(get_random_position(), {entity_width, entity_height}, enemy_default_speed),
                       enemy2({}, {entity_width, entity_height}, enemy_default_speed)
{
    adrenaline.hide();
    enemy2.hide();

    while (hero.is_intersect(project))
        project.set_position(get_random_position());

    while (enemy.is_intersect(hero) || enemy.is_intersect(project))
        enemy.set_position(get_random_position());
}

void gameplay::draw()
{
    draw_sprites();
    draw_status();
    process_key_press();
    process_project();
    process_adrenaline();
    process_enemy();

    auto& arduboy = game::core::get_arduboy();
    static const auto border = get_border(game::geometry::point{0, char_height});

    if (arduboy.everyXFrames(hero_frame_interval))
        hero.move(border, enemy, enemy2);

    if (arduboy.everyXFrames(enemy_frame_interval))
    {
        enemy.move(border, hero);
        enemy2.move(border, hero);
    }

    ++frame_count;

    if (!project_remaining)
    {
        to_next_level();
        auto& state = game::core::get_state();
        state.set_next_level(level_number);
        state.set_current_scene(game::core::mode::level);
        return;
    }

    if (frame_count % game::core::fps == 0)
    {
        frame_count = 0;
        --time_remaining;

        if (time_remaining == 0)
        {
            auto& state = game::core::get_state();
            state.set_last_score(hero_score);
            state.set_current_scene(game::core::mode::end);

            auto& storage = state.get_storage();
            if (const auto [is_top, _] = storage.add(hero_score); is_top)
                storage.save();

            reset();
        }
    }
}

void gameplay::reset()
{
    level_number = 0;
    hero_score = 0;
    reset_objects();
}

void gameplay::draw_sprites() const
{
    const auto hero_pos = hero.get_position();
    const auto project_pos = project.get_position();
    const auto adrenaline_pos = adrenaline.get_position();
    const auto enemy_pos = enemy.get_position();
    const auto enemy2_pos = enemy2.get_position();

    Sprites::drawOverwrite(hero_pos.x, hero_pos.y, c_icon, 0);
    Sprites::drawOverwrite(enemy_pos.x, enemy_pos.y, rust_icon, 0);
    Sprites::drawOverwrite(project_pos.x, project_pos.y, project_icon, 0);

    if (!enemy2.is_hide())
        Sprites::drawOverwrite(enemy2_pos.x, enemy2_pos.y, python_icon2, 0);

    if (!adrenaline.is_hide())
        Sprites::drawOverwrite(adrenaline_pos.x, adrenaline_pos.y, adrenaline_icon, 0);
}

void gameplay::draw_status() const
{
    auto& arduboy = game::core::get_arduboy();
    arduboy.setCursor(0, 0);
    arduboy.print(F("S:"));
    arduboy.print(hero_score);
    arduboy.print(F(";E:"));
    arduboy.print(hero.get_energy());
    arduboy.print(F(";T:"));
    arduboy.print(time_remaining);
    arduboy.print(F(";P:"));
    arduboy.print(project_remaining);
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
    else if (arduboy.justPressed(A_BUTTON))
        hero.switch_acceleration();
    else if (arduboy.justPressed(B_BUTTON))
        game::core::get_state().set_current_scene(game::core::mode::menu);
}

void gameplay::process_project()
{
    if (hero.is_intersect(project))
    {
        hero_score += scores_for_project;
        auto& beep1 = game::core::get_beep_pin1();
        beep1.tone(beep1.freq(1000), game::tools::seconds_to_frame_count(1));
        project.hide();
        --project_remaining;
    }

    if (project.is_hide())
    {
        project.show();
        update_position(project, hero, adrenaline, enemy, enemy2);
    }
}

void gameplay::process_adrenaline()
{
    if (hero.is_intersect(adrenaline))
    {
        hero.add_energy(10);
        hero_score += 1;
        auto& beep1 = game::core::get_beep_pin1();
        beep1.tone(beep1.freq(1000), game::tools::seconds_to_frame_count(1));
        adrenaline.hide();
    }

    if (adrenaline.is_hide() && adrenaline_propability > random(100))
    {
        adrenaline.show();
        update_position(adrenaline, hero, project, enemy, enemy2);
    }
}

void gameplay::process_enemy()
{
    if (enemy.is_intersect(adrenaline) || enemy2.is_intersect(adrenaline))
        adrenaline.hide();

    if (enemy.is_intersect(project) || enemy2.is_intersect(project))
        project.hide();

    const auto ai_logic = [&](auto& enemy)
    {
        const auto project_pos = project.get_position();
        const auto project_size = project.get_hitbox();
        const auto enemy_pos = enemy.get_position();
        const auto enemy_size = enemy.get_hitbox();

        if (project_pos.x >= enemy_pos.x + enemy_size.first)
            enemy.set_direction(entity::direction::right);
        else if (project_pos.x + project_size.first <= enemy_pos.x)
            enemy.set_direction(entity::direction::left);
        else if (project_pos.y >= enemy_pos.y + enemy_size.second)
            enemy.set_direction(entity::direction::down);
        else if (project_pos.y + project_size.second <= enemy_pos.y)
            enemy.set_direction(entity::direction::up);
    };

    const auto ai_logic2 = [&](auto& enemy)
    {
        const auto adrenaline_pos = adrenaline.get_position();
        const auto adrenaline_size = adrenaline.get_hitbox();
        const auto enemy_pos = enemy.get_position();
        const auto enemy_size = enemy.get_hitbox();

        if (adrenaline_pos.x >= enemy_pos.x + enemy_size.first)
            enemy.set_direction(entity::direction::right);
        else if (adrenaline_pos.x + adrenaline_size.first <= enemy_pos.x)
            enemy.set_direction(entity::direction::left);
        else if (adrenaline_pos.y >= enemy_pos.y + enemy_size.second)
            enemy.set_direction(entity::direction::down);
        else if (adrenaline_pos.y + adrenaline_size.second <= enemy_pos.y)
            enemy.set_direction(entity::direction::up);
    };

    ai_logic(enemy);

    if (!enemy2.is_hide())
    {
        if (!adrenaline.is_hide())
            ai_logic2(enemy2);
        else
            ai_logic(enemy2);
    }
}

void gameplay::to_next_level()
{
    ++level_number;
    reset_objects();
}

void gameplay::reset_objects()
{
    enemy.set_speed(enemy_default_speed + (level_number > 4 ? 4 : level_number));
    enemy2.set_speed(enemy_default_speed + (level_number > 4 ? 4 : level_number));

    if (level_number > 2)
        enemy2.show();

    project_limit = project_limit_base + project_limit_factor * level_number;
    project_remaining = project_limit;
    time_limit = time_limit_base + time_limit_factor * level_number;
    time_remaining = time_limit;
    frame_count = 0;

    adrenaline.hide();
    hero.set_position(get_center_position());

    update_position(project, hero);
    update_position(enemy, hero, project);
    update_position(enemy2, enemy, hero, project);
}

} // namespace game::scene
