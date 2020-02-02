#pragma once

#include "dummy/core/character.hpp"
#include "dummy/protocol/map_update/update.hpp"
#include <cstdint>
#include <string>

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

class CharacterPosition : public Update
{
public:
    CharacterPosition(std::uint32_t id, std::uint16_t x, std::uint16_t y,
                      Dummy::Core::Character::Direction);


    virtual void accept(MapUpdateVisitor&) const override;
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;

    std::uint16_t x() const { return m_x; }
    std::uint16_t y() const { return m_y; }
    Dummy::Core::Character::Direction direction() const { return m_direction; }
    std::uint32_t id() const { return m_id; }

protected:
    std::uint32_t m_id;
    std::uint16_t m_x, m_y;
    Dummy::Core::Character::Direction m_direction;
};

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
