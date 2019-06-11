#pragma once

#include <map>

#include "server/game_session.hpp"
#include "server/map_state.hpp"
#include "server/game_session_state/state.hpp"
#include "protocol/living.hpp"

namespace Dummy {
namespace Server {

namespace Command {
class Command;
class Ping;
class SetPosition;
}

namespace Response {
class Response;
}

namespace GameSessionState {

using MapUpdatesVector = std::vector<
    std::unique_ptr<Dummy::Protocol::MapUpdate::Update>
>;

class PlayingState : public State {
public:
    PlayingState(GameSession&);
    virtual void onCommand(const Command::Command&) override;
    virtual void resume() override;

    virtual void visitCommand(const Command::Ping&) override;
    virtual void visitCommand(const Command::SetPosition&) override;
private:
    void _createMapUpdates(
        std::shared_ptr<Player>,
        std::shared_ptr<Map>,
        MapUpdatesVector&);

     MapState m_mapState;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
