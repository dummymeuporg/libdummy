#pragma once

#include "protocol/teleport_request.hpp"
#include "server/game_session_state/state.hpp"

namespace Dummy {
namespace Server {

namespace Command {
    class Command;
    class TeleportMap;
}

namespace Response {
    class Response;
}

namespace GameSessionState {

class LoadingState : public State {
public:
    LoadingState(GameSession&,
                 Dummy::Protocol::TeleportRequest&&);
    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>
    onCommand(const ::Dummy::Server::Command::Command&) override;

    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>
    visitCommand(const Dummy::Server::Command::TeleportMap&) override;
    virtual void resume() override;
private:
    Dummy::Protocol::TeleportRequest m_teleportRequest;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
