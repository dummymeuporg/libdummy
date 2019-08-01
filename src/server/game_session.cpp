#include <iostream>
#include <dummy/server/player.hpp>
#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/account.hpp>
#include <dummy/server/game_session.hpp>
#include <dummy/server/game_session_state/initial_state.hpp>

#include <dummy/server/command/command.hpp>
#include <dummy/server/response/response.hpp>
#include <dummy/server/response/message.hpp>

#include <dummy/server/game_session_communicator.hpp>


namespace Dummy {
namespace Server {

GameSession::GameSession(
    AbstractGameServer& abstractGameServer,
    std::shared_ptr<GameSessionCommunicator> gameSessionCommunicator,
    boost::asio::io_context& ioContext
)
    : m_abstractGameServer(abstractGameServer),
      m_gameSessionCommunicator(gameSessionCommunicator),
      m_ioContext(ioContext),
      m_state(nullptr),
      m_account(nullptr),
      m_player(nullptr),
      m_open(false)
{

}

GameSession::~GameSession() {
    std::cerr << "Ending game session." << std::endl;
}

void GameSession::start() {
    m_gameSessionCommunicator->setCommandHandler(shared_from_this());
    m_state = std::make_shared<GameSessionState::InitialState>(*this);
    m_open = true;
    m_state->resume();
}

void GameSession::close() {
    // XXX: Get the character out of the map, if needed.
    auto self(shared_from_this());
    if (nullptr != m_account && nullptr != m_player) {
        m_abstractGameServer.saveCharacter(*m_account, *m_player->character());
    }
    m_state.reset();
    m_abstractGameServer.removeSession(self);
    m_open = false;
}

void GameSession::changeState(std::shared_ptr<GameSessionState::State> state) {
    m_state = state;
}

void GameSession::setAccount(std::shared_ptr<Account> account) {
    m_account = account;
}

void GameSession::setPlayer(std::shared_ptr<Player> player) {
    m_player = player;
}

void
GameSession::addResponse(ResponsePtr response) {
    //m_responses.emplace(std::move(response));
    m_gameSessionCommunicator->forwardResponse(response);
}

void GameSession::handleCommand(CommandPtr command) {
    m_state->onCommand(*command);
}

void GameSession::responseHandlerClosed() {
    m_gameSessionCommunicator = nullptr;
    close();
}

std::unique_ptr<const Dummy::Server::Response::Response>
GameSession::getResponse() {
    if (m_responses.size() > 0) {
        std::unique_ptr<const Dummy::Server::Response::Response> r(
            std::move(m_responses.front())
        );
        m_responses.pop();
        return r;
    }
    return nullptr; // no response
}

void GameSession::receiveMessage(
    const std::string& author,
    const std::string& content
) {
    auto message(std::make_unique<Dummy::Server::Response::Message>());
    message->setAuthor(author);
    message->setContent(content);
    addResponse(std::move(message));
}


} // namespace Server
} // namespace Dummy
