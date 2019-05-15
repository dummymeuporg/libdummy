#pragma once

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
    OutgoingPacket& operator<<(const std::uint16_t);
    OutgoingPacket& operator<<(const std::uint32_t);
private:
    void _updateInternalSize();
    std::vector<std::uint8_t> m_buffer;
    std::size_t m_cursor;
};

} // namespace Protocol

} // namespace Dummy
