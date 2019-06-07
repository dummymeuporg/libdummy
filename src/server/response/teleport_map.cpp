#include "server/response/teleport_map.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void TeleportMap::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
