#include <dummy/protocol/map_update/update.hpp>
#include <dummy/protocol/map_update/character_position.hpp>
#include <dummy/protocol/map_update/character_off.hpp>
#include <dummy/protocol/map_update/character_on.hpp>

#include <dummy/server/command/command.hpp>
#include <dummy/server/command/ping.hpp>
#include <dummy/server/command/message.hpp>
#include <dummy/server/command/set_position.hpp>

#include <dummy/server/response/change_character.hpp>
#include <dummy/server/response/ping.hpp>
#include <dummy/server/response/set_position.hpp>
#include <dummy/server/response/teleport_map.hpp>

#include <dummy/server/player.hpp>
#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/game_session.hpp>
#include <dummy/server/instance.hpp>
#include <dummy/server/map.hpp>

#include <dummy/server/game_session_state/loading_state.hpp>
#include <dummy/server/game_session_state/playing_state.hpp>
#include <dummy/server/game_session_state/manage_characters_state.hpp>

namespace Dummy {
namespace Server {
namespace GameSessionState {

using MapUpdatesVector = std::vector<
    std::unique_ptr<Dummy::Protocol::MapUpdate::Update>
>;

PlayingState::PlayingState(GameSession& gameSession) : State(gameSession) {
}

void
PlayingState::resume() {
    // XXX: send the map state?
}


void
PlayingState::createMapUpdates(
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
            mapUpdates.push_back(
                std::make_unique<Dummy::Protocol::MapUpdate::CharacterOn>(
                    otherPlayer->serverPosition().first,
                    otherPlayer->serverPosition().second,
                    otherPlayer->character()->floor(),
                    otherPlayer->character()->name(),
                    otherPlayer->character()->skin(),
                    otherPlayer->character()->direction()
                )
            );
            std::cerr << "Hello " << name << std::endl;
        } else {
            // Update the living status if necessary
            const auto& living(m_mapState.living(chr->name()));
            if (living.x() != otherPlayer->serverPosition().first ||
                living.y() != otherPlayer->serverPosition().second)
            {
                mapUpdates.push_back(
                    std::make_unique<
                        Dummy::Protocol::MapUpdate::CharacterPosition
                    >(
                        otherPlayer->serverPosition().first,
                        otherPlayer->serverPosition().second,
                        otherPlayer->character()->name(),
                        otherPlayer->character()->direction()
                    ));
                // XXX: update the skin / direction?
                std::cerr << "Updated " << name << std::endl;
            }
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
        player->setPosition(setPosition.x(), setPosition.y());
        response->setStatus(0);
    } else {
        // XXX: Error
        response->setStatus(1);
    }
    m_gameSession.addResponse(std::move(response));
}

void PlayingState::visitCommand(
    const Dummy::Server::Command::Message& message
) {
    // XXX: notify other players on the map.
    auto player = m_gameSession.player().lock();
    if(player == nullptr) {
       // XXX: throw an exception?
        std::cerr << "Error while acquiering player" << std::endl;
        return;
    }

    auto map = player->map().lock();
    if (map == nullptr) {
        // XXX: throw an exception?
        std::cerr << "Error while acquiering map" << std::endl;
        return;
    }

    sendMessageToMap(map, player->name(), message.content());
}

void PlayingState::visitCommand(
    const Dummy::Server::Command::Ping&
) {
    auto response(std::make_shared<Dummy::Server::Response::Ping>());
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
   createMapUpdates(player, map, mapUpdates);

   // Apply map updates to the map state and put them into the response
   for (const auto& update: mapUpdates) {
       update->accept(m_mapState);
   }

    // Move updates to the response
    for (auto& update: mapUpdates) {
        response->addUpdate(std::move(update));
    }

    m_gameSession.addResponse(response);
}

void PlayingState::visitCommand(
    const Dummy::Server::Command::ChangeCharacter&
) {
    auto self(shared_from_this());
    // XXX: Disconnect player from map, send a response
    // (then switch back to manage characters state)
    auto player = m_gameSession.player().lock();
    if (nullptr == player) {
        // XXX: throw an exception?
        std::cerr << "Error while acquiering player." << std::endl;
    }
    // XXX: Ugly.
    player->leaveCurrentMap();
    m_gameSession.abstractGameServer().saveCharacter(
        m_gameSession.account(),
        *player->character()
    );

    // Get the actual player position, for client synchronization.
    auto playerMap(player->character()->mapLocation());
    auto playerPosition(player->character()->position());

    // Get characters list.
    CharactersMap&& map = m_gameSession.getCharactersList();

    // Reset player.
    m_gameSession.setPlayer(nullptr);

    // Change state.
    auto state(std::make_shared<ManageCharactersState>(
        m_gameSession, std::move(map)
    ));
    m_gameSession.changeState(state);

    // Emplace a ChangeCharacter response (so the client knows that
    // he has to go back to the select character screen).
    auto response(
        std::make_shared<Dummy::Server::Response::ChangeCharacter>()
    );
    response->setStatus(0);
    response->setMapLocation(playerMap);
    response->setPosition(playerPosition);
    m_gameSession.addResponse(std::move(response));
}

void PlayingState::sendMessageToMap(
    std::shared_ptr<Map> map,
    const std::string& author,
    const std::string& message
) {
    boost::asio::post(m_gameSession.ioContext(),
                      [author,
                      map=map->shared_from_this(),
                      message]()
    {
        map->dispatchMessage(author, message);
    });
}

void PlayingState::visitCommand(
    const Dummy::Server::Command::TeleportMap& teleportMap
) {
    std::cerr << "Server: teleport to " << teleportMap.mapName()
        << std::endl;
    auto response =
        std::make_shared<Dummy::Server::Response::TeleportMap>();

    auto& gameServer(m_gameSession.abstractGameServer());
    const auto& mapName(teleportMap.mapName());
    const auto& mapNames(gameServer.project().maps());
    auto& mainInstance(gameServer.mainInstance());

    if (mapNames.find(mapName) == std::end(mapNames)) {
        // XXX: Throw an exception?
        std::cerr << "Cannot find map name." << std::endl;
        m_gameSession.close();
    }

    const auto& destinationMap(mapNames.at(mapName));
    if (teleportMap.x() > destinationMap->width()*2 ||
        teleportMap.y() > destinationMap->height()*2)
    {
        // XXX: Throw an exception?
        std::cerr << "Coordinates are not valid." << std::endl;
        m_gameSession.close();
    }

    if (teleportMap.floor() >= destinationMap->floorsCount()) {
        // XXX: Throw an exception?
        std::cerr << "Floor is not valid." << std::endl;
        m_gameSession.close();
    }

    // TODO: Check that there actually is a teleport command written in the
    // lua file.

    // ...
    auto serverMap = mainInstance.map(mapName).lock();

    if (serverMap == nullptr) {
        // XXX: Throw an exception?
        std::cerr << "Could not access to destination map server."
                  << std::endl;
        m_gameSession.close();
    }

    auto player = m_gameSession.player().lock();

    if (nullptr == player) {
        // XXX: Throw an exception?
        std::cerr << "Could not access the players.";
    }

    auto oldServerMap = player->map().lock();
    if (nullptr == oldServerMap) {
        // XXX: Throw an exception?
        std::cerr << "Cannot access the current player's map." << std::endl;
    }

    oldServerMap->removePlayer(player);
    serverMap->addPlayer(player);

    Dummy::Protocol::TeleportRequest request(
        mapName,
        teleportMap.destination(),
        teleportMap.floor(),
        "main"
    );
    m_gameSession.addResponse(response);
    response->setStatus(0);
    m_gameSession.changeState(
        std::make_shared<LoadingState>(m_gameSession, std::move(request))
    );
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
