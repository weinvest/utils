//#define private public
#ifndef _WIN32
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include <boost/make_shared.hpp>
#include "utils/Double.h"
#include <iostream>
// #include "teamcity_boost/teamcity_boost.h"

BOOST_AUTO_TEST_SUITE(DoubleTest)
BOOST_AUTO_TEST_CASE(PositiveNifinityTest)
{
   // jetbrains::teamcity::TeamcityGlobalFixture();
   double posInf = Double::PositiveInfinity();
   std::cout<<"positive infinity:"<<posInf<<std::endl;
   BOOST_CHECK(0 == memcmp(&posInf,&Double::_POSITIVE_INFINITY,sizeof(double)));
   BOOST_CHECK(Double::IsPositiveInfinity(posInf));
   BOOST_CHECK(Double::IsInfinity(posInf));
}

BOOST_AUTO_TEST_CASE(NegativeInfinityTest)
{
    double negInf = Double::NegativeInfinity();
    std::cout<<"negative infinity:"<<negInf<<std::endl;

    BOOST_CHECK(0 == memcmp(&negInf,&Double::_NEGATIVE_INFINITY,sizeof(double)));
    BOOST_CHECK(Double::IsNegativeInfinity(negInf));
    BOOST_CHECK(Double::IsInfinity(negInf));
}

BOOST_AUTO_TEST_CASE(MaxValueTest)
{
    double maxValue = Double::MaxValue();
    std::cout<<"max value:"<<maxValue<<std::endl;
    BOOST_CHECK(0 == memcmp(&maxValue,&Double::_MAX_VALUE,sizeof(double)));
    BOOST_CHECK(Double::IsMaxValue(maxValue));
}

BOOST_AUTO_TEST_CASE(MinValueTest)
{
    double minValue = Double::MinValue();
    std::cout<<"min value:"<<minValue<<std::endl;

    BOOST_CHECK(0 == memcmp(&minValue,&Double::_MIN_VALUE,sizeof(double)));
    BOOST_CHECK(Double::IsMinValue(minValue));
}

BOOST_AUTO_TEST_CASE(NaNTest)
{
    double nan = Double::NaN();
    std::cout<<"nan:"<<nan<<std::endl;

    BOOST_CHECK(0 == memcmp(&nan,&Double::_NaN,sizeof(double)));
    BOOST_CHECK(Double::IsNaN(nan));
}

BOOST_AUTO_TEST_CASE(IsValidTest)
{
    double posInf = Double::PositiveInfinity();
    BOOST_CHECK(!Double::IsValid(posInf));

    double negInf = Double::NegativeInfinity();
    BOOST_CHECK(!Double::IsValid(negInf));

    double maxValue = Double::MaxValue();
    BOOST_CHECK(!Double::IsValid(maxValue));

    double minValue = Double::MinValue();
    BOOST_CHECK(!Double::IsValid(minValue));

    double nan = Double::NaN();
    BOOST_CHECK(!Double::IsValid(nan));

    double d = 0.3;
    BOOST_CHECK(Double::IsValid(d));
}

BOOST_AUTO_TEST_CASE(EqualTest)
{
    double d1 = 0.3;
    double d2 = 0.3;
    double d3 = 0.4;
    double d4 = 0.2;

    BOOST_CHECK(Double::Equal(d1,d2));
    BOOST_CHECK(!Double::Equal(d1,d3));
    BOOST_CHECK(!Double::Equal(d1,d4));

    BOOST_TEST(!Double::Equal(Double::NaN(), Double::NaN()));
    BOOST_TEST(!Double::Equal(Double::NaN(), 3.0));
    BOOST_TEST(!Double::Equal(3.0, Double::NaN()));

    BOOST_TEST(Double::Equal(3.2, 3.2));
    BOOST_TEST(Double::Equal(3.2+1E-15, 3.2));
    BOOST_TEST(!Double::Equal(3.2+1E-13, 3.2));

    double tickSize = 0.1*0.5;
    BOOST_TEST(!Double::Equal(3.2, 3.2500001, tickSize));
    BOOST_TEST(Double::Equal(3.2, 3.24999,tickSize));
    BOOST_TEST(Double::Equal(3.2, 3.24, tickSize));
    BOOST_TEST(Double::Equal(3.2, 3.19, tickSize));
    BOOST_TEST(Double::Equal(3.2, 3.1500001, tickSize));
    BOOST_TEST(!Double::Equal(3.2, 3.149999, tickSize));
}

