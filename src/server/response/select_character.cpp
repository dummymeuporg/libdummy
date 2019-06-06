#include "core/character.hpp"
#include "server/response/select_character.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void SelectCharacter::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
