#include <dummy/server/command/connect_command.hpp>
#include <dummy/server/command/command_visitor.hpp>
#include <dummy/server/response/response.hpp>

namespace Dummy {
namespace Server {
namespace Command {

ConnectCommand::ConnectCommand(const std::string& tagName,
                               const std::string& sessionID)
    : m_tagName(tagName), m_sessionID(sessionID)
{
}

void
ConnectCommand::accept(::Dummy::Server::Command::CommandVisitor& visitor) const
{
    visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
