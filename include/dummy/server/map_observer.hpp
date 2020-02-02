#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "dummy/utils/dummy_types.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {
class Update;
} // namespace MapUpdate
} // namespace Protocol

namespace Server {

class Map;
class MapState;

using MapUpdatesVector =
    std::vector<std::unique_ptr<Dummy::Protocol::MapUpdate::Update>>;

class MapObserver : public std::enable_shared_from_this<MapObserver>
{
public:
    MapObserver();
    MapObserver(uint32_t);
    MapObserver(uint32_t, std::weak_ptr<Map>);
    void setMap(std::weak_ptr<Map>);
    void setID(uint32_t);
    void resetID();
    uint32_t id() const { return m_id.value(); }

    virtual void notifyOn(MapUpdatesVector&)                         = 0;
    virtual void notifyPosition(MapUpdatesVector&)                   = 0;
    virtual void receiveMessage(uint32_t author, const std::string&) = 0;
    virtual tilecoords position()                                    = 0;

protected:
    std::optional<uint32_t> m_id;
    std::weak_ptr<Map> m_map;
};

} // namespace Server
} // namespace Dummy
