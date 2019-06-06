#include <iostream>

#include "server/game_session_state/initial_state.hpp"

namespace Dummy {
namespace Server {
namespace GameSessionState {

InitialState::InitialState(Dummy::Server::GameSession& gameSession)
    : State(gameSession)
{

}

void InitialState::resume()
{
    std::cerr << "[InitialState] resume." << std::endl;
}

void
InitialState::onCommand(const ::Dummy::Server::Command::Command& command) {
    std::cerr << "[InitialState] command." << std::endl;
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
