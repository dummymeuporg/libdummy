#include "server/command/connect_command.hpp"

namespace Dummy {
namespace Server {
namespace Command {

ConnectCommand::ConnectCommand(const std::string& tagName,
                               const std::string& sessionID)
    : m_tagName(tagName), m_sessionID(sessionID)
{
}

} // namespace Command
} // namespace Server
} // namespace Dummy
