#include "dummy/protocol/named_living.hpp"

namespace Dummy {
namespace Protocol {

NamedLiving::NamedLiving(uint32_t id, tilecoords xy, uint8_t floor,
                         const std::string& name, const std::string& chipset,
                         Dummy::Core::Character::Direction direction)
    : Living(id, xy, floor, chipset, direction)
    , m_name(name)
{}

void NamedLiving::setName(const std::string& name)
{
    m_name = name;
}

} // namespace Protocol
} // namespace Dummy
