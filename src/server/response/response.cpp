#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Response {

Response::Response()
{}

void Response::setStatus(Response::Status status) {
    m_status = status;
}

} // namespace Response
} // namespace Server
} // namespace Dummy
