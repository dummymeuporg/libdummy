#include "protocol/map_update/map_update_visitor.hpp"
#include "protocol/map_update/character_off.hpp"

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

CharacterOff::CharacterOff(const std::string& name) : m_name(name) {}

void CharacterOff::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
