#pragma once

#include <memory>

namespace Dummy {
namespace Server {

namespace Command {
    class Command;
} // namespace Command

class GameSession;
namespace GameSessionState {

class State : public std::enable_shared_from_this<State> {
public:
    State(GameSession&);
    virtual void resume() = 0;
    virtual void onCommand(const ::Dummy::Server::Command::Command&) = 0;
protected:
    Dummy::Server::GameSession& m_gameSession;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
