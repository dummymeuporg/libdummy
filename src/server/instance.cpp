#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/instance.hpp>
#include <dummy/server/map.hpp>

namespace Dummy {
namespace Server {

Instance::Instance(AbstractGameServer& abstractGameServer) :
    m_abstractGameServer(abstractGameServer) 
{}

void Instance::spawnMaps() {
    // XXX: simplify it
    const Dummy::Server::Project& project(m_abstractGameServer.project());
    for (auto const &projectMap : project.maps()) {
        std::cerr << "Spawn map " << projectMap.first << std::endl;
        m_maps[projectMap.first] = std::make_shared<Map>(
            *this, *projectMap.second
        );
    }
}

} // namespace Server
} // namespace Dummy
