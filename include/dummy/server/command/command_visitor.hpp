#pragma once

#include <dummy/server/errors.hpp>

namespace Dummy {
namespace Server {

namespace Response {
    class Response;
}

namespace Command {

class CommandNotHandled : public ::Dummy::Server::Error {
public:
    virtual const char* what() const noexcept override {
        return "this state does not handle such a command";
    };
};

class ChangeCharacter;
class CreateCharacter;
class ConnectCommand;
class GetPrimaryInfoCommand;
class Message;
class Ping;
class SelectCharacter;
class SetPosition;
class TeleportMap;

namespace Spell {
    class GrognardAttack;
    class SentinelleAttack;
    class SpadassinAttack;
}

class CommandVisitor {
public:

    virtual void visitCommand(const ChangeCharacter&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const ConnectCommand&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const CreateCharacter&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const GetPrimaryInfoCommand&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const Message&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const Ping&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const SetPosition&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const SelectCharacter&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const TeleportMap&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const Spell::GrognardAttack&) {
        throw CommandVisitor();
    }

    virtual void visitCommand(const Spell::SentinelleAttack&) {
        throw CommandVisitor();
    }

    virtual void visitCommand(const Spell::SpadassinAttack&) {
        throw CommandVisitor();
    }
};

} // namespace Command
} // namespace Server
} // namespace Dummy
