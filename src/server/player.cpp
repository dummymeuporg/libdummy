#include <dummy/protocol/map_update/named_living_on.hpp>

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
        m->removeObserver(m_id.value());
        m_map.reset();
    }
}

void Player::setMap(std::weak_ptr<Map> map) {
    m_map = map;
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

void Player::notifyOn(MapUpdatesVector& mapUpdates) {
    mapUpdates.push_back(
        std::make_unique<Dummy::Protocol::MapUpdate::NamedLivingOn>(
            m_id.value(),
            serverPosition().first,
            serverPosition().second,
            character()->floor(),
            character()->name(),
            character()->skin(),
            character()->direction()
        )
    );
}

void Player::notifyPosition(MapUpdatesVector& mapUpdates) {
    mapUpdates.push_back(
        std::make_unique<
            Dummy::Protocol::MapUpdate::CharacterPosition
        >(
            m_id.value(),
            serverPosition().first,
            serverPosition().second,
            character()->direction()
        ));
}

std::pair<std::uint16_t, std::uint16_t> Player::position() {
    return serverPosition();
}

void Player::receiveMessage(std::uint32_t author, const std::string& message) {
    m_gameSession.receiveMessage(author, message);
}

} // namespace Server
} // namespace Dummy
