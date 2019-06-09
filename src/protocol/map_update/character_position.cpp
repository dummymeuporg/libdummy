#include "protocol/map_update/map_update_visitor.hpp"
#include "protocol/map_update/character_position.hpp"

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

CharacterPosition::CharacterPosition(
    std::uint16_t x,
    std::uint16_t y,
    const std::string& name,
    const std::string& chipset,
    Dummy::Core::Character::Direction direction
) : m_x(x), m_y(y), m_name(name), m_chipset(chipset), m_direction(direction)
{
}

void CharacterPosition::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
