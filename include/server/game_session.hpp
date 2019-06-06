#pragma once

#include <memory>

namespace Dummy {
namespace Server {

class AbstractGameServer;

namespace Command {
    class Command;
}

namespace Response {
    class Response;
}

namespace GameSessionState {
    class State;
}

class GameSession : public std::enable_shared_from_this<GameSession> {
public:
    GameSession(AbstractGameServer&);
    void start();
    void changeState(std::shared_ptr<GameSessionState::State>);

    std::unique_ptr<Dummy::Server::Response::Response>
    handleCommand(const ::Dummy::Server::Command::Command&);

    AbstractGameServer& abstractGameServer() {
        return m_abstractGameServer;
    }
private:
    AbstractGameServer& m_abstractGameServer;
    std::shared_ptr<GameSessionState::State> m_state;

};

} // namespace Server
} // namespace Dummy
