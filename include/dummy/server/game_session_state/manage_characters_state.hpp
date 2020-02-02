#pragma once

#include "dummy/server/game_session_state/state.hpp"

namespace Dummy {
namespace Server {

namespace Command {
    class Command;
}

namespace Response {
    class Response;
}

namespace GameSessionState {

using CharactersMap =
    std::map<std::string, std::shared_ptr<Dummy::Core::Character>>;
class ManageCharactersState : public State {
public:
    ManageCharactersState(GameSession&, CharactersMap&&);
    virtual void resume() override;
    virtual void
    onCommand(const ::Dummy::Server::Command::Command&) override;

    virtual void
    visitCommand(const Dummy::Server::Command::CreateCharacter&) override;

    virtual void
    visitCommand(const Dummy::Server::Command::SelectCharacter&) override;
private:
    CharactersMap m_charactersMap;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
