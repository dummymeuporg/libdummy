#include "server/command/teleport_map.hpp"
#include "server/command/command_visitor.hpp"
#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Command {

TeleportMap::TeleportMap(
    const std::string& mapName,
    const std::pair<std::uint16_t, std::uint16_t>& destination,
    const std::string& instance
) : m_mapName(mapName), m_destination(destination), m_instance(instance)
{

}

TeleportMap::TeleportMap(
    const std::string& mapName,
    std::uint16_t x, std::uint16_t y,
    const std::string& instance
) : m_mapName(mapName), m_destination(x, y), m_instance(instance)
{
}

std::unique_ptr<const ::Dummy::Server::Response::Response>
TeleportMap::accept(::Dummy::Server::Command::CommandVisitor& visitor)
const {
    return visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
