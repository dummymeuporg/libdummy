#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

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
    MapObserver(std::uint32_t);
    MapObserver(std::uint32_t, std::weak_ptr<Map>);
    void setMap(std::weak_ptr<Map>);
    void setID(std::uint32_t);
    void resetID();
    std::uint32_t id() const { return m_id.value(); }

    virtual void notifyOn(MapUpdatesVector&)                              = 0;
    virtual void notifyPosition(MapUpdatesVector&)                        = 0;
    virtual void receiveMessage(std::uint32_t author, const std::string&) = 0;
    virtual std::pair<std::uint16_t, std::uint16_t> position()            = 0;

protected:
    std::optional<std::uint32_t> m_id;
    std::weak_ptr<Map> m_map;
};

} // namespace Server
} // namespace Dummy
