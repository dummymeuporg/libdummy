#include "server/command/select_character.hpp"
#include "server/command/command_visitor.hpp"
#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Command {

SelectCharacter::SelectCharacter(const std::string& name)
    : m_name(name)
{
}

std::unique_ptr<const ::Dummy::Server::Response::Response>
SelectCharacter::accept(::Dummy::Server::Command::CommandVisitor& visitor)
const {
    return visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
