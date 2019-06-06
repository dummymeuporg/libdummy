#pragma once

#include <memory>

#include "server/abstract_game_server.hpp"
#include "server/map.hpp"

namespace Dummy {
namespace Server {

class Instance : public std::enable_shared_from_this<Instance> {
public:
    Instance(AbstractGameServer&);
    std::weak_ptr<Map> map(const std::string& mapName) {
        return m_maps[mapName];
    }
    void spawnMaps();
private:
    AbstractGameServer& m_abstractGameServer;
    std::map<std::string,
             std::shared_ptr<Map>> m_maps;
};

} // namespace Server
} // namespace Dummy
