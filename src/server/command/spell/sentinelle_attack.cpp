#include <dummy/server/command/spell/sentinelle_attack.hpp>
#include <dummy/server/command/command_visitor.hpp>


namespace Dummy {
namespace Server {
namespace Command {
namespace Spell {

SentinelleAttack::SentinelleAttack(std::uint8_t direction)
    : m_direction(direction)
{}

void SentinelleAttack::accept(CommandVisitor& visitor) const
{
    visitor.visitCommand(*this);
}


} // namespace Spell
} // namespace Command
} // namespace Server
} // namespace Dummy
