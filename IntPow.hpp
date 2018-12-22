#ifndef _INT_POWER_HPP
#define _INT_POWER_HPP
template<int N, typename T>
struct IntPow
{
    inline static const T GetValue(T v)
    {
        return v*IntPow<N-1,T>::GetValue(v);
    }
};

#define MAKE_SPECIAL_INT_POW(N,s)\
template<typename T>\
struct IntPow<N,T>\
{\
    inline static const T GetValue(T v)\
    {\
        return s;\
    }\
};

MAKE_SPECIAL_INT_POW(0, 1.0) //0
MAKE_SPECIAL_INT_POW(1, (v)) //0
MAKE_SPECIAL_INT_POW(2, (v*v)) //1
MAKE_SPECIAL_INT_POW(3, (v*v*v)) //2
MAKE_SPECIAL_INT_POW(4, (IntPow<2,T>::GetValue(IntPow<2,T>::GetValue(v)))) //2
// MAKE_SPECIAL_INT_POW(5, (IntPow<4,T>::GetValue(v)*v)) //3
MAKE_SPECIAL_INT_POW(6, (IntPow<2,T>::GetValue(IntPow<3,T>::GetValue(v)))) //3
// MAKE_SPECIAL_INT_POW(7, (IntPow<6,T>::GetValue(v)*v)) //4
MAKE_SPECIAL_INT_POW(8, (IntPow<2,T>::GetValue(IntPow<2,T>::GetValue(IntPow<2,T>::GetValue(v))))) //3
MAKE_SPECIAL_INT_POW(9, (IntPow<3,T>::GetValue(IntPow<3,T>::GetValue(v)))) //4

#endif
