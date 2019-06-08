#pragma once

#include <map>

#include "server/game_session.hpp"
#include "server/game_session_state/state.hpp"
#include "protocol/living.hpp"

namespace Dummy {
namespace Server {

namespace Command {
class Command;
}

namespace Response {
class Response;
}

namespace GameSessionState {

class PlayingState : public State {
public:
    PlayingState(GameSession&);
    virtual void onCommand(const ::Dummy::Server::Command::Command&) override;
    virtual void resume() override;
private:
    void _updateLivings(std::shared_ptr<Player> player,
                        std::shared_ptr<Map> map);

    std::map<std::string, std::unique_ptr<Dummy::Protocol::Living>> m_livings;
};

} // namespace GameSessionState
} // namespace Server
} // namespace Dummy
