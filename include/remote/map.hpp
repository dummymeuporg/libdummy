#pragma once

#include <vector>

#include "core/blocking_layer.hpp"
#include "core/map.hpp"


namespace Dummy {
namespace Server {
class Project;
} // namespace Server
namespace Remote {

class Map : public Core::Map {
public:
    Map(const Dummy::Server::Project&, const std::string&);

    void load() override;

private:
    const Dummy::Server::Project& m_project;
    std::vector<Dummy::Core::BlockingLayer> m_floors;
};

} // namespace Remote
} // namespace Dummy
