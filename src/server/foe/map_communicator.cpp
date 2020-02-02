#include "dummy/server/foe/map_communicator.hpp"

namespace Dummy {
namespace Server {

namespace Foe {

MapCommunicator::MapCommunicator(Foe& foe, Map& map)
    : m_foe(foe), m_map(map) {}

} // namespace Foe
} // namespace Server
} // namespace Dummy
