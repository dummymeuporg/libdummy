#include "dummy/server/account.hpp"

namespace Dummy {
namespace Server {

Account::Account(const std::string& name, const std::string& sessionID)
    : m_name(name)
    , m_sessionID(sessionID)
{}

} // namespace Server
} // namespace Dummy
