#pragma once

#include "dummy/protocol/errors.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

class MapUpdateNotHandled : public Error
{
public:
    virtual const char* what() const noexcept override
    {
        return "this map update type is not handled";
    }
};

class CharacterFloor;
class LivingOff;
class LivingOn;
class NamedLivingOn;
class CharacterPosition;

class MapUpdateVisitor
{
public:
    virtual void visitMapUpdate(const LivingOff&)
    {
        throw MapUpdateNotHandled();
    }

    virtual void visitMapUpdate(const CharacterPosition&)
    {
        throw MapUpdateNotHandled();
    }

    virtual void visitMapUpdate(const LivingOn&)
    {
        throw MapUpdateNotHandled();
    }

    virtual void visitMapUpdate(const CharacterFloor&)
    {
        throw MapUpdateNotHandled();
    }

    virtual void visitMapUpdate(const NamedLivingOn&)
    {
        throw MapUpdateNotHandled();
    }
};

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
