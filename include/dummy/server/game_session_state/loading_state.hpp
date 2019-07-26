#pragma once

#include <dummy/protocol/teleport_request.hpp>
#include <dummy/server/game_session_state/state.hpp>

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
    void onCommand(const ::Dummy::Server::Command::Command&) override;

    void visitCommand(const Dummy::Server::Command::TeleportMap&) override;
    virtual void resume() override;
private:
    Dummy::Protocol::TeleportRequest m_teleportRequest;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
