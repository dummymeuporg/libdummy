#pragma once

#include <map>

#include "dummy/protocol/living.hpp"
#include "dummy/server/command/teleport_map.hpp"
#include "dummy/server/game_session.hpp"
#include "dummy/server/game_session_state/state.hpp"
#include "dummy/server/map_state.hpp"

namespace Dummy {
namespace Server {

namespace Command {
class Command;
class Ping;
class SetPosition;
} // namespace Command

namespace Response {
class Response;
}

class Map;

namespace GameSessionState {

using MapUpdatesVector =
    std::vector<std::unique_ptr<Dummy::Protocol::MapUpdate::Update>>;

class PlayingState : public State
{
public:
    PlayingState(GameSession&);
    virtual void onCommand(const Command::Command&) override;
    virtual void resume() override;

    void visitCommand(const Command::Ping&) override;
    void visitCommand(const Command::SetPosition&) override;
    void visitCommand(const Command::Message&) override;
    void visitCommand(const Command::ChangeCharacter&) override;
    void visitCommand(const Command::TeleportMap&) override;

private:
    void createMapUpdates(std::shared_ptr<Player>, std::shared_ptr<Map>,
                          MapUpdatesVector&);

    void sendMessageToMap(std::shared_ptr<Map>, std::uint32_t,
                          const std::string&);

    void leavePreviousMap(std::shared_ptr<Player>);

    MapState m_mapState;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
