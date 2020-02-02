#pragma once

#include <string>

#include "dummy/protocol/living.hpp"

namespace Dummy {
namespace Protocol {

// XXX: Has become useless. Remove it.
class Character : public Living
{
public:
    Character(uint32_t, tilecoords, uint8_t, const std::string&,
              const std::string&, Dummy::Core::Character::Direction direction);
};

} // namespace Protocol
} // namespace Dummy
