#include <dummy/protocol/character.hpp>

namespace Dummy {

namespace Protocol {

Character::Character(std::uint16_t x,
                     std::uint16_t y,
                     const std::string& name,
                     const std::string& chipset,
                     Dummy::Core::Character::Direction direction)
    : Living(x, y, name, chipset, direction)
{
}

} // namespace Protocol

} // namespace Dummy