BOOST_AUTO_TEST_CASE(NonEqualTest)
{
    double d1 = 0.4;
    double d2 = 0.3;
    double d3 = 0.4;
    double d4 = 0.2;
    BOOST_CHECK(Double::NonEqual(d1,d2));
    BOOST_CHECK(!Double::NonEqual(d1,d3));
    BOOST_CHECK(Double::NonEqual(d1,d4));

    BOOST_TEST(Double::NonEqual(Double::NaN(), Double::NaN()));
    BOOST_TEST(Double::NonEqual(Double::NaN(), 3.0));
    BOOST_TEST(Double::NonEqual(3.0, Double::NaN()));

    BOOST_TEST(!Double::NonEqual(3.2, 3.2));
    BOOST_TEST(!Double::NonEqual(3.2+1E-15, 3.2));
    BOOST_TEST(Double::NonEqual(3.2+1E-13, 3.2));

    double tickSize = 0.1*0.5;
    BOOST_TEST(Double::NonEqual(3.2, 3.250001, tickSize));
    BOOST_TEST(!Double::NonEqual(3.2, 3.24999,tickSize));
    BOOST_TEST(!Double::NonEqual(3.2, 3.24, tickSize));
    BOOST_TEST(!Double::NonEqual(3.2, 3.19, tickSize));
    BOOST_TEST(!Double::NonEqual(3.2, 3.1500001, tickSize));
    BOOST_TEST(Double::NonEqual(3.2, 3.149999, tickSize));
}

BOOST_AUTO_TEST_CASE(GreatThanTest)
{
    double d1 = 0.4;
    double d2 = 0.3;
    double d3 = 0.4;
    double d4 = 0.5;
    BOOST_CHECK(Double::GreatThan(d1,d2));
    BOOST_CHECK(!Double::GreatThan(d1,d3));
    BOOST_CHECK(!Double::GreatThan(d1,d4));

    BOOST_TEST(!Double::GreatThan(Double::NaN(), Double::NaN()));
    BOOST_TEST(!Double::GreatThan(3.2, Double::NaN()));
    BOOST_TEST(!Double::GreatThan(Double::NaN(), 3.2));

    BOOST_TEST(!Double::GreatThan(3.2, 3.2));
    BOOST_TEST(!Double::GreatThan(3.2, 3.3));

    double tickSize = 0.1*0.5;
    BOOST_TEST(Double::GreatThan(3.2, 3.1, tickSize));
    BOOST_TEST(Double::GreatThan(3.2, 3.14, tickSize));
    BOOST_TEST(Double::GreatThan(3.2, 3.14999999, tickSize));
    BOOST_TEST(!Double::GreatThan(3.2, 3.1500001, tickSize));
    BOOST_TEST(!Double::GreatThan(3.2, 3.18, tickSize));
    BOOST_TEST(!Double::GreatThan(3.2, 3.24, tickSize));
    BOOST_TEST(!Double::GreatThan(3.2, 3.24999999, tickSize));
    BOOST_TEST(!Double::GreatThan(3.2, 3.25000001, tickSize));
    BOOST_TEST(!Double::GreatThan(3.2, 3.26, tickSize));
}

