#pragma once

#include <cstdint>
#include <string>

#include "dummy/protocol/map_update/character_position.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

class NamedLivingOn : public CharacterPosition
{
public:
    NamedLivingOn(uint32_t id, tilecoords xy,
                  uint8_t floor, const std::string&, const std::string&,
                  Dummy::Core::Character::Direction);

    virtual void accept(MapUpdateVisitor&) const override;

    const std::string& chipset() const { return m_chipset; }

    const std::string& name() const { return m_name; }

    Dummy::Core::Character::Direction direction() const { return m_direction; }

    uint8_t floor() const { return m_floor; }

    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;

protected:
    std::string m_name;
    std::string m_chipset;
    uint8_t m_floor;
};

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
