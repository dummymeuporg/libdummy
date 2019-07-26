#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/protocol/map_update/map_update_visitor.hpp>
#include <dummy/protocol/map_update/character_floor.hpp>

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

CharacterFloor::CharacterFloor(const std::string& name, std::uint8_t floor)
    : m_name(name), m_floor(floor) {}

void CharacterFloor::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

void
CharacterFloor::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const {
    packet << m_name << m_floor;
}

void CharacterFloor::readFrom(Dummy::Protocol::IncomingPacket& packet) {
    packet >> m_name >> m_floor;
}

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
