#pragma once

#include <cstdint>
#include <memory>

namespace Dummy {
namespace Protocol {
class IncomingPacket;
class OutgoingPacket;
} // namespace Protocol
namespace Server {
namespace Response {

class ResponseVisitor;

class Response : public std::enable_shared_from_this<Response> {
public:
    Response();
    std::uint8_t status() const {
        return m_status;
    }

    void setStatus(std::uint8_t status);
    virtual void accept(ResponseVisitor&) const = 0;
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const = 0;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) = 0;
protected:
    std::uint8_t m_status;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
