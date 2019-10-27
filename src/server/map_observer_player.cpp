#include <dummy/server/map_observer_player.hpp>

namespace Dummy {
namespace Server {

MapObserverPlayer::MapObserverPlayer(
    std::uint32_t id,
    std::weak_ptr<Player> player
) : MapObserver(id), m_player(player)
{}

} // namespace Server
} // namespace Dummy
