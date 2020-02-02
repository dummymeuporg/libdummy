#include "dummy/server/command/message.hpp"
#include "dummy/server/command/command_visitor.hpp"
#include "dummy/server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Command {

Message::Message(const std::string& content)
    : m_content(content)
{}

void Message::accept(CommandVisitor& visitor) const
{
    visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
