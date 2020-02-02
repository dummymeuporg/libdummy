#pragma once

#include <cstdint>

namespace Dummy {
namespace Protocol {
namespace Bridge {

/* Initial state */
const uint16_t CONNECT = 1;

/* Get Primary Info */
const uint16_t GET_PRIMARY_INFO = 1;

/* Manage Characters */
const uint16_t CREATE_CHARACTER = 1;
const uint16_t SELECT_CHARACTER = 2;

/* Loading state */
const uint16_t TELEPORT_MAP = 5;

/* Playing state */
const uint16_t PING                 = 1;
const uint16_t SET_POSITION         = 2;
const uint16_t MESSAGE              = 3;
const uint16_t CHANGE_CHARACTER     = 4;
const uint16_t PLAYING_TELEPORT_MAP = 5;


/* map updates */
const uint16_t LIVING_OFF         = 1;
const uint16_t LIVING_ON          = 2;
const uint16_t CHARACTER_POSITION = 3;
const uint16_t CHARACTER_FLOOR    = 4;
const uint16_t NAMED_LIVING_ON    = 5;

} // namespace Bridge
} // namespace Protocol
} // namespace Dummy
