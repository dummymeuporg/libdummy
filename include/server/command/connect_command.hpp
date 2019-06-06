#pragma once

#include <string>

#include "server/command/command.hpp"

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


    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>
    accept(::Dummy::Server::Command::CommandVisitor&) const override;
private:
    std::string m_tagName;
    std::string m_sessionID;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
