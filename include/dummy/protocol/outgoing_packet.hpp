#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace Dummy {
namespace Protocol {

class OutgoingPacket
{
public:
    OutgoingPacket();
    OutgoingPacket(std::size_t);

    std::size_t capacity() const { return m_buffer.size(); }
    uint8_t* buffer() { return m_buffer.data(); }
    uint8_t* data() { return m_buffer.data() + sizeof(uint16_t); }
    const uint8_t* buffer() const { return m_buffer.data(); }
    const uint8_t* data() const
    {
        return m_buffer.data() + sizeof(uint16_t);
    }
    std::size_t size() const { return m_buffer.size(); }
    std::size_t dataSize() const
    {
        return m_buffer.size() - sizeof(uint16_t);
    }

    OutgoingPacket& operator<<(const std::string&);
    OutgoingPacket& operator<<(const uint8_t);
    OutgoingPacket& operator<<(const uint16_t);
    OutgoingPacket& operator<<(const uint32_t);

    template <std::size_t SIZE>
    OutgoingPacket& operator<<(const std::array<uint8_t, SIZE>& arr)
    {
        if (m_buffer.size() < m_cursor + (SIZE * sizeof(uint8_t))) {
            m_buffer.resize(m_buffer.size() + (SIZE * sizeof(uint8_t)));
        }

        std::copy(arr.begin(), arr.end(), m_buffer.begin() + m_cursor);
        m_cursor += sizeof(uint8_t) * SIZE;
        _updateInternalSize();
        return *this;
    }

private:
    void _updateInternalSize();
    std::vector<uint8_t> m_buffer;
    std::size_t m_cursor;
};

} // namespace Protocol
} // namespace Dummy
