#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Response {

Response::Response()
{}

void Response::setStatus(std::uint8_t status) {
    m_status = status;
}

} // namespace Response
} // namespace Server
} // namespace Dummy
