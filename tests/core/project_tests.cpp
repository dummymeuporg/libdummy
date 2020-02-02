#define BOOST_TEST_MODULE PROJECT Unit Tests

#include <algorithm>
#include <filesystem>

#include <boost/test/included/unit_test.hpp>

#include "dummy/core/project.hpp"

using namespace boost::unit_test;

namespace fs = std::filesystem;

BOOST_AUTO_TEST_CASE(load_project)
{
    BOOST_TEST_REQUIRE(framework::master_test_suite().argc == 2);
    fs::path projectPath(framework::master_test_suite().argv[1]);
    
    // Instantiate the project
    Dummy::Core::Project project(projectPath);

    // Will keep track of maps found while parsing the project file.
    std::vector<std::string> referencedMaps;

    // Keep a reference to the project maps
    /*
    const auto& projectMaps(project.maps());

    std::for_each(
        projectMaps.begin(),
        projectMaps.end(),
        [&referencedMaps](auto& i) { referencedMaps.push_back(i.first); }
    );

    std::vector<std::string> expected {"map1", "map2"};
    BOOST_TEST(referencedMaps == expected);
    */

}
