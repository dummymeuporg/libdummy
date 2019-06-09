#include "protocol/map_update/update.hpp"
#include "server/map_state.hpp"

namespace Dummy {
namespace Server {

MapState::MapState() {}

void MapState::update(const Dummy::Protocol::MapUpdate::Update& update) {
    update.accept(*this);
}

void MapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterPosition& update
) {

}

void MapState::visitMapUpdate(
    const Dummy::Protocol::MapUpdate::CharacterOff& update
) {

}

} // namespace Server

} // namespace Dummy
