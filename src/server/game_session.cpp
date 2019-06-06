#include "server/game_session.hpp"
#include "server/game_session_state/initial_state.hpp"

namespace Dummy {
namespace Server {

GameSession::GameSession(AbstractGameServer& abstractGameServer)
    : m_abstractGameServer(abstractGameServer), m_state(nullptr)
{}

void GameSession::start() {
    m_state = std::make_shared<GameSessionState::InitialState>(*this);
    m_state->resume();
}

void GameSession::changeState(std::shared_ptr<GameSessionState::State> state) {
    m_state = state;
    m_state->resume();
}

void
GameSession::handleCommand(
    std::unique_ptr<Dummy::Server::Command::Command> command
)
{
    m_state->onCommand(*command);
}

} // namespace Server
} // namespace Dummy
