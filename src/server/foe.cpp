#include <dummy/core/foe.hpp>
#include <dummy/server/foe.hpp>

namespace Dummy {
namespace Server {

Foe::Foe(const Dummy::Core::Foe& foe, const std::string& name)
    : m_name(name),
      m_chipset(foe.chipset()),
      m_position{foe.position().first*2, foe.position().second*2},
      m_floor(foe.floor())
{

}

} // namespace Server
} // namespace Dummy
