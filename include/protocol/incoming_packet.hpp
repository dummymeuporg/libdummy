#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>

#include "protocol/errors.hpp"

namespace Dummy {

namespace Protocol {

class IncomingPacket {
public:
    IncomingPacket(const std::uint8_t*, std::size_t);
    IncomingPacket(const std::vector<std::uint8_t>&);
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
    template<typename T>
    IncomingPacket& operator>>(T& value) {
        if (m_size - m_cursor < sizeof(T)) {
            throw ParseError();
        }
        value = *(reinterpret_cast<const T*>(m_data + m_cursor));
        m_cursor += sizeof(T);
        return *this;
    }
    const std::uint8_t* m_data;
    std::size_t m_cursor;
    std::size_t m_size;
};

} // namespace Protocol

} // namespace Dummy
