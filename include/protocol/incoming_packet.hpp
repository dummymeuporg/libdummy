#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Dummy {

namespace Protocol {

class IncomingPacket {
public:
    IncomingPacket(const std::uint8_t*);
    IncomingPacket& operator>>(std::string&);
    IncomingPacket& operator>>(std::uint8_t&);
    IncomingPacket& operator>>(std::uint16_t&);
    IncomingPacket& operator>>(std::uint32_t&);
private:
    const std::uint8_t* m_data;
    std::size_t m_cursor;
};

} // namespace Protocol

} // namespace Dummy
