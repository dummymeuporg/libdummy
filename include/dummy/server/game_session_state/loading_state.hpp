#pragma once

#include "dummy/protocol/teleport_request.hpp"
#include "dummy/server/game_session_state/state.hpp"

namespace Dummy {
namespace Server {

namespace Command {
    class Command;
    class TeleportMap;
}

namespace Response {
    class Response;
}

class Instance;
class Player;

namespace GameSessionState {

class LoadingState : public State {
public:
    LoadingState(GameSession&,
                 Dummy::Protocol::TeleportRequest&&);
    void onCommand(const ::Dummy::Server::Command::Command&) override;

    void visitCommand(const Dummy::Server::Command::TeleportMap&) override;
    virtual void resume() override;

private:
    /* Methods */
    std::weak_ptr<Instance> getServerInstance(
        const std::string&,
        std::shared_ptr<Player>
    );

    void switchInstance(
        std::shared_ptr<Player>,
        std::shared_ptr<Instance>,
        const std::string&
    );

    void addToInstance(
        std::shared_ptr<Player> player,
        const std::string& newInstanceName
    );

    void leavePreviousMap(std::shared_ptr<Player>);

private:
    Dummy::Protocol::TeleportRequest m_teleportRequest;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
