#include <iostream>
#include <dummy/server/player.hpp>
#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/account.hpp>
#include <dummy/server/game_session.hpp>
#include <dummy/server/game_session_state/initial_state.hpp>

#include <dummy/server/command/command.hpp>
#include <dummy/server/response/response.hpp>

namespace Dummy {
namespace Server {

GameSession::GameSession(AbstractGameServer& abstractGameServer)
    : m_abstractGameServer(abstractGameServer), m_state(nullptr),
      m_account(nullptr), m_player(nullptr)
{}

GameSession::~GameSession() {
    std::cerr << "Ending game session." << std::endl;
}

void GameSession::start() {
    m_state = std::make_shared<GameSessionState::InitialState>(*this);
    m_state->resume();
}

void GameSession::close() {
    // XXX: Get the character out of the map, if needed.
    if (nullptr != m_account && nullptr != m_player) {
        m_abstractGameServer.saveCharacter(*m_account, *m_player->character());
    }
    m_state.reset();
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
GameSession::addResponse(
    std::unique_ptr<const Dummy::Server::Response::Response> response
) {
    m_responses.emplace(std::move(response));
}

void
GameSession::handleCommand(const Dummy::Server::Command::Command& command)
{
    m_state->onCommand(command);
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


} // namespace Server
} // namespace Dummy
