#pragma once

#include <exception>

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

class MapUpdateError : public std::exception {

};

class UnknownUpdateCode : public MapUpdateError {
public:
    const char* what() const noexcept override {
        return "unknown update code";
    }
};

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
