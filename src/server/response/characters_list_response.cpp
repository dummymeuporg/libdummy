#include "server/response/characters_list_response.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void CharactersListResponse::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void
CharactersListResponse::addCharacter(
    std::shared_ptr<Dummy::Core::Character> character
)
{
    m_charactersList.push_back(character);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
