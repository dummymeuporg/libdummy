#pragma once

#include <memory>

#include "dummy/core/character.hpp"
#include "dummy/server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Response {

class CharactersListResponse : public Response
{

public:
    using CharactersList = std::vector<std::shared_ptr<Dummy::Core::Character>>;
    virtual void accept(ResponseVisitor&) const override;
    std::shared_ptr<Response> clone() const override;
    const CharactersList& charactersList() const { return m_charactersList; }
    void addCharacter(std::shared_ptr<Dummy::Core::Character>);
    virtual void
    serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;

private:
    CharactersList m_charactersList;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
