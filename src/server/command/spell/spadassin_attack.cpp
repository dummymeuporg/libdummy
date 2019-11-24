#include <dummy/server/command/spell/spadassin_attack.hpp>
#include <dummy/server/command/command_visitor.hpp>


namespace Dummy {
namespace Server {
namespace Command {
namespace Spell {

SpadassinAttack::SpadassinAttack(std::uint8_t direction)
    : m_direction(direction)
{}

} // namespace Spell
} // namespace Command
} // namespace Server
} // namespace Dummy
