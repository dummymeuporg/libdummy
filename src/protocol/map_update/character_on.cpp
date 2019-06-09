#include "protocol/map_update/map_update_visitor.hpp"
#include "protocol/map_update/character_on.hpp"

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

CharacterOn::CharacterOn(std::uint16_t x,
                         std::uint16_t y,
                         const std::string& name,
                         const std::string& chipset,
                         Dummy::Core::Character::Direction direction)
    : CharacterPosition(x, y, name), m_chipset(chipset),
      m_direction(direction)
{
}

void CharacterOn::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy