#pragma once

namespace Dummy {
namespace Server {
class Map;
namespace Foe {

class Foe;

class MapCommunicator {
public:
    MapCommunicator(Foe&, Map&);
private:
    Foe& m_foe;
    Map& m_map;
};

} // namespace Foe
} // namespace Server
} // namespace Dummy
