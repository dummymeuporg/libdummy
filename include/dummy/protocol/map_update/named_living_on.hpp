#pragma once

#include <cstdint>
#include <string>
#include <dummy/protocol/map_update/character_position.hpp>
#include <dummy/core/character.hpp>

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

class LivingOn : public CharacterPosition {
public:
    LivingOn(std::uint32_t id,
             std::uint16_t x,
             std::uint16_t y,
             std::uint8_t floor,
             const std::string&,
             Dummy::Core::Character::Direction);
 
    virtual void accept(MapUpdateVisitor&) const override;

    const std::string& chipset() const {
        return m_chipset;
    }

    Dummy::Core::Character::Direction direction() const {
        return m_direction;
    }

    std::uint8_t floor() const {
        return m_floor;
    }

    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;
protected:
    std::string m_chipset;
    std::uint8_t m_floor;
};

} // name MapUpdate

} // namespace Protocol

} // namespace Dummy
