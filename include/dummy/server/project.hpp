#pragma once

#include <map>
#include <memory>
#include <string>

#include "dummy/core/project.hpp"
#include "dummy/remote/map.hpp"

namespace fs = std::filesystem;

namespace Dummy {
namespace Server {

using RemoteMaps = std::map<std::string,
                            std::unique_ptr<Dummy::Remote::Map>>;

class Project : public Core::Project {
public:
    Project(const fs::path&);
    Project(const std::string&);
    const RemoteMaps& maps() const {
        return m_maps;
    }
protected:
    void onMapFound(const std::string&) override;
    bool mapExists(const std::string&) override;
private:
    RemoteMaps m_maps;
};

} // namespace Server
} // namespace Dummy
