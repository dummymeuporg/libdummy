#include <dummy/protocol/living.hpp>
#include <dummy/protocol/map_update/update.hpp>
#include <dummy/protocol/map_update/character_on.hpp>
#include <dummy/protocol/map_update/character_off.hpp>
#include <dummy/protocol/map_update/character_position.hpp>
#include <dummy/server/map_state.hpp>

namespace Dummy {
namespace Server {

MapState::MapState() {}

void MapState::update(const Dummy::Protocol::MapUpdate::Update& update) {
    update.accept(*this);
}

void MapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterPosition& update
) {
    if (m_livings.find(update.name()) == std::end(m_livings)) {
        throw LivingNotFound();
    }

    auto& living = m_livings[update.name()];
    living->setPosition(update.x(), update.y());
}

void MapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterOff& update
) {
    if (m_livings.find(update.name()) == std::end(m_livings)) {
        throw LivingNotFound();
    }
    m_livings.erase(update.name());
}

void MapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterOn& update) {
    std::unique_ptr<Dummy::Protocol::Living> living =
        std::make_unique<Dummy::Protocol::Living>(
            update.x(),
            update.y(),
            update.name(),
            update.chipset(),
            update.direction()
        );
    m_livings[update.name()] = std::move(living);
}

} // namespace Server

} // namespace Dummy
