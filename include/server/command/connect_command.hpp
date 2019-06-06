#pragma once

#include <string>

namespace Dummy {
namespace Server {
namespace Command {

class ConnectCommand {
public:
    ConnectCommand(const std::string&, const std::string&);

    const std::string& tagName() const {
        return m_tagName;
    }

    const std::string& sessionID() const {
        return m_sessionID;
    }
private:
    std::string m_tagName;
    std::string m_sessionID;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
