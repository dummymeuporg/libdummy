#include "dummy/server/command/get_primary_info_command.hpp"
#include "dummy/server/command/command_visitor.hpp"
#include "dummy/server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Command {

GetPrimaryInfoCommand::GetPrimaryInfoCommand() {}

void
GetPrimaryInfoCommand::accept(
    ::Dummy::Server::Command::CommandVisitor& visitor
) const {
    visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
