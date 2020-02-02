#include "dummy/server/game_session_state/state.hpp"
#include "dummy/server/game_session.hpp"

namespace Dummy {
namespace Server {
namespace GameSessionState {

State::State(Dummy::Server::GameSession& gameSession)
    : m_gameSession(gameSession)
{}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
