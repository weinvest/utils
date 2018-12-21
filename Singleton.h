#ifndef _SINGLETON_H
#define _SINGLETON_H
#include <cstdint>
#include <boost/noncopyable.hpp>
#include <memory>
#include <mutex>

#define DECLARE_AS_SINGLETON(T)\
public:\
    static T& Instance( void );\
private:\
    T();\
    T(const T&);

#define IMPLEMENT_SINGLETON(T)\
    T& T::Instance( void )\
        {\
            static std::shared_ptr<T> gpInstance;\
            if(BOOST_LIKELY(nullptr != gpInstance)) { return *gpInstance; }\
            static std::once_flag init_instance;\
            std::call_once(init_instance,[](){gpInstance.reset(new T());});\
            return *gpInstance;\
        }
#endif
