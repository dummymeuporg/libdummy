#pragma once

#include <memory>

#include "server/response/response.hpp"

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
private:
    std::shared_ptr<Dummy::Core::Character> m_character;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
