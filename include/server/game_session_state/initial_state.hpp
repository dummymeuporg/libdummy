#pragma once

#include "server/game_session_state/state.hpp"

namespace Dummy {
namespace Server {

namespace Command {
    class Command;
}

namespace GameSessionState {

class InitialState : public State {
public:
    InitialState(GameSession&);
    virtual void resume() override;
    virtual void onCommand(const ::Dummy::Server::Command::Command&) override;
};

} // namespace GameSessionState
} // namespace Server
} // namespace State
