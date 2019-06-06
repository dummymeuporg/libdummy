#pragma once

#include "server/game_session_state/state.hpp"

namespace Dummy {
namespace Server {

namespace Command {
    class ConnectCommand;
    class Command;
}

namespace GameSessionState {

class InitialState : public State {
public:
    InitialState(GameSession&);
    virtual void resume() override;

    virtual std::unique_ptr<::Dummy::Server::Response::Response>
    onCommand(const ::Dummy::Server::Command::Command&) override;

    virtual std::unique_ptr<::Dummy::Server::Response::Response>    
    visitCommand(const ::Dummy::Server::Command::ConnectCommand&);
};

} // namespace GameSessionState
} // namespace Server
} // namespace State
