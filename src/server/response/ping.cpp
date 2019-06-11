#include <memory>
#include "protocol/outgoing_packet.hpp"
#include "protocol/incoming_packet.hpp"
#include "protocol/map_update/update.hpp"
#include "server/response/response_visitor.hpp"
#include "server/response/ping.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void Ping::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void
Ping::addUpdate(std::unique_ptr<Dummy::Protocol::MapUpdate::Update> update) {
    m_mapUpdates.push_back(std::move(update));
}

void Ping::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const {

}

void Ping::readFrom(Dummy::Protocol::IncomingPacket& packet) {

}

} // namespace Response
} // namespace Server
} // namespace Dummy
