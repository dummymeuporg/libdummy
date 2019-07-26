#pragma once

#include <memory>

#include <dummy/server/response/response.hpp>

namespace Dummy {

namespace Core {
class Character;
} // namespace Core

namespace Server {
namespace Response {

class CreateCharacter : public Response {
public:
    virtual void accept(ResponseVisitor&) const override;
    std::shared_ptr<Dummy::Core::Character> character() const {
        return m_character;
    }
    void setCharacter(std::shared_ptr<Dummy::Core::Character> character);
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;
private:
    std::shared_ptr<Dummy::Core::Character> m_character;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
