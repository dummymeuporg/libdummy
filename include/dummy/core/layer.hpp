#pragma once

#include "dummy/utils/dummy_types.hpp"
#include <fstream>
#include <vector>

namespace Dummy {
namespace Core {

template <typename T> class Layer
{
public:
    Layer()
        : m_width(0)
        , m_height(0)
    {}

    Layer(uint16_t width, uint16_t height, T defaultValue)
        : m_content(width * height, defaultValue)
        , m_width(width)
        , m_height(height)
    {}

    uint16_t width() const { return m_width; }
    uint16_t height() const { return m_height; }
    size_t size() const { return m_content.size(); }

    // Index must be checked before a call to this method
    T at(tilecoords coords) const
    {
        // cast to uint32_t to be sure to avoid uint16 overflow
        uint32_t rowIdx = coords.second;
        return m_content[coords.first + rowIdx * m_width];
    }

    // Index must be checked before a call to this method
    void set(tilecoords coords, T val)
    {
        // cast to uint32_t to be sure to avoid uint16 overflow
        uint32_t rowIdx = coords.second;

        m_content[coords.first + rowIdx * m_width] = val;
    }

    // Fill the layer data with some raw data.
    void fillWithRawData(std::ifstream& ifs)
    {
        ifs.read(reinterpret_cast<char*>(m_content.data()),
                 static_cast<std::streamsize>(m_content.size() * sizeof(T)));
    }

    // Fill raw data stream from layer data.
    void writeRawData(std::ofstream& ofs) const
    {
        ofs.write(reinterpret_cast<const char*>(m_content.data()),
                  static_cast<std::streamsize>(m_content.size() * sizeof(T)));
    }

private:
    std::vector<T> m_content;
    uint16_t m_width;
    uint16_t m_height;
};

using GraphicLayer  = Layer<tileaspect>;
using BlockingLayer = Layer<uint8_t>;

} // namespace Core
} // namespace Dummy
