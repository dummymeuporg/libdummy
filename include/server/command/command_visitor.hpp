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
class SelectCharacter;

class CommandVisitor {
public:
    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>    
    visitCommand(const ConnectCommand&) {
        throw CommandNotHandled();
    }

    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>    
    visitCommand(const GetPrimaryInfoCommand&) {
        throw CommandNotHandled();
    }

    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>
    visitCommand(const CreateCharacter&) {
        throw CommandNotHandled();
    }

    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>
    visitCommand(const SelectCharacter&) {
        throw CommandNotHandled();
    }
};

} // namespace Command
} // namespace Server
} // namespace Dummy
