#pragma once

#include <map>
#include <memory>
#include <string>

#include "protocol/map_update/map_update_visitor.hpp"
#include "server/errors.hpp"

namespace Dummy {

namespace Protocol {
class Living;

namespace MapUpdate {
class Update;
class CharacterPosition;
class CharacterOff;
class CharacterOn;
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
    using LivingsMap = std::map<std::string,
                                std::shared_ptr<Dummy::Protocol::Living>>;
    MapState();
    void update(const Dummy::Protocol::MapUpdate::Update&);

    virtual void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterPosition&
    );

    virtual void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterOff&
    );

    virtual void visitMapUpdate(
        const Dummy::Protocol::MapUpdate::CharacterOn&
    );

    const LivingsMap& livings() const {
        return m_livings;
    }
    
    const Dummy::Protocol::Living& living(const std::string& name) const {
        return *m_livings.at(name);
    }
private:
    LivingsMap m_livings;
};

} // namespace Server
} // namespace Dummy
