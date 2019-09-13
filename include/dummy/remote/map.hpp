#pragma once

#include <vector>

#include <dummy/core/blocking_layer.hpp>
#include <dummy/core/map.hpp>


namespace Dummy {
namespace Server {
class Project;
} // namespace Server
namespace Remote {

class Map : public Core::Map {
public:
    Map(const Dummy::Server::Project&, const std::string&);

    void load() override;
protected:
    int luaOnTouchEvent(::lua_State*) override;
private:
    const Dummy::Server::Project& m_project;
    std::vector<Dummy::Core::BlockingLayer> m_floors;
};

} // namespace Remote
} // namespace Dummy
