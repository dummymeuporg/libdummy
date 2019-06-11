#pragma once

#include "server/errors.hpp"

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

class CreateCharacter;
class ConnectCommand;
class GetPrimaryInfoCommand;
class Ping;
class SelectCharacter;
class SetPosition;
class TeleportMap;

class CommandVisitor {
public:
    virtual void visitCommand(const ConnectCommand&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const GetPrimaryInfoCommand&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const CreateCharacter&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const SelectCharacter&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const TeleportMap&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const Ping&) {
        throw CommandNotHandled();
    }

    virtual void visitCommand(const SetPosition&) {
        throw CommandNotHandled();
    }
};

} // namespace Command
} // namespace Server
} // namespace Dummy
