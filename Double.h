#ifndef _DFC_DOUBLECOMPARATOR_H
#define _DFC_DOUBLECOMPARATOR_H
#include <cstdint>
#include <string>
#include <cmath>
#include <limits>
#include "utils/IntPow.hpp"
class Double
{
public:
    static constexpr uint64_t POSITIVE_INFINITY_BIT = 0x7ff0000000000000L;
    static constexpr uint64_t NEGATIVE_INFINITY_BIT = 0xfff0000000000000L;
    static constexpr uint64_t NaN_BIT = 0x7ff8000000000000L;
    static constexpr uint64_t MAX_VALUE_BIT = 0x7fefffffffffffffL;
    static constexpr uint64_t MIN_VALUE_BIT = 0xffefffffffffffffL;
    static constexpr uint64_t SIGN_BIT_MASK = 1UL << (sizeof(double)*8-1);
    static constexpr uint64_t INV_SIGN_BIT_MASK = ~SIGN_BIT_MASK;
    static constexpr uint64_t BASE_BIT_MASK = 0x3ff0000000000000;
    static constexpr double EPSILON = 1e-14;
    static constexpr double DEFAULT_RELATIVE_TOLRENCE = 1e-9;
    static constexpr double DEFAULT_ABSOLUTE_TOLRENCE = 0.0;
public:
    static BOOST_FORCEINLINE double Epsilon() { return EPSILON; }
    static BOOST_FORCEINLINE double PositiveInfinity( void )
    {
        return std::numeric_limits<double>::infinity();
    }

    static BOOST_FORCEINLINE double NegativeInfinity( void )
    {
        return -std::numeric_limits<double>::infinity();
    }

    static BOOST_FORCEINLINE double NaN( void )
    {
        return std::numeric_limits<double>::quiet_NaN();
    }

    static BOOST_FORCEINLINE double MaxValue( void )
    {
        #if defined(max)
        #undef max
        #endif
        return std::numeric_limits<double>::max();
    }

    static BOOST_FORCEINLINE bool IsMaxValue(double v)
    {
        return v == MaxValue();
    }

    static BOOST_FORCEINLINE double MinValue( void )
    {
        #if defined(min)
        #undef min
        #endif
        return -std::numeric_limits<double>::max();
    }

    static BOOST_FORCEINLINE bool IsMinValue(double v)
    {
        return v == MinValue();
    }

    static BOOST_FORCEINLINE bool IsPositiveInfinity(double v)
    {
        return true == std::isinf(v);
    }

    static BOOST_FORCEINLINE bool IsNegativeInfinity(double v)
    {
        return true == std::isinf(-v);
    }

    static BOOST_FORCEINLINE bool IsInfinity(double v)
    {
        return IsPositiveInfinity(v) || IsNegativeInfinity(v);
    }

    static BOOST_FORCEINLINE bool IsNaN(double v)
    {
        return std::isnan(v);
    }

    static BOOST_FORCEINLINE double And(double v1, uint64_t v2)
    {
        auto br = (*(uint64_t*)&v1) & v2;
        return *(double*)&br;
    }

    static BOOST_FORCEINLINE double Or(double v1, uint64_t v2)
    {
        auto br = (*(uint64_t*)&v1) | v2;
        return *(double*)&br;
    }

    static BOOST_FORCEINLINE double Abs(double v)
    {
        return And(v, INV_SIGN_BIT_MASK);
    }

    static BOOST_FORCEINLINE double Max(double v1, double v2)
    {
        return v1 > v2 ? v1 : v2;
    }

    static BOOST_FORCEINLINE double Min(double v1,double v2)
    {
        return v1 < v2 ? v1 : v2;
    }

    static BOOST_FORCEINLINE double Tolrence(double v1
        , double v2
        , double relTol
        , double absTol)
    {
        return Max(relTol*Max(Abs(v1), Abs(v2)), absTol);
    }

    static BOOST_FORCEINLINE bool Equal(double v1
        , double v2
        , double absTol = EPSILON)
    {
        auto diff = v1-v2;
        return Abs(diff) <= absTol;
    }

    static BOOST_FORCEINLINE bool Equal(double v1
        , double v2
        , double relTol
        , double absTol)
    {
        auto tol = Tolrence(v1, v2, relTol, absTol);
        return Equal(v1, v2, tol);
    }

    static BOOST_FORCEINLINE bool NonEqual(double v1
        , double v2
        , double absTol = EPSILON)
    {
        return !Equal(v1, v2, absTol);
    }

    static BOOST_FORCEINLINE bool NonEqual(double v1
        , double v2
        , double relTol
        , double absTol)
    {
        auto tol = Tolrence(v1, v2, relTol, absTol);
        return !Equal(v1, v2, tol);
    }

    static BOOST_FORCEINLINE bool LessEqual(double v1
        , double v2
        , double absTol = EPSILON)
    {
        return v1 <= (v2+absTol);
    }

    static BOOST_FORCEINLINE bool LessEqual(double v1
        , double v2
        , double relTol
        , double absTol)
    {
        auto tol = Tolrence(v1, v2, relTol, absTol);
        return LessThan(v1, v2, tol);
    }


    static BOOST_FORCEINLINE bool GreatEqual(double v1
        , double v2
        , double absTol = EPSILON)
    {
        return v1 >= (v2-absTol);
    }

    static BOOST_FORCEINLINE bool GreatEqual(double v1
        , double v2
        , double relTol
        , double absTol)
    {
        auto tol = Tolrence(v1, v2, relTol, absTol);
        return GreatEqual(v1, v2, tol);
    }


    static BOOST_FORCEINLINE bool LessThan(double v1
        , double v2
        , double absTol = EPSILON)
    {
        return v1 < (v2-absTol);
    }

    static BOOST_FORCEINLINE bool LessThan(double v1
        , double v2
        , double relTol
        , double absTol)
    {
        auto tol = Tolrence(v1, v2, relTol, absTol);
        return LessThan(v1, v2, tol);
    }


    static BOOST_FORCEINLINE bool GreatThan(double v1
        , double v2
        , double absTol = EPSILON)
    {
        return v1 > (v2+absTol);
    }

    static BOOST_FORCEINLINE bool GreatThan(double v1
        , double v2
        , double relTol
        , double absTol)
    {
        auto tol = Tolrence(v1, v2, relTol, absTol);
        return GreatThan(v1, v2, tol);
    }

    static BOOST_FORCEINLINE int Sign(double v)
    {
        return Or(And(v, SIGN_BIT_MASK), BASE_BIT_MASK);
    }

    static double Floor(double v);
    static double Ceil(double v);
    static int32_t Round(double v);
    static BOOST_FORCEINLINE int32_t Round(double v, int nanValue)
    {
        return IsNaN(v) ? nanValue : Round(v);
    }

    static double Parse(const std::string& v);
    static std::string ToString(double v);

    template<int32_t N>
    static BOOST_FORCEINLINE double Pow(double v)
    {
        return IntPow<N, double>::GetValue(v);
    }
};
#endif // _DFC_DOUBLECOMPARATOR_H
