#include "server/command/create_character.hpp"
#include "server/command/command_visitor.hpp"
#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Command {

CreateCharacter::CreateCharacter(const std::string& name,
                                 const std::string& skin)
    : m_name(name), m_skin(skin)
{
}

std::unique_ptr<const ::Dummy::Server::Response::Response>
CreateCharacter::accept(::Dummy::Server::Command::CommandVisitor& visitor)
const {
    return visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
