#include "dummy/server/command/set_position.hpp"

#include "dummy/server/command/command_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Command {

SetPosition::SetPosition(tilecoords xy)
    : m_xy(xy)
{}

void SetPosition::accept(CommandVisitor& visitor) const
{
    visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
