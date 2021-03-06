#pragma once

#include <map>
#include <memory>
#include <string>

#include <dummy/protocol/map_update/map_update_visitor.hpp>
#include <dummy/server/errors.hpp>

namespace Dummy {

namespace Protocol {
class Living;

namespace MapUpdate {
class Update;
class CharacterPosition;
class LivingOff;
class LivingOn;
}

} // namespace Protocol

class LivingNotFound : public Server::Error {
public:
    virtual const char* what() const noexcept override {
        return "the living was not found in the map state";
    }
};

namespace Server {
class MapState : public Dummy::Protocol::MapUpdate::MapUpdateVisitor {
public:
    using LivingsMap = std::map<std::uint32_t,
                                std::shared_ptr<Dummy::Protocol::Living>>;
    MapState();
    void update(const Dummy::Protocol::MapUpdate::Update&);

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterPosition&
    ) override;

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::LivingOff&
    ) override;

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::LivingOn&
    ) override;

    void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::NamedLivingOn &
    ) override;

    const LivingsMap& livings() const {
        return m_livings;
    }
    
    const Dummy::Protocol::Living& living(std::uint32_t id) const {
        return *m_livings.at(id);
    }
private:
    LivingsMap m_livings;
};

} // namespace Server
} // namespace Dummy
