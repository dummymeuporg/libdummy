#include <iostream>
#include <fstream>
#include <filesystem>

#include <boost/range/iterator_range.hpp>

#include <dummy/core/character.hpp>

#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/account.hpp>
#include <dummy/server/errors.hpp>

#include <dummy/server/game_session.hpp>
#include <dummy/server/game_session_state/manage_characters_state.hpp>
#include <dummy/server/game_session_state/send_characters_state.hpp>

#include <dummy/server/command/command.hpp>
#include <dummy/server/response/characters_list_response.hpp>

namespace fs = std::filesystem;

namespace Dummy {
namespace Server {
namespace GameSessionState {

using CharactersListResponse = Dummy::Server::Response::CharactersListResponse;

SendCharactersState::SendCharactersState(GameSession& gameSession)
    : State(gameSession)
{
}

void SendCharactersState::resume() {
}


void SendCharactersState::onCommand(
    const ::Dummy::Server::Command::Command& command
)
{
    std::cerr << "[SendCharactersState] command." << std::endl;
    return command.accept(*this);
}

void SendCharactersState::visitCommand(
    const Dummy::Server::Command::GetPrimaryInfoCommand& command
) {
    auto self(shared_from_this());

    auto response = std::make_shared<CharactersListResponse>();

    // Retrieve the account's characters list.
    CharactersMap&& map(m_gameSession.getCharactersList());

    for (const auto& [name, chr]: map) {
        response->addCharacter(chr);
    }

    std::cerr << "Will change state." << std::endl;
    m_gameSession.changeState(
        std::make_shared<ManageCharactersState>(m_gameSession, std::move(map))
    );
    m_gameSession.addResponse(std::move(response));
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
