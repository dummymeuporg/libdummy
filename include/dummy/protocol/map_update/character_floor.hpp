#pragma once

#include <string>
#include "dummy/protocol/map_update/update.hpp"

namespace Dummy {
namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

namespace MapUpdate {

class CharacterFloor : public Update {
public:
    CharacterFloor(const std::string&, std::uint8_t);

    void accept(MapUpdateVisitor&) const override;
    void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    void readFrom(Dummy::Protocol::IncomingPacket&) override;

    const std::string& name() const {
        return m_name;
    }

    std::uint8_t floor() const {
        return m_floor;
    }
private:
    std::string m_name;
    std::uint8_t m_floor;
};

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
