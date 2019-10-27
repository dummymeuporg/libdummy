#include <memory>

#include <dummy/server/map_observer.hpp>

namespace Dummy {
namespace Server {


class Player;

class MapObserverPlayer : public MapObserver {
public:
    MapObserverPlayer(std::uint32_t, std::weak_ptr<Player>);
private:
    std::weak_ptr<Player> m_player;
};

}
}
