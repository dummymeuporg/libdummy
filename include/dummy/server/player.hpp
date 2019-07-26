#pragma once

#include <memory>

#include <dummy/core/character.hpp>
#include <dummy/server/game_session.hpp>

namespace Dummy {
namespace Server {

class Map;

class Player : public std::enable_shared_from_this<Player> {
public:
    Player(GameSession&,
           std::shared_ptr<::Dummy::Core::Character>);

    GameSession& gameSession() {
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

    std::weak_ptr<Map> map() const {
        return m_map;
    }

    void setMap(std::weak_ptr<Map>);
    void setPosition(const std::pair<std::uint16_t, std::uint16_t>&);
    void setPosition(std::uint16_t, std::uint16_t);
    void leaveCurrentMap();

private:
    GameSession& m_gameSession;
    std::shared_ptr<Dummy::Core::Character> m_character;
    std::weak_ptr<Map> m_map;

};

} // namespace Server
} // namespace Dummy
