#define BOOST_TEST_MODULE CHARACTER_READ_FILE Unit Tests

#include <boost/test/included/unit_test.hpp>

#include <dummy/core/character.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(character_filename)
{
    BOOST_TEST_REQUIRE(framework::master_test_suite().argc == 2);
    std::ifstream ifs(framework::master_test_suite().argv[1],
                      std::ios::binary);
    Dummy::Core::Character chr;
    ifs >> chr;
    BOOST_TEST(chr.name() == "Gilebran Scale");
    BOOST_TEST(chr.skin() == "WhiteScale.png");
    BOOST_TEST(chr.position().first == 14);
    BOOST_TEST(chr.position().second == 6);
    BOOST_TEST(chr.mapLocation() == "LhynnBis");
}
