#pragma once

#include <map>
#include <memory>
#include <string>

namespace Dummy {

namespace Protocol {
class MapUpdate;
} // namespace Protocol

namespace Server {
class MapState {
public:
    using LivingsMap = std::map<std::string,
                                std::shared<ptr<Dummy::Protocol::Living>>;
    MapState();
    virtual void update(const Dummy::Protocol::MapUpdate&);
private:
    LivingsMap m_livings;
}
} // namespace Server
} // namespace Dummy
