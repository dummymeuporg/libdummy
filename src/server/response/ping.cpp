#include <boost/range/irange.hpp>
#include <memory>

#include "core/character.hpp"
#include "protocol/bridge.hpp"
#include "protocol/outgoing_packet.hpp"
#include "protocol/incoming_packet.hpp"
#include "protocol/map_update/update.hpp"
#include "protocol/map_update/character_off.hpp"
#include "protocol/map_update/character_on.hpp"
#include "protocol/map_update/character_position.hpp"
#include "protocol/map_update/packet_serializer.hpp"
#include "server/response/response_visitor.hpp"
#include "server/response/ping.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void Ping::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void
Ping::addUpdate(
    std::unique_ptr<const Dummy::Protocol::MapUpdate::Update> update
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
        case Dummy::Protocol::Bridge::CHARACTER_OFF:
            /* Read character off */
            addUpdate(_readCharacterOff(packet));
            break;
        case Dummy::Protocol::Bridge::CHARACTER_ON:
            /* Read character on */
            addUpdate(_readCharacterOn(packet));
            break;
        case Dummy::Protocol::Bridge::CHARACTER_POSITION:
            /* Read character position */
            addUpdate(_readCharacterPosition(packet));
        }
    }
}

std::unique_ptr<const Dummy::Protocol::MapUpdate::CharacterOff>
Ping::_readCharacterOff(Dummy::Protocol::IncomingPacket& packet) {
    std::string name;
    packet >> name;
    return std::make_unique<Dummy::Protocol::MapUpdate::CharacterOff>(
        name
    );
}

std::unique_ptr<const Dummy::Protocol::MapUpdate::CharacterOn>
Ping::_readCharacterOn(Dummy::Protocol::IncomingPacket& packet) {
    std::uint16_t x, y;
    std::uint8_t floor;
    std::string name, skin;
    Dummy::Core::Character::Direction direction;
    packet >> x >> y >> floor >> name >> skin
        >> reinterpret_cast<std::uint8_t&>(direction);
    return std::make_unique<Dummy::Protocol::MapUpdate::CharacterOn>(
        x, y, floor, name, skin, direction
    );
}

std::unique_ptr<const Dummy::Protocol::MapUpdate::CharacterPosition>
Ping::_readCharacterPosition(Dummy::Protocol::IncomingPacket& packet) {
    std::uint16_t x, y;
    std::uint8_t floor;
    std::string name;
    Dummy::Core::Character::Direction direction;
    packet >> x >> y >> floor
           >> name >> reinterpret_cast<std::uint8_t&>(direction);
    return std::make_unique<Dummy::Protocol::MapUpdate::CharacterPosition>(
        x, y, floor, name, direction
    );
}

} // namespace Response
} // namespace Server
} // namespace Dummy
