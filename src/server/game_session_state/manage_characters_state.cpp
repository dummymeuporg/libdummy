#include <iostream>
#include <fstream>

#include <boost/range/iterator_range.hpp>

#include "core/character.hpp"

#include "server/command/command.hpp"
#include "server/command/create_character.hpp"
#include "server/command/select_character.hpp"
#include "server/response/create_character.hpp"
#include "server/response/select_character.hpp"
#include "server/abstract_game_server.hpp"
#include "server/game_session.hpp"
#include "server/game_session_state/loading_state.hpp"
#include "server/game_session_state/manage_characters_state.hpp"
#include "server/player.hpp"


namespace Dummy {
namespace Server {
namespace GameSessionState {

ManageCharactersState::ManageCharactersState(
    GameSession& gameSession,
    CharactersMap&& characters
) : State(gameSession), m_charactersMap(std::move(characters))
{
}

void ManageCharactersState::resume() {
}

std::unique_ptr<const ::Dummy::Server::Response::Response>
ManageCharactersState::onCommand(
    const ::Dummy::Server::Command::Command& command
)
{
    return command.accept(*this);
}

std::unique_ptr<const ::Dummy::Server::Response::Response>
ManageCharactersState::visitCommand(
    const Dummy::Server::Command::SelectCharacter& selectCharacter
) {

    auto self(shared_from_this());

    std::unique_ptr<Dummy::Server::Response::SelectCharacter> response =
        std::make_unique<Dummy::Server::Response::SelectCharacter>();

    if (m_charactersMap.find(selectCharacter.name())
            == std::end(m_charactersMap)
    ) {
        response->setStatus(SelectCharacterError::Code::CHARACTER_NOT_FOUND);
    } else {
        auto chr = m_charactersMap[selectCharacter.name()];
        std::shared_ptr<Dummy::Server::Player> player =
            std::make_shared<Dummy::Server::Player>(m_gameSession, chr);

        std::cerr << "Set player..." << std::endl;
        m_gameSession.setPlayer(player);

        Dummy::Protocol::TeleportRequest teleportRequest(
            chr->mapLocation(), chr->position(), "main"
        );
        m_gameSession.changeState(
            std::make_shared<LoadingState>(
                m_gameSession, std::move(teleportRequest)
            )
        );
        std::cerr << "Created teleport request." << std::endl;
        response->setStatus(0); // O.K.
    }
    return response;
}

std::unique_ptr<const ::Dummy::Server::Response::Response>
ManageCharactersState::visitCommand(
    const Dummy::Server::Command::CreateCharacter& createCharacter
) {
    Dummy::Server::AbstractGameServer& svr(
        m_gameSession.abstractGameServer()
    );
    std::unique_ptr<Dummy::Server::Response::CreateCharacter> response =
        std::make_unique<Dummy::Server::Response::CreateCharacter>();

    try {
        std::shared_ptr<Dummy::Core::Character> chr =
            std::make_shared<Dummy::Core::Character>(
                std::move(
                    svr.createCharacter(
                        m_gameSession.account(),
                        createCharacter.name(), 
                        createCharacter.skin()
                    )
                )
            );

        // Here, if the character has been created, no exception should
        // be thrown.
        m_charactersMap[chr->name()] = chr;
        response->setStatus(0);
        response->setCharacter(chr);
    } catch(const Dummy::Server::CreateCharacterError& e) {
        std::cerr << "Could not create character: "
            << e.what() << std::endl;
        response->setStatus(e.code());
    }
    return response;
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy