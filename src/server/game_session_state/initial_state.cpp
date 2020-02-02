#include "dummy/server/game_session_state/initial_state.hpp"

#include <iostream>

#include "dummy/server/abstract_game_server.hpp"
#include "dummy/server/command/command.hpp"
#include "dummy/server/command/connect_command.hpp"
#include "dummy/server/game_session.hpp"
#include "dummy/server/game_session_state/send_characters_state.hpp"
#include "dummy/server/response/connect_response.hpp"

namespace Dummy {
namespace Server {
namespace GameSessionState {

InitialState::InitialState(Dummy::Server::GameSession& gameSession)
    : State(gameSession)
{}

void InitialState::resume()
{
    std::cerr << "[InitialState] resume." << std::endl;
}

void InitialState::onCommand(const ::Dummy::Server::Command::Command& command)
{
    std::cerr << "[InitialState] command." << std::endl;
    command.accept(*this);
}

void InitialState::visitCommand(
    const Dummy::Server::Command::ConnectCommand& connectCommand)
{
    auto self(shared_from_this());
    ::Dummy::Server::AbstractGameServer& server(
        m_gameSession.abstractGameServer());

    std::shared_ptr<Dummy::Server::Response::ConnectResponse> response =
        std::make_shared<Dummy::Server::Response::ConnectResponse>();

    // XXX: connect the account and return a connect response accordingly.
    std::cerr << "Tagname is: " << connectCommand.tagName() << std::endl;

    try {
        m_gameSession.setAccount(server.connect(connectCommand.sessionID(),
                                                connectCommand.tagName()));
        response->setStatus(0); /* O.K. */
        m_gameSession.changeState(
            std::make_shared<SendCharactersState>(m_gameSession));
    } catch (const Dummy::Server::GameServerError& e) {
        std::cerr << "Could not connect " << connectCommand.tagName()
                  << " with session id " << connectCommand.sessionID() << ": "
                  << e.what() << std::endl;
        response->setStatus(e.code());
    }
    m_gameSession.addResponse(std::move(response));
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
