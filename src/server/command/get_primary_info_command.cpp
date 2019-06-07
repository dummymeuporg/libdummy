#include "server/command/get_primary_info_command.hpp"
#include "server/command/command_visitor.hpp"
#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Command {

GetPrimaryInfoCommand::GetPrimaryInfoCommand() {}

std::unique_ptr<const ::Dummy::Server::Response::Response>
GetPrimaryInfoCommand::accept(
    ::Dummy::Server::Command::CommandVisitor& visitor
) const {
    return visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy