#pragma once

#include <memory>

namespace Dummy {
namespace Server {

class AbstractGameServer;
class Account;

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

    std::unique_ptr<const Dummy::Server::Response::Response>
    handleCommand(const ::Dummy::Server::Command::Command&);

    AbstractGameServer& abstractGameServer() {
        return m_abstractGameServer;
    }

    const Dummy::Server::Account& account() const {
        return *m_account;
    }

    void setAccount(std::shared_ptr<Account> account);
private:
    AbstractGameServer& m_abstractGameServer;
    std::shared_ptr<GameSessionState::State> m_state;
    std::shared_ptr<Account> m_account;

};

} // namespace Server
} // namespace Dummy
