#pragma once

#include <string>

#include "dummy/protocol/map_update/update.hpp"

namespace Dummy {
namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

namespace MapUpdate {

class LivingOff : public Update
{
public:
    LivingOff(uint32_t id);

    virtual void accept(MapUpdateVisitor&) const override;
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;

    uint32_t id() const { return m_id; }

private:
    uint32_t m_id;
};

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
