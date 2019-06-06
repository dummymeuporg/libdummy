#pragma once

#include <memory>

#include "server/command/command_visitor.hpp"

namespace Dummy {
namespace Server {

namespace Command {
    class Command;
} // namespace Command

namespace Response {
    class Response;
}

class GameSession;
namespace GameSessionState {

class State : public std::enable_shared_from_this<State>,
              public ::Dummy::Server::Command::CommandVisitor {
public:
    State(::Dummy::Server::GameSession&);
    virtual void resume() = 0;

    virtual std::unique_ptr<::Dummy::Server::Response::Response>
    onCommand(const ::Dummy::Server::Command::Command&) = 0;
protected:
    ::Dummy::Server::GameSession& m_gameSession;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
