#pragma once

#include <cstdint>
#include <memory>
#include <optional>

namespace Dummy {
namespace Protocol {
namespace MapUpdate {
class Update;
} // namespace MapUpdate
} // namespace Protocol

namespace Server {

class Map;

class MapObserver : public std::enable_shared_from_this<MapObserver> {
public:
    MapObserver();
    MapObserver(std::uint32_t);
    MapObserver(std::uint32_t, std::weak_ptr<Map>);
    void setMap(std::weak_ptr<Map>);
    void setID(std::uint32_t);
    void resetID();
    std::uint32_t id() const {
        return m_id.value();
    }
private:
    std::optional<std::uint32_t> m_id;
    std::weak_ptr<Map> m_map;
};

} // namespace Server
} // namespace Dummy
