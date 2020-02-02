#pragma once

#include <string>

#include "dummy/server/command/command.hpp"

namespace Dummy {
namespace Server {
namespace Command {

class ConnectCommand : public Command {
public:
    ConnectCommand(const std::string&, const std::string&);

    const std::string& tagName() const {
        return m_tagName;
    }

    const std::string& sessionID() const {
        return m_sessionID;
    }

    virtual void
    accept(::Dummy::Server::Command::CommandVisitor&) const override;
private:
    std::string m_tagName;
    std::string m_sessionID;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
