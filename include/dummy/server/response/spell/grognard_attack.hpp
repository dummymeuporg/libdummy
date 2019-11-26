#pragma once

#include <memory>

#include <dummy/server/response/response.hpp>

namespace Dummy {
namespace Server {
namespace Response {
namespace Spell {

class GrognardAttack : public Response {
public:
    GrognardAttack(std::uint32_t author, std::uint8_t direction);
    void accept(ResponseVisitor &) const override;
    std::shared_ptr<Response> clone() const override;
    void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    void readFrom(Dummy::Protocol::IncomingPacket&) override;
private:
    std::uint32_t m_author;
    std::uint8_t m_direction;
};

} // namespace Spell
} // namespace Response
} // namespace Server
} // namespace Dummy
