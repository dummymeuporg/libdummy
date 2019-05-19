#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <iostream>
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

    template<std::size_t SIZE>
    IncomingPacket& operator>>(std::array<std::uint8_t, SIZE>& arr) {
        std::copy(
            m_data + m_cursor,
            m_data + m_cursor + SIZE,
            arr.data()
        );
        m_cursor += SIZE;
        return *this;
    }
private:
    const std::uint8_t* m_data;
    std::size_t m_cursor;
};

} // namespace Protocol

} // namespace Dummy
