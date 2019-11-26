#include <dummy/server/response/response_visitor.hpp>
#include <dummy/server/response/spell/grognard_attack.hpp>


namespace Dummy {
namespace Server {
namespace Response {
namespace Spell {

GrognardAttack::GrognardAttack(std::uint32_t author, std::uint8_t direction)
    : m_author(author), m_direction(direction)
{}

void GrognardAttack::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

std::shared_ptr<Response> GrognardAttack::clone() const {
    return std::make_shared<GrognardAttack>(*this);
}

void GrognardAttack::serializeTo(Dummy::Protocol::OutgoingPacket&) const {

}

void GrognardAttack::readFrom(Dummy::Protocol::IncomingPacket&) {

}

} // namespace Spell
} // namespace Response
} // namespace Server
} // namespace Dummy
