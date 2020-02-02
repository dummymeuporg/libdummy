#include "dummy/server/map_state.hpp"

#include "dummy/protocol/map_update/character_position.hpp"
#include "dummy/protocol/map_update/living_off.hpp"
#include "dummy/protocol/map_update/living_on.hpp"
#include "dummy/protocol/map_update/named_living_on.hpp"
#include "dummy/protocol/map_update/update.hpp"
#include "dummy/protocol/named_living.hpp"

namespace Dummy {
namespace Server {

MapState::MapState() {}

void MapState::update(const Dummy::Protocol::MapUpdate::Update& update)
{
    update.accept(*this);
}

void MapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterPosition& update)
{
    if (m_livings.find(update.id()) == std::end(m_livings)) {
        throw LivingNotFound();
    }

    auto& living = m_livings[update.id()];
    living->setPosition(update.pos());
}

void MapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::LivingOff& update)
{
    if (m_livings.find(update.id()) == std::end(m_livings)) {
        throw LivingNotFound();
    }
    m_livings.erase(update.id());
}

void MapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::LivingOn& update)
{
    std::unique_ptr<Dummy::Protocol::Living> living =
        std::make_unique<Dummy::Protocol::Living>(
            update.id(), update.pos(), update.floor(), update.chipset(),
            update.direction());
    m_livings[update.id()] = std::move(living);
}

void MapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::NamedLivingOn& update)
{
    std::unique_ptr<Dummy::Protocol::NamedLiving> living =
        std::make_unique<Dummy::Protocol::NamedLiving>(
            update.id(), update.pos(), update.floor(), update.name(),
            update.chipset(), update.direction());
    m_livings[update.id()] = std::move(living);
}

} // namespace Server
} // namespace Dummy
