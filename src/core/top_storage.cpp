#include "core/top_storage.h"

#include <Arduboy2.h>
#include <EEPROM.h>

namespace game::core
{

top_storage::top_storage()
{
    read();
}

void top_storage::read()
{
    for (uint8_t i = 0; i < count; ++i)
    {
        uint32_t m;
        EEPROM.get(EEPROM_STORAGE_SPACE_START + i * offset, m);

        if (m != magic)
        {
            top[i] = 0;
            continue;
        }

        EEPROM.get(EEPROM_STORAGE_SPACE_START + i * offset + sizeof(magic), top[i]);
    }
}

tools::pair<bool, uint8_t> top_storage::add(uint32_t value)
{
    bool found = false;
    uint8_t index = 0;

    for (uint8_t i = 0; i < count; ++i)
    {
        if (value > top[i])
        {
            found = true;
            index = i;
            break;
        }
    }

    if (!found)
        return {false, 0};

    for (uint8_t i = index + 1; i < count; ++i)
        top[i] = top[i - 1];

    top[index] = value;

    return {true, index};
}

void top_storage::save()
{
    for (uint8_t i = 0; i < count; ++i)
    {
        EEPROM.put(EEPROM_STORAGE_SPACE_START + i * offset, magic);
        EEPROM.put(EEPROM_STORAGE_SPACE_START + i * offset + sizeof(magic), top[i]);
    }
}

} // namespace game::core
