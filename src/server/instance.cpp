#include "dummy/server/abstract_game_server.hpp"
#include "dummy/server/instance.hpp"
#include "dummy/server/map.hpp"

namespace Dummy {
namespace Server {

Instance::Instance(
    AbstractGameServer& abstractGameServer,
    boost::asio::io_context& ioContext,
    const std::string& name) :
    m_abstractGameServer(abstractGameServer), m_ioContext(ioContext),
    m_name(name)
{}


void Instance::addPlayer(const std::string& name, std::weak_ptr<Player> player)
{
    m_players[name] = player;
}

void Instance::removePlayer(const std::string& name) {
    m_players.erase(name);
}

std::weak_ptr<Map> Instance::map(const std::string& name) {
    if (m_maps.find(name) == std::end(m_maps)) {
        // Ensure that the map exists by its name.
        const Dummy::Server::Project& project(m_abstractGameServer.project());
        if (project.maps().find(name) == std::end(project.maps())) {
            // XXX: throw an exception.
        }

        // Spawn the map.
        std::cerr << "Spawning map " << name << std::endl;
        m_maps[name] = std::make_shared<Map>(
            *this, *project.maps().at(name), m_ioContext
        );
        m_maps[name]->spawn();

    }
    return m_maps[name];
}

} // namespace Server
} // namespace Dummy
