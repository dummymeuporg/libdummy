#pragma once

#include <memory>

namespace Dummy {

namespace Server {

class Account
{
public:
    Account(const std::string&, const std::string&);

    const std::string& name() const {
        return m_name;
    }

    const std::string& sessionID() const {
        return m_sessionID;
    }

private:
    std::string m_name;
    std::string m_sessionID;
};

} // namespace Server

} // namepsace Dummy
