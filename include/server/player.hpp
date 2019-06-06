#pragma once

#include <memory>

#include "core/character.hpp"
#include "server/game_session.hpp"

namespace Dummy {
namespace Server {

class Map;

class Player : public std::enable_shared_from_this<Player> {
public:
    Player(std::shared_ptr<GameSession>,
           std::shared_ptr<::Dummy::Core::Character>);

    std::shared_ptr<GameSession> gameSession() {
        return m_gameSession;
    }

    std::shared_ptr<::Dummy::Core::Character> character() const {
        return m_character;
    }

    const std::string& name() const {
        return m_character->name();
    }

    const std::pair<std::uint16_t, std::uint16_t> serverPosition() const {
        return m_character->position();
    }

    std::shared_ptr<Map> map() const {
        return m_map;
    }

    void setMap(std::shared_ptr<Map>);
    void setPosition(const std::pair<std::uint16_t, std::uint16_t>&);
    void setPosition(std::uint16_t, std::uint16_t);
    void leaveCurrentMap();

private:
    std::shared_ptr<GameSession> m_gameSession;
    std::shared_ptr<Dummy::Core::Character> m_character;
    std::shared_ptr<Map> m_map;

};

} // namespace Server
} // namespace Dummy
