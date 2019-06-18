#pragma once

#include "core/map.hpp"

namespace Dummy
{

namespace Core
{

using GraphicLayer = std::vector<std::pair<std::int8_t, std::int8_t>>;

class GraphicMap : public Map {
public:
    GraphicMap(const Project&, const std::string&);
    const std::string& chipset() const {
        return m_chipset;
    }

    const std::string& music() const {
        return m_music;
    }

    const GraphicLayer& firstLayer() const {
        return m_firstLayer;
    }

    const GraphicLayer& secondLayer() const {
        return m_secondLayer;
    }

    const GraphicLayer& thirdLayer() const {
        return m_thirdLayer;
    }

    const GraphicLayer& fourthLayer() const {
        return m_fourthLayer;
    }

    GraphicLayer& firstLayer() {
        return m_firstLayer;
    }

    GraphicLayer& secondLayer() {
        return m_secondLayer;
    }

    GraphicLayer& thirdLayer() {
        return m_thirdLayer;
    }

    GraphicLayer& fourthLayer() {
        return m_fourthLayer;
    }
protected:
    virtual void _loadMapFile(std::ifstream& ifs) override;
protected:
    std::string m_chipset;
    std::string m_music;
    GraphicLayer m_firstLayer;
    GraphicLayer m_secondLayer;
    GraphicLayer m_thirdLayer;
    GraphicLayer m_fourthLayer;
};

} // namespace Core

} // namespace Dummy
