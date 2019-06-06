#include "server/abstract_game_server.hpp"
#include "server/game_session.hpp"
#include "server/game_session_state/loading_state.hpp"
#include "server/game_session_state/playing_state.hpp"
#include "server/player.hpp"
#include "server/map.hpp"


namespace Dummy {
namespace Server {
namespace GameSessionState {

LoadingState::LoadingState(GameSession& gameSession,
                           Dummy::Protocol::TeleportRequest&& teleportRequest)
    : State(gameSession),
      m_teleportRequest(std::move(teleportRequest))
{

}

void LoadingState::resume() {
    std::cerr << "[LoadingState]" << std::endl;
}


} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
