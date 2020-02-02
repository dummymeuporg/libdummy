#include "dummy/protocol/incoming_packet.hpp"

namespace Dummy {
namespace Protocol {

IncomingPacket::IncomingPacket(const std::uint8_t* data, std::size_t size)
    : m_data(data)
    , m_cursor(0)
    , m_size(size)
{}

IncomingPacket::IncomingPacket(const std::vector<std::uint8_t>& vector)
    : m_data(vector.data())
    , m_cursor(0)
    , m_size(vector.size())
{}

IncomingPacket& IncomingPacket::operator>>(std::string& str)
{
    std::uint32_t strSize;
    *this >> strSize;
    str.resize(strSize);
    std::copy(m_data + m_cursor, m_data + m_cursor + strSize, str.begin());
    m_cursor += strSize;
    return *this;
}

IncomingPacket& IncomingPacket::operator>>(std::uint32_t& value)
{
    return operator>><std::uint32_t>(value);
}

IncomingPacket& IncomingPacket::operator>>(std::uint16_t& value)
{
    return operator>><std::uint16_t>(value);
}

IncomingPacket& IncomingPacket::operator>>(std::uint8_t& value)
{
    return operator>><std::uint8_t>(value);
}

} // namespace Protocol
} // namespace Dummy
