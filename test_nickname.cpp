#define BOOST_TEST_MODULE test_nickname

#include "nickname.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_nickname)

BOOST_AUTO_TEST_CASE(test_find)
{

    RadixTree nicknames;

    nicknames.add("Denis");

    BOOST_CHECK(nicknames.find("Denis"));

    BOOST_CHECK(!nicknames.find("Dinsul"));
}

BOOST_AUTO_TEST_CASE(test_print)
{

    RadixTree nicknames;

    nicknames.add("Denis");
    nicknames.add("Dinsul");
    nicknames.add("Den");

    nicknames.printTree();

    BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()
