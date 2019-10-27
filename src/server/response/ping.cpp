#include <boost/range/irange.hpp>
#include <memory>

#include <dummy/core/character.hpp>
#include <dummy/protocol/bridge.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/map_update/update.hpp>
#include <dummy/protocol/map_update/character_floor.hpp>
#include <dummy/protocol/map_update/living_on.hpp>
#include <dummy/protocol/map_update/living_off.hpp>
#include <dummy/protocol/map_update/named_living_on.hpp>
#include <dummy/protocol/map_update/character_position.hpp>
#include <dummy/protocol/map_update/packet_serializer.hpp>
#include <dummy/server/response/response_visitor.hpp>
#include <dummy/server/response/ping.hpp>

namespace Dummy {
namespace Server {
namespace Response {

void Ping::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void
Ping::addUpdate(
    std::shared_ptr<const Dummy::Protocol::MapUpdate::Update> update
) {
    m_mapUpdates.push_back(std::move(update));
}

void Ping::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const {
    std::uint16_t count = static_cast<std::uint16_t>(m_mapUpdates.size());
    Dummy::Protocol::MapUpdate::PacketSerializer serializer(packet);
    packet << count;
    for (const auto& mapUpdate: m_mapUpdates) {
        serializer.visit(*mapUpdate);
    }
}

void Ping::readFrom(Dummy::Protocol::IncomingPacket& packet) {
    std::uint16_t countUpdates;
    packet >> countUpdates;
    for (const auto i: boost::irange(countUpdates)) {
        std::uint16_t code;
        packet >> code;
        switch(code) {
        case Dummy::Protocol::Bridge::LIVING_OFF:
            /* Read character off */
            addUpdate(readCharacterOff(packet));
            break;
        case Dummy::Protocol::Bridge::LIVING_ON:
            /* Read character on */
            addUpdate(readCharacterOn(packet));
            break;
        case Dummy::Protocol::Bridge::CHARACTER_POSITION:
            /* Read character position */
            addUpdate(readCharacterPosition(packet));
            break;
        case Dummy::Protocol::Bridge::CHARACTER_FLOOR:
            addUpdate(readCharacterFloor(packet));
            break;
        }
    }
}

std::shared_ptr<const Dummy::Protocol::MapUpdate::LivingOff>
Ping::readCharacterOff(Dummy::Protocol::IncomingPacket& packet) {
    std::uint32_t id;
    packet >> id;
    return std::make_shared<Dummy::Protocol::MapUpdate::LivingOff>(
        id
    );
}

std::shared_ptr<const Dummy::Protocol::MapUpdate::LivingOn>
Ping::readCharacterOn(Dummy::Protocol::IncomingPacket& packet) {
    std::uint32_t id;
    std::uint16_t x, y;
    std::uint8_t floor;
    std::string skin;
    Dummy::Core::Character::Direction direction;
    packet >> id >> x >> y >> floor >> skin
        >> reinterpret_cast<std::uint8_t&>(direction);
    return std::make_shared<const Dummy::Protocol::MapUpdate::LivingOn>(
        id, x, y, floor, skin, direction
    );
}

std::shared_ptr<const Dummy::Protocol::MapUpdate::CharacterPosition>
Ping::readCharacterPosition(Dummy::Protocol::IncomingPacket& packet) {
    std::uint32_t id;
    std::uint16_t x, y;
    Dummy::Core::Character::Direction direction;
    packet >> id >> x >> y
           >> reinterpret_cast<std::uint8_t&>(direction);
    return std::make_shared<Dummy::Protocol::MapUpdate::CharacterPosition>(
        id, x, y, direction
    );
}

std::shared_ptr<const Dummy::Protocol::MapUpdate::CharacterFloor>
Ping::readCharacterFloor(Dummy::Protocol::IncomingPacket& packet) {
    std::string name;
    std::uint8_t floor;
    packet >> name >> floor;
    return std::make_shared<Dummy::Protocol::MapUpdate::CharacterFloor>(
        name, floor
    );
}

std::shared_ptr<Response> Ping::clone() const {
    return std::make_shared<Ping>(*this);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
