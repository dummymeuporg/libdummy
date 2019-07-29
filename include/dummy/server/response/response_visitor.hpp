#pragma once

#include <exception>

#include <dummy/server/errors.hpp>

namespace Dummy {
namespace Server {
namespace Response {

class ResponseNotHandled : public ::Dummy::Server::Error {
public:
    virtual const char* what() const noexcept override {
        return "this state does not handle such a response";
    }
};

class ConnectResponse;
class CreateCharacter;
class CharactersListResponse;
class Message;
class Ping;
class SelectCharacter;
class SetPosition;
class TeleportMap;

class ResponseVisitor {
public:
    virtual void visitResponse(const ConnectResponse&) {
        throw ResponseNotHandled();
    }
    virtual void visitResponse(const CharactersListResponse&) {
        throw ResponseNotHandled();
    }
    virtual void visitResponse(const CreateCharacter&) {
        throw ResponseNotHandled();
    }
    virtual void visitResponse(const Message&) {
        throw ResponseNotHandled();
    }
    virtual void visitResponse(const SelectCharacter&) {
        throw ResponseNotHandled();
    }
    virtual void visitResponse(const TeleportMap&) {
        throw ResponseNotHandled();
    }
    virtual void visitResponse(const Ping&) {
        throw ResponseNotHandled();
    }
    virtual void visitResponse(const SetPosition&) {
        throw ResponseNotHandled();
    }
};

} // namespace Response
} // namespace Server
} // namespace Dummy
