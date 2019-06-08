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

void
CreateCharacter::accept(::Dummy::Server::Command::CommandVisitor& visitor)
const {
    visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
