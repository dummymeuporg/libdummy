#pragma once

#include <cstdint>
#include <string>
#include <dummy/protocol/map_update/character_position.hpp>
#include <dummy/core/character.hpp>

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

class NamedLivingOn : public CharacterPosition {
public:
    NamedLivingOn(std::uint32_t id,
                  std::uint16_t x,
                  std::uint16_t y,
                  std::uint8_t floor,
                  std::uint8_t velocity,
                  const std::string&,
                  const std::string&,
                  Dummy::Core::Character::Direction);
 
    virtual void accept(MapUpdateVisitor&) const override;

    const std::string& chipset() const {
        return m_chipset;
    }

    const std::string& name() const {
        return m_name;
    }

    Dummy::Core::Character::Direction direction() const {
        return m_direction;
    }

    std::uint8_t floor() const {
        return m_floor;
    }

    std::uint8_t velocity() const {
        return m_velocity;
    }

    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;
protected:
    std::string m_name;
    std::string m_chipset;
    std::uint8_t m_floor;
    std::uint8_t m_velocity;
};

} // name MapUpdate

} // namespace Protocol

} // namespace Dummy
