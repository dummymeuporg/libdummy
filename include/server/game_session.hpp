#pragma once

#include <memory>

namespace Dummy {
namespace Server {

class AbstractGameServer;

namespace Command {
    class Command;
}

namespace GameSessionState {
    class State;
}

class GameSession : public std::enable_shared_from_this<GameSession> {
public:
    GameSession(AbstractGameServer&);
    void start();
    void changeState(std::shared_ptr<GameSessionState::State>);
    void handleCommand(std::unique_ptr<::Dummy::Server::Command::Command>);
private:
    AbstractGameServer& m_abstractGameServer;
    std::shared_ptr<GameSessionState::State> m_state;

};

} // namespace Server
} // namespace Dummy
