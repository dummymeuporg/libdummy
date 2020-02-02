#include "dummy/server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Response {

Response::Response() {}

void Response::setStatus(uint8_t status)
{
    m_status = status;
}

} // namespace Response
} // namespace Server
} // namespace Dummy
