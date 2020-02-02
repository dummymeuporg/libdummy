#pragma once

#include <memory>
#include <string>

#include <boost/uuid/uuid.hpp>

namespace Dummy {
namespace Core {

class Account
{
public:
    Account(const std::string&, boost::uuids::uuid);

    inline const std::string& name() const { return m_name; }
    const boost::uuids::uuid& sessionUUID() const { return *m_sessionUUID; }

private:
    std::string m_name;
    std::shared_ptr<boost::uuids::uuid> m_sessionUUID;
};

} // namespace Core
} // namespace Dummy
