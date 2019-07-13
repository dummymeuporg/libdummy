#pragma once

#include <vector>

#include "core/blocking_layer.hpp"
#include "core/map.hpp"

namespace Dummy {
namespace Remote {

class Map : public Core::Map {
    Map(const std::string&);

    void load() override;

private:
    std::vector<Dummy::Core::BlockingLayer> m_floors;
};

} // namespace Remote
} // namespace Dummy
