#pragma once

#include "core/map.hpp"

namespace Dummy
{

namespace Core
{

class GraphicMap : public Map {
    GraphicMap(const Project&, const std::string&);
    friend std::fstream& operator>>(std::fstream&, GraphicMap&);
};

} // namespace Core

} // namespace Dummy
