#pragma once

#include <map>
#include <memory>
#include <string>

#include "protocol/map_update/map_update_visitor.hpp"

namespace Dummy {

namespace Protocol {
class Living;

namespace MapUpdate {
class Update;
}

} // namespace Protocol

namespace Server {
class MapState : public Dummy::Protocol::MapUpdate::MapUpdateVisitor {
public:
    using LivingsMap = std::map<std::string,
                                std::shared_ptr<Dummy::Protocol::Living>>;
    MapState();
    void update(const Dummy::Protocol::MapUpdate::Update&);
private:
    LivingsMap m_livings;
};

} // namespace Server
} // namespace Dummy
