#pragma once

#include "server/game_session_state/state.hpp"

namespace Dummy {
namespace Server {

namespace Command {
    class GetPrimaryInfoCommand;
    class Command;
}

namespace Response {
    class Response;
}

namespace GameSessionState {

class SendCharactersState : public State {
public:
    using CharactersList =
        std::vector<std::shared_ptr<Dummy::Core::Character>>;
    SendCharactersState(GameSession&);

    virtual void resume() override;

    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>
    onCommand(const ::Dummy::Server::Command::Command&) override;

    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>
    visitCommand(
        const Dummy::Server::Command::GetPrimaryInfoCommand& command
    ) override;

    /*
    virtual std::unique_ptr<::Dummy::Server::Response::Response>    
    visitCommand(const ::Dummy::Server::Command::ConnectCommand&);
    */
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
