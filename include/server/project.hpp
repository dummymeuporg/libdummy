#pragma once

#include "core/project.hpp"

namespace Dummy {
namespace Server {

class Project : public Core::Project {
protected:
    void onMapFound(const std::string&) override;
};

} // namespace Server
} // namespace Dummy
