#include "server/game_session.hpp"
#include "server/game_session_state/state.hpp"

namespace Dummy {
namespace Server {
namespace GameSessionState {

State::State(Dummy::Server::GameSession& gameSession)
    : m_gameSession(gameSession)
{}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
