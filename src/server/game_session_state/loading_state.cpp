#include "dummy/server/game_session_state/loading_state.hpp"

#include "dummy/server/abstract_game_server.hpp"
#include "dummy/server/command/command.hpp"
#include "dummy/server/command/teleport_map.hpp"
#include "dummy/server/game_session.hpp"
#include "dummy/server/game_session_state/playing_state.hpp"
#include "dummy/server/map.hpp"
#include "dummy/server/player.hpp"
#include "dummy/server/response/teleport_map.hpp"

namespace Dummy {
namespace Server {
namespace GameSessionState {

LoadingState::LoadingState(GameSession& gameSession,
                           Dummy::Protocol::TeleportRequest&& teleportRequest)
    : State(gameSession)
    , m_teleportRequest(std::move(teleportRequest))
{}

void LoadingState::resume()
{
    std::cerr << "[LoadingState]" << std::endl;
}


void LoadingState::onCommand(const ::Dummy::Server::Command::Command& command)
{
    command.accept(*this);
}

void LoadingState::visitCommand(
    const Dummy::Server::Command::TeleportMap& teleportMap)
{
    auto self(shared_from_this());
    Dummy::Server::AbstractGameServer& srv(m_gameSession.abstractGameServer());
    std::shared_ptr<Player> player = m_gameSession.player().lock();
    auto response = std::make_shared<Dummy::Server::Response::TeleportMap>();

    if (nullptr == player) {
        response->setStatus(-1);
        m_gameSession.addResponse(response);
        return;
    }


    if (m_teleportRequest.destinationMap() == teleportMap.mapName()
        && m_teleportRequest.floor() == teleportMap.floor()
        && m_teleportRequest.position() == teleportMap.destination()) {
        std::cerr << "Teleport request valid." << std::endl;
        std::weak_ptr<Map> newServerMap;

        // Remove the player from its former map, if needed.


        auto playerInstance(player->instance().lock());

        if (nullptr != playerInstance) {
            if (playerInstance->name()
                != m_teleportRequest.destinationInstance()) {
                // XXX: Switch instance. Make sure that the instance being left
                // contains no more player, and release it (unspawn it).
                switchInstance(player, playerInstance,
                               m_teleportRequest.destinationInstance());
            }
        } else {
            // The player had no previous instance. Welcome it to the brand
            // new instance.
            addToInstance(player, m_teleportRequest.destinationInstance());
        }

        auto dstInstance =
            getServerInstance(m_teleportRequest.destinationInstance(), player)
                .lock();

        if (nullptr == dstInstance) {
            response->setStatus(-3);
            m_gameSession.addResponse(response);
            return;
        }

        newServerMap = dstInstance->map(teleportMap.mapName());

        if (auto mapPt = newServerMap.lock()) {
            player->setMap(mapPt);
            player->character()->setMapLocation(
                m_teleportRequest.destinationMap());
            player->character()->setPosition(m_teleportRequest.position());
            // mapPt->addPlayer(player);
            mapPt->addObserver(player);
            response->setStatus(0);

            std::cerr << "CHANGE STATE" << std::endl;
            m_gameSession.changeState(
                std::make_shared<PlayingState>(m_gameSession));
        } else {
            response->setStatus(-4);
        }
    } else {
        std::cerr << "Error with teleport request." << std::endl;
        std::cerr << m_teleportRequest.destinationMap() << " "
                  << teleportMap.mapName() << std::endl;
        std::cerr << static_cast<int>(m_teleportRequest.floor()) << " "
                  << static_cast<int>(teleportMap.floor()) << std::endl;
        std::cerr << m_teleportRequest.position().first << " "
                  << teleportMap.destination().first << std::endl;
        std::cerr << m_teleportRequest.position().second << " "
                  << teleportMap.destination().second << std::endl;
        response->setStatus(-2);
    }
    m_gameSession.addResponse(response);
}

std::weak_ptr<Instance>
LoadingState::getServerInstance(const std::string& name,
                                std::shared_ptr<Player> player)
{
    // Check masks.
    if (name == "%PLAYER_NAME%") {
        return m_gameSession.abstractGameServer().instance(player->name());
    } else {
        return m_gameSession.abstractGameServer().instance(name);
    }
}

void LoadingState::switchInstance(std::shared_ptr<Player> player,
                                  std::shared_ptr<Instance> formerInstance,
                                  const std::string& newInstanceName)
{
    auto newInstance(getServerInstance(newInstanceName, player));
    auto pt = newInstance.lock();
    if (nullptr != pt) {
        formerInstance->removePlayer(player->name());
        pt->addPlayer(player->name(), player);
        player->setInstance(pt);

        // Unspawn the former instance, if empty (no players)
        if (0 == formerInstance->countPlayers()) {

            // XXX: defer this through io context?
            m_gameSession.abstractGameServer().releaseInstance(
                formerInstance->name());
        }
    }
}

void LoadingState::addToInstance(std::shared_ptr<Player> player,
                                 const std::string& newInstanceName)
{
    auto newInstance(getServerInstance(newInstanceName, player));
    auto pt = newInstance.lock();
    if (nullptr != pt) {
        pt->addPlayer(player->name(), player);
        player->setInstance(pt);
    }
}

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
