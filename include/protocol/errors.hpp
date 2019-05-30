#include <exception>

namespace Dummy {

namespace Protocol {

class Error : public std::exception {

};

class ParseError : public Error {
public:
    virtual const char* what() const noexcept override {
        return "error while parsing the packet.";
    }
};

}; // namespace Protocol

}; // namespace Dummy
