#include "dummy/core/foe.hpp"

namespace Dummy {
namespace Core {

Foe::Foe(const std::string& luaFilename) : m_luaFilename(luaFilename) {}

/*
Foe::Foe(
    const std::string& chipset,
    std::uint16_t x,
    std::uint16_t y,
    std::uint8_t floor
) : m_chipset(chipset), m_position{x, y}, m_floor(floor)
{}

Foe::Foe(
    const std::string& chipset,
    const std::pair<std::uint16_t, std::uint16_t>& position,
    std::uint8_t floor
) : m_chipset(chipset), m_position(position), m_floor(floor)
{
}
*/

} // namespace Core
} // namespace Dummy
