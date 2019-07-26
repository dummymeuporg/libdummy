#pragma once

#include <dummy/protocol/map_update/map_update_visitor.hpp>

namespace Dummy {
namespace Protocol {
class OutgoingPacket;
namespace MapUpdate {

class Update;
class CharacterOff;
class CharacterOn;
class CharacterPosition;

class PacketSerializer : public MapUpdateVisitor {
public:
    PacketSerializer(OutgoingPacket&);
    void visit(const Update&);
    void visitMapUpdate(const CharacterFloor&) override;
    void visitMapUpdate(const CharacterOff&) override;
    void visitMapUpdate(const CharacterOn&) override;
    void visitMapUpdate(const CharacterPosition&) override;
private:
    Dummy::Protocol::OutgoingPacket& m_packet;
};

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