BOOST_AUTO_TEST_CASE(GreatEqualTest)
{
    double d1 = 0.4;
    double d2 = 0.3;
    double d3 = 0.4;
    double d4 = 0.5;
    BOOST_CHECK(Double::GreatEqual(d1,d2));
    BOOST_CHECK(Double::GreatEqual(d1,d3));
    BOOST_CHECK(!Double::GreatEqual(d1,d4));

    BOOST_TEST(!Double::GreatEqual(Double::NaN(), Double::NaN()));
    BOOST_TEST(!Double::GreatEqual(3.2, Double::NaN()));
    BOOST_TEST(!Double::GreatEqual(Double::NaN(), 3.2));

    BOOST_TEST(Double::GreatEqual(3.2, 3.2));
    BOOST_TEST(!Double::GreatEqual(3.2, 3.3));

    double tickSize = 0.1*0.5;
    BOOST_TEST(Double::GreatEqual(3.2, 3.1, tickSize));
    BOOST_TEST(Double::GreatEqual(3.2, 3.14, tickSize));
    BOOST_TEST(Double::GreatEqual(3.2, 3.149999999, tickSize));
    BOOST_TEST(Double::GreatEqual(3.2, 3.150000001, tickSize));
    BOOST_TEST(Double::GreatEqual(3.2, 3.18, tickSize));
    BOOST_TEST(Double::GreatEqual(3.2, 3.249999999, tickSize));
    BOOST_TEST(!Double::GreatEqual(3.2, 3.250000001, tickSize));
    BOOST_TEST(!Double::GreatEqual(3.2, 3.26, tickSize));
}

BOOST_AUTO_TEST_CASE(LessThanTest)
{
    double d1 = 0.4;
    double d2 = 0.5;
    double d3 = 0.4;
    double d4 = 0.2;
    BOOST_CHECK(Double::LessThan(d1,d2));
    BOOST_CHECK(!Double::LessThan(d1,d3));
    BOOST_CHECK(!Double::LessThan(d1,d4));

    BOOST_TEST(!Double::LessThan(Double::NaN(), Double::NaN()));
    BOOST_TEST(!Double::LessThan(3.2, Double::NaN()));
    BOOST_TEST(!Double::LessThan(Double::NaN(), 3.2));

    BOOST_TEST(!Double::LessThan(3.2, 3.2));
    BOOST_TEST(Double::LessThan(3.2, 3.3));

    double tickSize = 0.1*0.5;
    BOOST_TEST(!Double::LessThan(3.2, 3.1, tickSize));
    BOOST_TEST(!Double::LessThan(3.2, 3.14, tickSize));
    BOOST_TEST(!Double::LessThan(3.2, 3.149999999, tickSize));
    BOOST_TEST(!Double::LessThan(3.2, 3.150000001, tickSize));
    BOOST_TEST(!Double::LessThan(3.2, 3.18, tickSize));
    BOOST_TEST(!Double::LessThan(3.2, 3.249999999, tickSize));
    BOOST_TEST(Double::LessThan(3.2, 3.2500000001, tickSize));
    BOOST_TEST(Double::LessThan(3.2, 3.26, tickSize));
}

BOOST_AUTO_TEST_CASE(LessEqualTest)
{
    double d1 = 0.4;
    double d2 = 0.5;
    double d3 = 0.4;
    double d4 = 0.2;
    BOOST_CHECK(Double::LessEqual(d1,d2));
    BOOST_CHECK(Double::LessEqual(d1,d3));
    BOOST_CHECK(!Double::LessEqual(d1,d4));

    BOOST_TEST(!Double::LessEqual(Double::NaN(), Double::NaN()));
    BOOST_TEST(!Double::LessEqual(3.2, Double::NaN()));
    BOOST_TEST(!Double::LessEqual(Double::NaN(), 3.2));

    BOOST_TEST(Double::LessEqual(3.2, 3.2));
    BOOST_TEST(Double::LessEqual(3.2, 3.3));

    double tickSize = 0.1*0.5;
    BOOST_TEST(!Double::LessEqual(3.2, 3.1, tickSize));
    BOOST_TEST(!Double::LessEqual(3.2, 3.14, tickSize));
    BOOST_TEST(Double::LessEqual(3.2, 3.150000001, tickSize));
    BOOST_TEST(Double::LessEqual(3.2, 3.18, tickSize));
    BOOST_TEST(Double::LessEqual(3.2, 3.24, tickSize));
    BOOST_TEST(Double::LessEqual(3.2, 3.249999999, tickSize));
    BOOST_TEST(Double::LessEqual(3.2, 3.250000001, tickSize));
    BOOST_TEST(Double::LessEqual(3.2, 3.26, tickSize));
}
BOOST_AUTO_TEST_SUITE_END()
