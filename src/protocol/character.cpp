#include "protocol/character.hpp"

namespace Dummy {

namespace Protocol {

Character::Character(std::uint16_t x,
                     std::uint16_t y,
                     const std::string& name,
                     const std::string& chipset)
    : Living(x, y, name, chipset)
{
}

} // namespace Protocol

} // namespace Dummy
