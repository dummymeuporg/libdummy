#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/game_session.hpp>
#include <dummy/server/command/command.hpp>
#include <dummy/server/command/teleport_map.hpp>
#include <dummy/server/game_session_state/loading_state.hpp>
#include <dummy/server/game_session_state/playing_state.hpp>
#include <dummy/server/player.hpp>
#include <dummy/server/map.hpp>
#include <dummy/server/response/teleport_map.hpp>


namespace Dummy {
namespace Server {
namespace GameSessionState {

LoadingState::LoadingState(GameSession& gameSession,
                           Dummy::Protocol::TeleportRequest&& teleportRequest)
    : State(gameSession),
      m_teleportRequest(std::move(teleportRequest))
{

}

void LoadingState::resume() {
    std::cerr << "[LoadingState]" << std::endl;
}


void 
LoadingState::onCommand(const ::Dummy::Server::Command::Command& command) {
    command.accept(*this);
}

void LoadingState::visitCommand(
    const Dummy::Server::Command::TeleportMap& teleportMap
) {
    auto self(shared_from_this());
    Dummy::Server::AbstractGameServer& srv(m_gameSession.abstractGameServer());
    std::shared_ptr<Player> player = m_gameSession.player().lock();
    auto response =
        std::make_shared<Dummy::Server::Response::TeleportMap>();

    if (nullptr == player) {
        response->setStatus(-1);
        m_gameSession.addResponse(response);
        return;
    }


    if (m_teleportRequest.destinationMap() == teleportMap.mapName() &&
        m_teleportRequest.floor() == teleportMap.floor() &&
        m_teleportRequest.position() == teleportMap.destination())
    {
        std::cerr << "Teleport request valid." << std::endl;
        std::weak_ptr<Map> previousServerMap = player->map();
        std::weak_ptr<Map> newServerMap;

        if (teleportMap.instance() == "main") {
            newServerMap = srv.mainInstance().map(teleportMap.mapName());
        } else {
            // XXX: Handle this case later!
        }

        if (auto mapPt = newServerMap.lock()) {
            player->setMap(mapPt);
            mapPt->addPlayer(player);
            response->setStatus(0);

            std::cerr << "CHANGE STATE" << std::endl;
            m_gameSession.changeState(
                std::make_shared<PlayingState>(m_gameSession)
            );
        } else {
            response->setStatus(-1);
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

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
