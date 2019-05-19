#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace Dummy {

namespace Protocol {

class OutgoingPacket {
public:
    OutgoingPacket();
    OutgoingPacket(std::size_t);

    std::size_t capacity() const {
        return m_buffer.size();
    }

    std::uint8_t* buffer() {
        return m_buffer.data();
    }

    std::uint8_t* data() {
        return m_buffer.data() + sizeof(std::uint16_t);
    }

    const std::uint8_t* buffer() const {
        return m_buffer.data();
    }

    const std::uint8_t* data() const {
        return m_buffer.data() + sizeof(std::uint16_t);
    }

    std::size_t size() const {
        return m_buffer.size();
    }

    std::size_t dataSize() const {
        return m_buffer.size() - sizeof(std::uint16_t);
    }

    OutgoingPacket& operator<<(const std::string&);
    OutgoingPacket& operator<<(const std::uint8_t);
    OutgoingPacket& operator<<(const std::uint16_t);
    OutgoingPacket& operator<<(const std::uint32_t);

    template<std::size_t SIZE>
    OutgoingPacket& operator<<(const std::array<std::uint8_t, SIZE>& arr)
    {
        if (m_buffer.size() < m_cursor + (SIZE * sizeof(std::uint8_t))) {
            m_buffer.resize(m_buffer.size() + (SIZE * sizeof(std::uint8_t)));
        }

        std::copy(arr.begin(),
                  arr.end(),
                  m_buffer.begin() + m_cursor);
        m_cursor += sizeof(std::uint8_t) * SIZE;
        _updateInternalSize();
        return *this;

    }
private:
    void _updateInternalSize();
    std::vector<std::uint8_t> m_buffer;
    std::size_t m_cursor;
};

} // namespace Protocol

} // namespace Dummy
