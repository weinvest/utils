#ifndef _WIN32
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <iomanip>
#include "IntPow.hpp"
#include "Double.h"

BOOST_AUTO_TEST_CASE(IntPow_Test)
{
    double v1 = 3.1415926;
    double v2 = v1*v1;
    double v3 = v2*v1;
    double v4 = v3*v1;
    double v5 = v4*v1;
    double v6 = v5*v1;
    double v7 = v6*v1;
    double v8 = v7*v1;
    double v9 = v8*v1;

    BOOST_TEST((Double::Equal(IntPow<0,double>::GetValue(v1), 1.0)));
    BOOST_TEST((Double::Equal(IntPow<1,double>::GetValue(v1), v1)));
    BOOST_TEST((Double::Equal(IntPow<2,double>::GetValue(v1), v2)));
    BOOST_TEST((Double::Equal(IntPow<3,double>::GetValue(v1), v3)));
    BOOST_TEST((Double::Equal(IntPow<4,double>::GetValue(v1), v4)));
    BOOST_TEST((Double::Equal(IntPow<5,double>::GetValue(v1), v5)));
    BOOST_TEST((Double::Equal(IntPow<6,double>::GetValue(v1), v6)));
    BOOST_TEST((Double::Equal(IntPow<7,double>::GetValue(v1), v7)));
    BOOST_TEST((Double::Equal(IntPow<8,double>::GetValue(v1), v8)));
    BOOST_TEST((Double::Equal(IntPow<9,double>::GetValue(v1), v9)));

    std::cout << std::setprecision(20) << "v6:" << v6 <<"\nv7:" << v7 << "\nv9:"<<v9 << std::endl;
    std::cout << std::setprecision(20) << "p6:" << IntPow<6,double>::GetValue(v1) << std::endl;
    std::cout << std::setprecision(20) << "p7:" << IntPow<7,double>::GetValue(v1) << std::endl;
    std::cout << std::setprecision(20) << "p9:" << IntPow<9,double>::GetValue(v1) << std::endl;
}
