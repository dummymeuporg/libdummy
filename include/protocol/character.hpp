#include <string>
#include "protocol/living.hpp"

namespace Dummy {

namespace Protocol {

class Character : public Living {
public:
    Character(std::uint16_t, std::uint16_t, const std::string&);
};

} // namespace Protocol

} // namespace Dummy
