#include <string>
#include <dummy/protocol/living.hpp>

namespace Dummy {

namespace Protocol {

class Character : public Living {
public:
    Character(std::uint16_t,
              std::uint16_t,
              const std::string&,
              const std::string&,
              Dummy::Core::Character::Direction direction);
};

} // namespace Protocol

} // namespace Dummy
