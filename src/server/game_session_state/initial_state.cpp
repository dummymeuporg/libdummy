#include <iostream>

#include "server/command/command.hpp"
#include "server/game_session_state/initial_state.hpp"
#include "server/response/response.hpp"

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

std::unique_ptr<::Dummy::Server::Response::Response>
InitialState::onCommand(const ::Dummy::Server::Command::Command& command) {
    auto self(shared_from_this());
    std::cerr << "[InitialState] command." << std::endl;
    return command.accept(*this);
}

std::unique_ptr<::Dummy::Server::Response::Response>
InitialState::visitCommand(
    const Dummy::Server::Command::ConnectCommand& connectCommand
) {
    // XXX: connect the account and return a connect response accordingly.
    return nullptr;
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
