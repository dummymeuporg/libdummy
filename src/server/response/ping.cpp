#include <memory>
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

} // namespace Response
} // namespace Server
} // namespace Dummy
