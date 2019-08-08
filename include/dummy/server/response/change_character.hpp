#pragma once

#include <dummy/server/response/characters_list_response.hpp>

namespace Dummy {
namespace Server {
namespace Response {

class ChangeCharacter : public Response {
public:
    ChangeCharacter();
    void setCharacter(std::shared_ptr<Dummy::Core::Character>);
    void accept(ResponseVisitor&) const override;
    void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    void readFrom(Dummy::Protocol::IncomingPacket&) override;
private:
    std::shared_ptr<Dummy::Core::Character> m_character;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
