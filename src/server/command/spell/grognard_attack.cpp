#include <dummy/server/command/spell/grognard_attack.hpp>
#include <dummy/server/command/command_visitor.hpp>


namespace Dummy {
namespace Server {
namespace Command {
namespace Spell {

GrognardAttack::GrognardAttack(std::uint8_t direction)
    : m_direction(direction)
{}

void GrognardAttack::accept(CommandVisitor& visitor) const
{
    visitor.visitCommand(*this);
}

} // namespace Spell
} // namespace Command
} // namespace Server
} // namespace Dummy
