#include "dummy/server/command/ping.hpp"
#include "dummy/server/command/command_visitor.hpp"
#include "dummy/server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Command {

Ping::Ping() {}

void Ping::accept(CommandVisitor& visitor) const
{
    visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
