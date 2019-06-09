#pragma once

#include <map>
#include <memory>
#include <string>

#include "protocol/map_update/map_update_visitor.hpp"

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
private:
    LivingsMap m_livings;
};

} // namespace Server
} // namespace Dummy
