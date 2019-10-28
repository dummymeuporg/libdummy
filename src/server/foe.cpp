#include <dummy/core/character.hpp>
#include <dummy/core/foe.hpp>

#include <dummy/protocol/map_update/living_on.hpp>

#include <dummy/server/foe.hpp>
#include <dummy/server/map_state.hpp>


namespace Dummy {
namespace Server {

Foe::Foe(const Dummy::Core::Foe& foe)
    : m_chipset(foe.chipset()),
      m_position{foe.position().first*2, foe.position().second*2},
      m_floor(foe.floor())
{

}

void Foe::notifyOn(MapUpdatesVector& mapUpdates) {
    mapUpdates.push_back(
        std::make_unique<Dummy::Protocol::MapUpdate::LivingOn>(
            m_id.value(),
            m_position.first,
            m_position.second,
            m_floor,
            m_chipset,
            Dummy::Core::Character::Direction::DOWN
        )
    );
}

void Foe::notifyPosition(MapUpdatesVector& mapUpdates) {
    mapUpdates.push_back(
        std::make_unique<
            Dummy::Protocol::MapUpdate::CharacterPosition
        >(
            m_id.value(),
            m_position.first,
            m_position.second,
            Dummy::Core::Character::Direction::DOWN // XXX: For now.
        ));
}

std::pair<std::uint16_t, std::uint16_t> Foe::position() {
    return m_position;
}

} // namespace Server
} // namespace Dummy
