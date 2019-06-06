#include "server/response/connect_response.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void ConnectResponse::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
