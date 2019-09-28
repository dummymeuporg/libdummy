#include <dummy/server/player.hpp>
#include <dummy/server/map.hpp>

namespace Dummy {
namespace Server {

Player::Player(GameSession& gameSession,
               std::shared_ptr<Dummy::Core::Character> character)
    : m_gameSession(gameSession),
      m_character(character)
{

}

void Player::leaveCurrentMap() {
    auto self(shared_from_this());
    if (auto m = m_map.lock()) {
        m->removePlayer(shared_from_this());
        m_map.reset();
    }
}

void Player::setMap(std::weak_ptr<Map> map) {
    //leaveCurrentMap();
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
