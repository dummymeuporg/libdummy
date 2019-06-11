#include "server/command/set_position.hpp"
#include "server/command/command_visitor.hpp"
#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Command {

SetPosition::SetPosition(std::uint16_t x, std::uint16_t y)
    : m_x(y), m_y(y) {}

void SetPosition::accept(CommandVisitor& visitor) const {
    visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
