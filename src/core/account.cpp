#include <dummy/core/account.hpp>

namespace Dummy {

namespace Core {


Account::Account(const std::string& name, boost::uuids::uuid sessionUUID)
    : m_name(name), m_sessionUUID(new boost::uuids::uuid(sessionUUID))
{
}

} // namespace Core

} // namespace Dummy
