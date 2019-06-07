#include <iostream>
#include <fstream>
#include <filesystem>

#include <boost/range/iterator_range.hpp>

#include "core/character.hpp"

#include "server/abstract_game_server.hpp"
#include "server/account.hpp"
#include "server/errors.hpp"

#include "server/game_session.hpp"
#include "server/game_session_state/manage_characters_state.hpp"
#include "server/game_session_state/send_characters_state.hpp"

#include "server/command/command.hpp"
#include "server/response/characters_list_response.hpp"

namespace fs = std::filesystem;

namespace Dummy {
namespace Server {
namespace GameSessionState {

using CharactersListResponse = Dummy::Server::Response::CharactersListResponse;

SendCharactersState::SendCharactersState(GameSession& gameSession)
    : State(gameSession)
{
}

void
SendCharactersState::resume() {
}


std::unique_ptr<const ::Dummy::Server::Response::Response>
SendCharactersState::onCommand(
    const ::Dummy::Server::Command::Command& command
)
{
    auto self(shared_from_this());
    std::cerr << "[SendCharactersState] command." << std::endl;
    return command.accept(*this);
}

std::unique_ptr<const ::Dummy::Server::Response::Response>
SendCharactersState::visitCommand(
    const Dummy::Server::Command::GetPrimaryInfoCommand& command
) {
    auto self(shared_from_this());
    const Dummy::Server::AbstractGameServer& svr(
        m_gameSession.abstractGameServer()
    );
    std::unique_ptr<CharactersListResponse>
        response = std::make_unique<CharactersListResponse>(); 
    fs::path accountPath(svr.serverPath()
        / "accounts" / m_gameSession.account().name() / "characters");

    std::cerr << "AccountPath: " << accountPath.string() << std::endl;
    for (const auto& entry: fs::directory_iterator(accountPath)) {
        std::cerr << "found " << entry << std::endl;
        std::shared_ptr<Dummy::Core::Character> chr =
            std::make_shared<Dummy::Core::Character>();
        std::ifstream ifs(entry.path().string(),
                          std::ios::binary | std::ofstream::out);
        ifs >> *chr;
        response->addCharacter(chr);
    }
    std::cerr << "There are " << response->charactersList().size()
        << " characters." << std::endl;

    CharactersMap map;
    for(auto chr: response->charactersList()) {
        map[chr->name()] = chr;
    }

    std::cerr << "Will change state." << std::endl;
    m_gameSession.changeState(
        std::make_shared<ManageCharactersState>(m_gameSession, std::move(map))
    );

    return response;
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
