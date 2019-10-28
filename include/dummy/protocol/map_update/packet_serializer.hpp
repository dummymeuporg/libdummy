#pragma once

#include <dummy/protocol/map_update/map_update_visitor.hpp>

namespace Dummy {
namespace Protocol {
class OutgoingPacket;
namespace MapUpdate {

class Update;
class LivingOff;
class LivingOn;
class NamedLivingOn;
class CharacterPosition;

class PacketSerializer : public MapUpdateVisitor {
public:
    PacketSerializer(OutgoingPacket&);
    void visit(const Update&);
    void visitMapUpdate(const CharacterFloor&) override;
    void visitMapUpdate(const LivingOff&) override;
    void visitMapUpdate(const LivingOn&) override;
    void visitMapUpdate(const NamedLivingOn&) override;
    void visitMapUpdate(const CharacterPosition&) override;
private:
    Dummy::Protocol::OutgoingPacket& m_packet;
};

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
