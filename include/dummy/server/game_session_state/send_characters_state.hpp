#pragma once

#include <vector>

#include "dummy/server/game_session_state/state.hpp"

namespace Dummy {
namespace Server {

namespace Command {
class GetPrimaryInfoCommand;
class Command;
} // namespace Command

namespace Response {
class Response;
}

namespace GameSessionState {

class SendCharactersState : public State
{
public:
    using CharactersList = std::vector<std::shared_ptr<Dummy::Core::Character>>;
    SendCharactersState(GameSession&);

    virtual void resume() override;

    virtual void onCommand(const ::Dummy::Server::Command::Command&) override;

    virtual void visitCommand(
        const Dummy::Server::Command::GetPrimaryInfoCommand& command) override;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
