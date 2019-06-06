#include "server/player.hpp"
#include "server/game_session.hpp"
#include "server/game_session_state/playing_state.hpp"
#include "server/map.hpp"

#include "protocol/map_update.hpp"
#include "protocol/character_position.hpp"
#include "protocol/character_off.hpp"


namespace Dummy {
namespace Server {
namespace GameSessionState {

PlayingState::PlayingState(GameSession& gameSession) : State(gameSession)
{
}

void
PlayingState::resume() {
    // XXX: send the map state?
}

void PlayingState::_updateLivings(std::shared_ptr<Player> player,
                                  std::shared_ptr<Map> map)
{

    std::vector<std::shared_ptr<Dummy::Protocol::MapUpdate>> mapUpdates;

    // Get the players around.
    std::cerr << "There are " << map->players().size() << " on the map."
        << std::endl;
    for (const auto otherPlayer: map->players()) {
        if (player->name() == otherPlayer.first) {
            continue;
        }

        std::cerr << "Player " << otherPlayer.first << std::endl;

        std::shared_ptr<const Dummy::Core::Character>
            chr(otherPlayer.second->character());
        if (m_livings.find(chr->name()) == std::end(m_livings)) {
            // A new character appeared.
            m_livings[otherPlayer.first] = 
                std::make_unique<Dummy::Protocol::Living>(
                    otherPlayer.second->serverPosition().first,
                    otherPlayer.second->serverPosition().second,
                    otherPlayer.second->character()->name(),
                    otherPlayer.second->character()->skin(),
                    otherPlayer.second->character()->direction()
                );
            std::cerr << "Hello " << otherPlayer.first << std::endl;
        } else {
            // Update the living status.
            Dummy::Protocol::Living& living(*m_livings[otherPlayer.first]);
            
            if (living.x() != otherPlayer.second->serverPosition().first ||
                living.y() != otherPlayer.second->serverPosition().second)
            {
                living.setPosition(
                    otherPlayer.second->serverPosition().first,
                    otherPlayer.second->serverPosition().second
                );
                std::cerr << "UPDATE POS TO: " << living.x() << ", "
                    << living.y() << std::endl;
            }

            if (living.chipset() !=
                otherPlayer.second->character()->skin())
            {
                living.setChipset(
                    otherPlayer.second->character()->skin()
                );
            }

            if (living.direction() !=
                otherPlayer.second->character()->direction())
            {
                living.setDirection(
                    otherPlayer.second->character()->direction()
                );
            }
            std::cerr << "Updated " << otherPlayer.first << std::endl;
        }

        // Create the event.
        Dummy::Protocol::Living& living(*m_livings[otherPlayer.first]);
        std::shared_ptr<Dummy::Protocol::CharacterPosition> event =
            std::make_shared<Dummy::Protocol::CharacterPosition>(
                living.x(),
                living.y(),
                living.name(),
                living.chipset(),
                living.direction()
            );
        mapUpdates.push_back(event);

    }

    std::vector<std::string> departures;
    // Check if any player left the map
    for(const auto& [name, living]: m_livings) {
        //const Dummy::Protocol::Living& living(*it.second);
        if (map->players().find(name) == std::end(map->players())) {
            std::shared_ptr<Dummy::Protocol::CharacterOff> event =
                std::make_shared<Dummy::Protocol::CharacterOff>(name);
            mapUpdates.push_back(event);
            departures.push_back(name);
        }
    }

    for (const auto& name: departures) {
        std::cerr << "Bye bye " << name << std::endl;
        m_livings.erase(name);
    }

    // Write map updates to outgoing packet.
    /*
    std::uint16_t count = mapUpdates.size();
    pkt << count;
    for (const auto& update: mapUpdates) {
        pkt << update->code() << *update;
    }
    */
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
