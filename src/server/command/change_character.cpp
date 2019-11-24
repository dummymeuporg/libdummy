#include <dummy/server/command/change_character.hpp>
#include <dummy/server/command/command_visitor.hpp>

namespace Dummy {
namespace Server {
namespace Command {

void ChangeCharacter::accept(CommandVisitor& visitor) const {
    visitor.visitCommand(*this);
}



} // namespace Command
} // namespace Server
} // namespace Dummy
