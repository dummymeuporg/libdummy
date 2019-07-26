#define BOOST_TEST_MODULE CHARACTER Unit Tests

#include <boost/test/included/unit_test.hpp>

#include <dummy/core/character.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(character_filename)
{
    Dummy::Core::Character chr;
    chr.setName("Gilebran Scale");
    BOOST_TEST(chr.filename() == "gilebran_scale.dat");

    chr.setName("Test 123 nombre d'or");
    BOOST_TEST(chr.name() == "Test Nombre D'Or");
    chr.setName("Test 123 nom4bre d'or");
    BOOST_TEST(chr.name() == "Test Nombre D'Or");
}
