#include <algorithm>

#include "dummy/protocol/outgoing_packet.hpp"

namespace Dummy {
namespace Protocol {

OutgoingPacket::OutgoingPacket()
    : m_buffer(sizeof(std::uint16_t))
    , m_cursor(2)
{}

OutgoingPacket::OutgoingPacket(std::size_t initialSize)
    : m_buffer(sizeof(std::uint16_t) + initialSize)
    , m_cursor(2)
{}

OutgoingPacket& OutgoingPacket::operator<<(const std::uint8_t val)
{
    if (m_buffer.size() < m_cursor + sizeof(std::uint8_t)) {
        m_buffer.resize(m_buffer.size() + sizeof(std::uint8_t));
    }
    *(reinterpret_cast<std::uint8_t*>(m_buffer.data() + m_cursor)) = val;
    m_cursor += sizeof(std::uint8_t);
    _updateInternalSize();
    return *this;
}

OutgoingPacket& OutgoingPacket::operator<<(const std::uint16_t val)
{
    if (m_buffer.size() < m_cursor + sizeof(std::uint16_t)) {
        m_buffer.resize(m_buffer.size() + sizeof(std::uint16_t));
    }
    *(reinterpret_cast<std::uint16_t*>(m_buffer.data() + m_cursor)) = val;
    m_cursor += sizeof(std::uint16_t);
    _updateInternalSize();
    return *this;
}

OutgoingPacket& OutgoingPacket::operator<<(const std::uint32_t val)
{
    if (m_buffer.size() < m_cursor + sizeof(std::uint32_t)) {
        m_buffer.resize(m_buffer.size() + sizeof(std::uint32_t));
    }
    *(reinterpret_cast<std::uint32_t*>(m_buffer.data() + m_cursor)) = val;
    m_cursor += sizeof(std::uint32_t);
    _updateInternalSize();
    return *this;
}

OutgoingPacket& OutgoingPacket::operator<<(const std::string& str)
{
    std::size_t appendSize = sizeof(std::uint32_t) + str.size();
    if (m_buffer.size() < m_cursor + appendSize) {
        m_buffer.resize(m_buffer.size() + appendSize);
    }

    *(reinterpret_cast<std::uint32_t*>(m_buffer.data() + m_cursor)) =
        static_cast<std::uint32_t>(str.size());
    m_cursor += sizeof(std::uint32_t);
    std::copy(str.begin(), str.end(), m_buffer.begin() + m_cursor);
    m_cursor += str.size();
    _updateInternalSize();
    return *this;
}

void OutgoingPacket::_updateInternalSize()
{
    *(reinterpret_cast<std::uint16_t*>(m_buffer.data())) =
        static_cast<std::uint16_t>(m_cursor) - sizeof(std::uint16_t);
}

} // namespace Protocol
} // namespace Dummy
