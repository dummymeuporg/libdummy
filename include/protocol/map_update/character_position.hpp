#pragma once

#include <cstdint>
#include <string>
#include "protocol/map_update/update.hpp"
#include "core/character.hpp"

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

class CharacterPosition : public Update {
public:
    CharacterPosition(std::uint16_t x,
                      std::uint16_t y,
                      const std::string&,
                      Dummy::Core::Character::Direction);

        
    virtual void accept(MapUpdateVisitor&) const override;
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    const std::string& name() const {
        return m_name;
    }

    Dummy::Core::Character::Direction direction() const {
        return m_direction;
    }

protected:
    std::uint16_t m_x, m_y;
    std::string m_name;
    Dummy::Core::Character::Direction m_direction;
};

} // name MapUpdate

} // namespace Protocol

} // namespace Dummy
