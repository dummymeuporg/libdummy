#pragma once

#include <cstdint>
#include <string>
#include "protocol/map_update/character_position.hpp"
#include "core/character.hpp"

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

class CharacterOn : public CharacterPosition {
public:
    CharacterOn(std::uint16_t x,
                std::uint16_t y,
                std::uint8_t floor,
                const std::string&,
                const std::string&,
                Dummy::Core::Character::Direction);
 
    virtual void accept(MapUpdateVisitor&) const override;

    const std::string& chipset() const {
        return m_chipset;
    }

    Dummy::Core::Character::Direction direction() const {
        return m_direction;
    }

    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;
protected:
    std::string m_chipset;
    Dummy::Core::Character::Direction m_direction;
};

} // name MapUpdate

} // namespace Protocol

} // namespace Dummy
