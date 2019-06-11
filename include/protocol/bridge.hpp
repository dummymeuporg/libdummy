#pragma once

#include <cstdint>

namespace Dummy {
namespace Protocol {
namespace Bridge {

/* Initial state */
const std::uint16_t CONNECT = 1;

/* Get Primary Info */
const std::uint16_t GET_PRIMARY_INFO = 1;

/* Manage Characters */
const std::uint16_t CREATE_CHARACTER = 1;
const std::uint16_t SELECT_CHARACTER = 2;

/* Loading state */
const std::uint16_t TELEPORT_MAP = 1;


/* map updates */
const std::uint16_t CHARACTER_OFF = 1;
const std::uint16_t CHARACTER_ON = 2;
const std::uint16_t CHARACTER_POSITION = 3;

} // namespace Bridge
} // namespace Protocol
} // namespace Dummy
