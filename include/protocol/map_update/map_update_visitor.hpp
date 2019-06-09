#pragma once

#include "protocol/errors.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

class MapUpdateNotHandled : public Error {
public:
    virtual const char* what() const noexcept override {
        return "this map update type is not handled";
    }
};

class CharacterOff;
class CharacterPosition;

class MapUpdateVisitor {
public:
    virtual void visitMapUpdate(const CharacterOff&) {
        throw MapUpdateNotHandled();
    }

    virtual void visitMapUpdate(const CharacterPosition&) {
        throw MapUpdateNotHandled();
    }
};

} // namespace MapUpdate
} // namespace Server
} // namespace Dummy
