#include "server/command/connect_command.hpp"
#include "server/command/command_visitor.hpp"
#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Command {

ConnectCommand::ConnectCommand(const std::string& tagName,
                               const std::string& sessionID)
    : m_tagName(tagName), m_sessionID(sessionID)
{
}

std::unique_ptr<::Dummy::Server::Response::Response>
ConnectCommand::accept(::Dummy::Server::Command::CommandVisitor& visitor) const
{
    return visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
