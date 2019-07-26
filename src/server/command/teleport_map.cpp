#include <dummy/server/command/teleport_map.hpp>
#include <dummy/server/command/command_visitor.hpp>
#include <dummy/server/response/response.hpp>

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

TeleportMap::~TeleportMap()
{

}

void
TeleportMap::accept(::Dummy::Server::Command::CommandVisitor& visitor)
const {
    visitor.visitCommand(*this);
}

} // namespace Command
} // namespace Server
} // namespace Dummy
