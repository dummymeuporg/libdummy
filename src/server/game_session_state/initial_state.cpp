#include <iostream>

#include "server/abstract_game_server.hpp"
#include "server/game_session.hpp"
#include "server/command/command.hpp"
#include "server/command/connect_command.hpp"
#include "server/game_session_state/initial_state.hpp"
#include "server/response/connect_response.hpp"

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
    ::Dummy::Server::AbstractGameServer& server(
        m_gameSession.abstractGameServer()
    );

    std::unique_ptr<Dummy::Server::Response::ConnectResponse> response =
        std::make_unique<Dummy::Server::Response::ConnectResponse>();
    
    // XXX: connect the account and return a connect response accordingly.
    std::cerr << "Tagname is: " << connectCommand.tagName() << std::endl;

    try {
        server.connect(connectCommand.sessionID(),
                       connectCommand.tagName());
        response->setStatus(0); /* O.K. */
    } catch(const Dummy::Server::GameServerError& e) {
        std::cerr << "Could not connect " << connectCommand.tagName()
            << " with session id " << connectCommand.sessionID() << ": "
            << e.what() << std::endl;
        response->setStatus(e.code());
    }
    return response;
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
