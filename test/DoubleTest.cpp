//#define private public
#ifndef _WIN32
#define BOOST_TEST_DYN_LINK
#endif
#include <random>
#include <valarray>
#include <boost/timer/timer.hpp>

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
   BOOST_CHECK(0 == memcmp(&posInf,&Double::POSITIVE_INFINITY_BIT,sizeof(double)));
   BOOST_CHECK(Double::IsPositiveInfinity(posInf));
   BOOST_CHECK(Double::IsInfinity(posInf));
}

BOOST_AUTO_TEST_CASE(NegativeInfinityTest)
{
    double negInf = Double::NegativeInfinity();
    std::cout<<"negative infinity:"<<negInf<<std::endl;

    BOOST_CHECK(0 == memcmp(&negInf,&Double::NEGATIVE_INFINITY_BIT,sizeof(double)));
    BOOST_CHECK(Double::IsNegativeInfinity(negInf));
    BOOST_CHECK(Double::IsInfinity(negInf));
}

BOOST_AUTO_TEST_CASE(MaxValueTest)
{
    double maxValue = Double::MaxValue();
    std::cout<<"max value:"<<maxValue<<std::endl;
    BOOST_CHECK(0 == memcmp(&maxValue,&Double::MAX_VALUE_BIT,sizeof(double)));
    BOOST_CHECK(Double::IsMaxValue(maxValue));
}

BOOST_AUTO_TEST_CASE(MinValueTest)
{
    double minValue = Double::MinValue();
    std::cout<<"min value:"<<minValue<<std::endl;

    BOOST_CHECK(0 == memcmp(&minValue,&Double::MIN_VALUE_BIT,sizeof(double)));
    BOOST_CHECK(Double::IsMinValue(minValue));
}

BOOST_AUTO_TEST_CASE(NaNTest)
{
    double nan = Double::NaN();
    std::cout<<"nan:"<<nan<<std::endl;

    BOOST_CHECK(0 == memcmp(&nan,&Double::NaN_BIT,sizeof(double)));
    BOOST_CHECK(Double::IsNaN(nan));
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

BOOST_AUTO_TEST_CASE(SignTest)
{
    double neg(-1.8), posi(1.9), inf(Double::PositiveInfinity());
    double ninf(Double::NegativeInfinity()), nan(Double::NaN());
    BOOST_TEST(-1.0 == Double::Sign(neg));
    BOOST_TEST(1.0 == Double::Sign(posi));
    BOOST_TEST(1.0 == Double::Sign(inf));
    BOOST_TEST(-1.0 == Double::Sign(ninf));
    BOOST_TEST(1.0 == Double::Sign(nan));
    BOOST_TEST(0.0 == Double::Sign(0.0));
}

BOOST_AUTO_TEST_CASE(AbsSpeadTest)
{
    static constexpr int32_t MAX_SAMPLE_COUNT = 1000000;
    std::default_random_engine gen;
    std::uniform_real_distribution<double> realUni(-1000.0, 1000.0);
    std::valarray<double> samples(MAX_SAMPLE_COUNT);
    std::valarray<double> result1(MAX_SAMPLE_COUNT);
    std::valarray<double> result2(MAX_SAMPLE_COUNT);

    for(int32_t iSample = 0; iSample < MAX_SAMPLE_COUNT; ++iSample)
    {
        samples[iSample] = realUni(gen);
    }

    {
        boost::timer::auto_cpu_timer t("std::abs consume %t sec CPU, %w sec real, %u sec user\n");
        for(int32_t iSample = 0; iSample < MAX_SAMPLE_COUNT; ++iSample)
        {
            result2[iSample] = std::abs(samples[iSample]);
        }
    }

    {
        boost::timer::auto_cpu_timer t("Double::Abs consume %t sec CPU, %w sec real, %u sec user\n");
        for(int32_t iSample = 0; iSample < MAX_SAMPLE_COUNT; ++iSample)
        {
            result1[iSample] = Double::Abs(samples[iSample]);
        }
    }
}
BOOST_AUTO_TEST_SUITE_END()
