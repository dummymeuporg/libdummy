#include "dummy/core/foe.hpp"

namespace Dummy {
namespace Core {

Foe::Foe(const std::string& luaFilename)
    : m_luaFilename(luaFilename)
{}

/*
Foe::Foe(
    const std::string& chipset,
    uint16_t x,
    uint16_t y,
    uint8_t floor
) : m_chipset(chipset), m_position{x, y}, m_floor(floor)
{}

Foe::Foe(
    const std::string& chipset,
    const std::pair<uint16_t, uint16_t>& position,
    uint8_t floor
) : m_chipset(chipset), m_position(position), m_floor(floor)
{
}
*/

} // namespace Core
} // namespace Dummy
