#include "server/player.hpp"
#include "server/map.hpp"

namespace Dummy {
namespace Server {

Player::Player(std::shared_ptr<GameSession> gameSession,
               std::shared_ptr<Dummy::Core::Character> character)
    : m_gameSession(gameSession), m_character(character),
      m_map(nullptr)
{

}

void Player::leaveCurrentMap() {
    auto self(shared_from_this());
    if (nullptr != m_map) {
        m_map->removePlayer(shared_from_this());
        m_map = nullptr;
    }
}

void Player::setMap(std::shared_ptr<Map> map) {
    leaveCurrentMap();
    m_map = map;
}

void
Player::setPosition(const std::pair<std::uint16_t, std::uint16_t>& pos) {
    m_character->setPosition(pos); 
}

void Player::setPosition(std::uint16_t x, std::uint16_t y) {
    setPosition(std::pair<std::uint16_t, std::uint16_t>(x, y));
}

} // namespace Server
} // namespace Dummy
