#pragma once

#include <boost/asio.hpp>

#include <dummy/server/command/handler.hpp>

#include <memory>
#include <queue>

namespace Dummy {
namespace Core {
class Character;
} // namespace Core
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

class GameSessionCommunicator;

using CommandPtr = std::shared_ptr<const Dummy::Server::Command::Command>;
using ResponsePtr = std::shared_ptr<const Dummy::Server::Response::Response>;

using CharactersMap =
    std::map<std::string, std::shared_ptr<Dummy::Core::Character>>;


class GameSession : public std::enable_shared_from_this<GameSession>,
                    public Command::Handler {
public:
    GameSession(
        AbstractGameServer&,
        std::shared_ptr<GameSessionCommunicator>,
        boost::asio::io_context&
    );
    virtual ~GameSession();
    void start();
    void close();
    void changeState(std::shared_ptr<GameSessionState::State>);

    void handleCommand(CommandPtr) override;
    void responseHandlerClosed() override;

    std::unique_ptr<const Dummy::Server::Response::Response>
    getResponse();

    void addResponse(ResponsePtr);

    AbstractGameServer& abstractGameServer() {
        return m_abstractGameServer;
    }

    const Dummy::Server::Account& account() const {
        return *m_account;
    }

    std::weak_ptr<Dummy::Server::Player> player() {
        return m_player;
    }

    boost::asio::io_context& ioContext() {
        return m_ioContext;
    }

    void setAccount(std::shared_ptr<Account> account);
    void setPlayer(std::shared_ptr<Player> player);
    void receiveMessage(const std::uint32_t, const std::string&);
    CharactersMap getCharactersList() const;


private:
    AbstractGameServer& m_abstractGameServer;
    std::shared_ptr<GameSessionCommunicator> m_gameSessionCommunicator;
    boost::asio::io_context& m_ioContext;
    std::shared_ptr<GameSessionState::State> m_state;
    std::shared_ptr<Account> m_account;
    std::shared_ptr<Player> m_player;
    std::queue<std::unique_ptr<const Dummy::Server::Response::Response>>
        m_responses;
    bool m_open;

};

} // namespace Server
} // namespace Dummy
