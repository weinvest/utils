#ifndef _FIX_POOL_HPP
#define _FIX_POOL_HPP
#include "utils/InstrusiveList.hpp"
template<typename T>
class FixPool
{
public:
    FixPool(int32_t capacity)
    :mData(new T[capacity])
    {
        assert(capacity > 0);
        for(int32_t iFree = 0; iFree < capacity; ++iFree)
        {
            mFreeLists.PushFront(mData+iFree);
        }
    }

    ~FixPool()
    {
        delete[] mData;
    }

    BOOST_FORCEINLINE int32_t GetCapacity( void ) const
    {
        return mFreeLists.GetSize();
    }

    BOOST_FORCEINLINE T* New( void )
    {
        return mFreeLists.PopFront();
    }

    template<typename ...Args>
    T* Construct(Args&& ...args)
    {
         auto pObject = mFreeLists.PopFront();
         if(BOOST_UNLIKELY(nullptr == pObject))
         {
             return nullptr;
         }

         return new(pObject)T{std::forward<Args>(args)...};
    }

    BOOST_FORCEINLINE void Destory(T* pObject)
    {
        mFreeLists.PushFront(pObject);
    }

private:
    T* mData{nullptr};
    InstrusiveList<T> mFreeLists;
};
#endif //_FIX_POOL_HPP
