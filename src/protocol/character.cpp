#include "dummy/protocol/character.hpp"

namespace Dummy {
namespace Protocol {

Character::Character(uint32_t id, tilecoords xy, uint8_t floor,
                     const std::string& name, const std::string& chipset,
                     Dummy::Core::Character::Direction direction)
    : Living(id, xy, floor, chipset, direction)
{}

} // namespace Protocol
} // namespace Dummy
