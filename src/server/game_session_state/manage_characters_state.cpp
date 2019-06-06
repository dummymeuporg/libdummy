#include <iostream>
#include <fstream>

#include <boost/range/iterator_range.hpp>

#include "core/character.hpp"

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

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
