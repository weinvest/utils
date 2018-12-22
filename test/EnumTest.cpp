#ifndef _WIN32
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include "Enum.h"
#define TEST_VALUES \
((E1, 0x0001))\
((E2, 0x0002))\
((E3, 0x0004))

DECLARE_ENUM(TestEnum, TEST_VALUES)
IMPLEMENT_ENUM(TestEnum, TEST_VALUES)

BOOST_AUTO_TEST_CASE(EnumParse_Test)
{
    TestEnum::type e1, e2, e3, e4;
    BOOST_TEST((TestEnum::Parse("E1", e1)));
    BOOST_TEST(e1 == TestEnum::E1);
    BOOST_TEST((TestEnum::Parse("E2", e2)));
    BOOST_TEST(e2 == TestEnum::E2);
    BOOST_TEST((TestEnum::Parse("E3", e3)));
    BOOST_TEST(e3 == TestEnum::E3);
    BOOST_TEST(!(TestEnum::Parse("E4", e4)));
}

BOOST_AUTO_TEST_CASE(EnumToString_Test)
{
    TestEnum::type e1=TestEnum::E1;
    TestEnum::type e2=TestEnum::E2;
    TestEnum::type e3=TestEnum::E3;
    TestEnum::type e4=TestEnum::type(8);
    BOOST_TEST((TestEnum::ToString(e1) == "E1"));
    BOOST_TEST((TestEnum::ToString(e2) == "E2"));
    BOOST_TEST((TestEnum::ToString(e3) == "E3"));
    BOOST_TEST((TestEnum::ToString(e4) == "UnknowValue4#TestEnum"));
}

DECLARE_ENUM_EX(TestEnumEx, TEST_VALUES)
IMPLEMENT_ENUM_EX(TestEnumEx, TEST_VALUES)

BOOST_AUTO_TEST_CASE(EnumExParse_Test)
{
    int32_t v1;
    BOOST_TEST((TestEnumEx::ParseEx("E1|E2", v1)));
    BOOST_TEST((v1 == (TestEnumEx::E1|TestEnumEx::E2)));
}
