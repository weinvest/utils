#ifndef _WIN32
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE UTILS_TEST
#include <boost/test/unit_test.hpp>
#include "json.hpp"

using namespace nlohmann;
BOOST_AUTO_TEST_CASE(AT_NotExists_Test)
{
    json j = {
        {"name", "shgli"},
        {"id", 3}
    };

    BOOST_TEST((j.at("name").get<std::string>() == "shgli"));
    BOOST_REQUIRE_THROW(j.at("descript"), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Value_Default_Test)
{
    json j = {
        {"name", "shgli"},
        {"id", 3}
    };

    BOOST_TEST((j.value("name", "lj") == "shgli"));
    BOOST_TEST((j.value("descript", "ok") == "ok"));
    BOOST_TEST((j.value("descript", 2) == 2));
}
