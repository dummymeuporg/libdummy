#pragma once

#include <cstdint>
#include <string>

#include "dummy/core/character.hpp"
#include "dummy/protocol/map_update/update.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

class CharacterPosition : public Update
{
public:
    CharacterPosition(uint32_t id, tilecoords,
                      Dummy::Core::Character::Direction);


    virtual void accept(MapUpdateVisitor&) const override;
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;

    tilecoords pos() const { return m_xy; }
    Dummy::Core::Character::Direction direction() const { return m_direction; }
    uint32_t id() const { return m_id; }

protected:
    uint32_t m_id;
    tilecoords m_xy;
    Dummy::Core::Character::Direction m_direction;
};

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
