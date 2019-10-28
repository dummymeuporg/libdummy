#include <string>
#include <dummy/protocol/living.hpp>

namespace Dummy {

namespace Protocol {

// XXX: Has become useless. Remove it.
class Character : public Living {
public:
    Character(std::uint32_t,
              std::uint16_t,
              std::uint16_t,
              std::uint8_t,
              const std::string&,
              const std::string&,
              Dummy::Core::Character::Direction direction);
};

} // namespace Protocol

} // namespace Dummy
