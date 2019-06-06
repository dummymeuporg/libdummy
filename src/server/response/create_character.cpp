#include "core/character.hpp"
#include "server/response/create_character.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void CreateCharacter::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void
CreateCharacter::setCharacter(std::shared_ptr<Dummy::Core::Character> chr) {
    m_character = chr;
}

} // namespace Response
} // namespace Server
} // namespace Dummy
