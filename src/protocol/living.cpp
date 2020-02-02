#include "dummy/protocol/living.hpp"

namespace Dummy {
namespace Protocol {

Living::Living(uint32_t id, tilecoords xy, uint8_t floor,
               const std::string& chipset,
               Dummy::Core::Character::Direction direction)
    : m_id(id)
    , m_xy(xy)
    , m_floor(floor)
    , m_chipset(chipset)
    , m_direction(direction)
{}

void Living::setPosition(tilecoords xy)
{
    m_xy = xy;
}

void Living::setDirection(Dummy::Core::Character::Direction direction)
{
    m_direction = direction;
}

void Living::setChipset(const std::string& chipset)
{
    m_chipset = chipset;
}

} // namespace Protocol
} // namespace Dummy
