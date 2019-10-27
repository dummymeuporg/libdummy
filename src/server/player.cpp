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

void
Player::setPosition(const std::pair<std::uint16_t, std::uint16_t>& pos) {
    std::cerr << "Server, set position: " << pos.first <<
                 " " << pos.second << std::endl;
    m_character->setPosition(pos); 
}

void Player::setPosition(std::uint16_t x, std::uint16_t y) {
    setPosition(std::pair<std::uint16_t, std::uint16_t>(x, y));
}

void Player::setInstance(std::weak_ptr<Instance> instance) {
    m_instance = instance;
}

} // namespace Server
} // namespace Dummy
