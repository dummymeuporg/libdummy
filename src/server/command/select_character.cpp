#include "dummy/server/command/select_character.hpp"

#include "dummy/server/command/command_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Command {

SelectCharacter::SelectCharacter(const std::string& name)
    : m_name(name)
{}

void SelectCharacter::accept(CommandVisitor& visitor) const
{
    visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
