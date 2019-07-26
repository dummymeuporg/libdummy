#pragma once

#include <dummy/server/game_session_state/state.hpp>

namespace Dummy {
namespace Server {

namespace Command {
    class ConnectCommand;
    class Command;
}

namespace Response {
    class Response;
}

namespace GameSessionState {

class InitialState : public State {
public:
    InitialState(GameSession&);
    virtual void resume() override;

    virtual void
    onCommand(const ::Dummy::Server::Command::Command&) override;

    virtual void
    visitCommand(const ::Dummy::Server::Command::ConnectCommand&) override;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
