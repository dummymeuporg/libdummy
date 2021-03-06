#include <dummy/protocol/character.hpp>

namespace Dummy {

namespace Protocol {

Character::Character(std::uint32_t id,
                     std::uint16_t x,
                     std::uint16_t y,
                     std::uint8_t floor,
                     const std::string& name,
                     const std::string& chipset,
                     Dummy::Core::Character::Direction direction)
    : Living(id, x, y, floor, chipset, direction)
{
}

} // namespace Protocol

} // namespace Dummy
