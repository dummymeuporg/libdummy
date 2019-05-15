#include "protocol/incoming_packet.hpp"

namespace Dummy {

namespace Protocol {

IncomingPacket::IncomingPacket(const std::uint8_t* data)
    : m_data(data), m_cursor(0)
{}

IncomingPacket& IncomingPacket::operator>>(std::string& str)
{
    std::uint32_t strSize;
    *this >> strSize;
    str.resize(strSize);
    std::copy(m_data + m_cursor, m_data + m_cursor + strSize,
              str.begin());
    m_cursor += strSize;
    return *this;
}

IncomingPacket& IncomingPacket::operator>>(std::uint32_t& value)
{
    value = *(reinterpret_cast<const std::uint32_t*>(m_data + m_cursor));
    m_cursor += sizeof(std::uint32_t);
    return *this;
}

IncomingPacket& IncomingPacket::operator>>(std::uint16_t& value)
{
    value = *(reinterpret_cast<const std::uint16_t*>(m_data + m_cursor));
    m_cursor += sizeof(std::uint16_t);
    return *this;
}

} // namespace Protocol

} // namespace Dummy
