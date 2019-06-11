#include "server/command/command.hpp"
#include "server/command/ping.hpp"
#include "server/command/set_position.hpp"
#include "server/response/ping.hpp"
#include "server/response/set_position.hpp"
#include "server/player.hpp"
#include "server/game_session.hpp"
#include "server/game_session_state/playing_state.hpp"
#include "server/map.hpp"

#include "protocol/map_update/update.hpp"
#include "protocol/map_update/character_position.hpp"
#include "protocol/map_update/character_off.hpp"
#include "protocol/map_update/character_on.hpp"


namespace Dummy {
namespace Server {
namespace GameSessionState {

using MapUpdatesVector = std::vector<
    std::unique_ptr<Dummy::Protocol::MapUpdate::Update>
>;

PlayingState::PlayingState(GameSession& gameSession) : State(gameSession)
{
}

void
PlayingState::resume() {
    // XXX: send the map state?
}


void
PlayingState::_createMapUpdates(
    std::shared_ptr<Player> player,
    std::shared_ptr<Map> map,
    MapUpdatesVector& mapUpdates)
{

    // Get the players around.
    std::cerr << "There are " << map->players().size() << " on the map."
        << std::endl;
    for (const auto& [name, otherPlayer]: map->players()) {
        /* ignore the self player */
        if (player->name() == name) {
            continue;
        }

        std::cerr << "Player " << name << std::endl;

        std::shared_ptr<const Dummy::Core::Character>
            chr(otherPlayer->character());
        if (m_mapState.livings().find(chr->name())
                == std::end(m_mapState.livings()))
        {
            // A new character appeared. create a CharacterOn update 
            mapUpdates.push_back(std::move(
                std::make_unique<Dummy::Protocol::MapUpdate::CharacterOn>(
                    otherPlayer->serverPosition().first,
                    otherPlayer->serverPosition().second,
                    otherPlayer->character()->name(),
                    otherPlayer->character()->skin(),
                    otherPlayer->character()->direction()
                )
            ));
            std::cerr << "Hello " << name << std::endl;
        } else {
            // Update the living status.
            mapUpdates.push_back(std::move(
                std::make_unique<
                    Dummy::Protocol::MapUpdate::CharacterPosition
                >(
                    otherPlayer->serverPosition().first,
                    otherPlayer->serverPosition().second,
                    otherPlayer->character()->name(),
                    otherPlayer->character()->direction()
                )));
            // XXX: update the skin / diretion?
            std::cerr << "Updated " << name << std::endl;
        }
    }

    // Check if any player left the map
    for(const auto& [name, living]: m_mapState.livings()) {
        if (map->players().find(name) == std::end(map->players())) {
            std::unique_ptr<Dummy::Protocol::MapUpdate::CharacterOff> update =
                std::make_unique<Dummy::Protocol::MapUpdate::CharacterOff>(
                    name
                );
            mapUpdates.push_back(std::move(update));
            std::cerr << "Bye bye " << name << std::endl;
        }
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

void PlayingState::onCommand(const ::Dummy::Server::Command::Command& command)
{
    command.accept(*this);
}

void PlayingState::visitCommand(
    const Dummy::Server::Command::SetPosition& setPosition
) {
    std::unique_ptr<Dummy::Server::Response::SetPosition> response =
    std::make_unique<Dummy::Server::Response::SetPosition>();

    // XXX: check that the position is not blocking.
    
    // XXX: update the player position
    auto player = m_gameSession.player().lock();
    if (player) {
        player->setPosition(setPosition.x(), setPosition.x());
        response->setStatus(0);
    } else {
        // XXX: Error
        response->setStatus(1);
    }
    m_gameSession.addResponse(std::move(response));
}

void PlayingState::visitCommand(
    const Dummy::Server::Command::Ping& ping
) {
    std::unique_ptr<Dummy::Server::Response::Ping> response =
        std::make_unique<Dummy::Server::Response::Ping>();
    MapUpdatesVector mapUpdates;

    // Get map updates
    auto player = m_gameSession.player().lock();
    if(player == nullptr) {
       // XXX: throw an exception?
        std::cerr << "Error while acquiering player" << std::endl;
    }

    auto map = player->map().lock();
    if (map == nullptr) {
        // XXX: throw an exception?
        std::cerr << "Error while acquiering map" << std::endl;
    }
   _createMapUpdates(player, map, mapUpdates);

   // Apply map updates to the map state and put them into the response
   for (const auto& update: mapUpdates) {
       update->accept(m_mapState);
   }

    // Move updates to the response
    for (auto& update: mapUpdates) {
        response->addUpdate(std::move(update));
    }

    m_gameSession.addResponse(std::move(response));
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
