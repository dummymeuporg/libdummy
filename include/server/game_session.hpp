#pragma once

#include <memory>

namespace Dummy {
namespace Server {

class AbstractGameServer;
class Account;
class Player;

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
    virtual ~GameSession();
    void start();
    void close();
    void changeState(std::shared_ptr<GameSessionState::State>);

    std::unique_ptr<const Dummy::Server::Response::Response>
    handleCommand(const ::Dummy::Server::Command::Command&);

    AbstractGameServer& abstractGameServer() {
        return m_abstractGameServer;
    }

    const Dummy::Server::Account& account() const {
        return *m_account;
    }

    std::weak_ptr<Dummy::Server::Player> player() {
        return m_player;
    }

    void setAccount(std::shared_ptr<Account> account);
    void setPlayer(std::shared_ptr<Player> player);
private:
    AbstractGameServer& m_abstractGameServer;
    std::shared_ptr<GameSessionState::State> m_state;
    std::shared_ptr<Account> m_account;
    std::shared_ptr<Player> m_player;

};

} // namespace Server
} // namespace Dummy
