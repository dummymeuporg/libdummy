#include "protocol/character.hpp"

namespace Dummy {

namespace Protocol {

Character::Character(std::uint16_t x, std::uint16_t y, const std::string& name)
    : Living(x, y, name)
{
}

} // namespace Protocol

} // namespace Dummy
