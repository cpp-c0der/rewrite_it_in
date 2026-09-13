#ifndef TOP_STORAGE_H
#define TOP_STORAGE_H

#include "tools.h"

#include <stdint.h>

namespace game::core
{

class top_storage final
{
public:
    static inline constexpr auto count = uint8_t(5);

    top_storage();

    void save();
    tools::pair<bool, uint8_t> add(uint32_t value);

    const auto& get_top() const
    {
        return top;
    }

private:
    void read();

    uint32_t top[count];

    static inline constexpr auto magic = uint32_t(426661111);
    static inline constexpr auto offset = sizeof(magic) + sizeof(top[0]);
};

} // namespace game::core

#endif
