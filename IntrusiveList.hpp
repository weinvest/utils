#ifndef _INSTRUSIVE_LIST_H
#define _INSTRUSIVE_LIST_H

template<typename T>
class InstrusiveList
{
public:
    InstrusiveList()
    :mHead(new T())
    ,mSize(0)
    {
        mHead->SetNext(mHead);
        mHead->SetPrev(mHead);
    }

    InstrusiveList(const InstrusiveList&) = delete;
    InstrusiveList(InstrusiveList&& o)
    :mHead(o.mHead)
    ,mSize(o.mSize)
    {
        o.mHead = nullptr;
        o.mSize = 0;
    }

    ~InstrusiveList()
    {
        delete mHead;
    }

    BOOST_FORCEINLINE void PushFront(T* pNode)
    {
        InsertAfter(mHead, pNode);
    }

    BOOST_FORCEINLINE void PushBack(T* pNode)
    {
        InsertBefore(mHead, pNode);
    }

    BOOST_FORCEINLINE T* PopFront( void )
    {
        auto pNode = mHead->GetNext();
        Erase(pNode);
        return pNode;
    }

    BOOST_FORCEINLINE T* PopBack( void )
    {
        auto pNode = mHead->GetPrev();
        Erase(pNode);
        return pNode;
    }

    static BOOST_FORCEINLINE void Erase(T* pNode)
    {
        pNode->GetPrev()->SetNext(pNode->GetNext());
        pNode->GetNext()->SetPrev(pNode->GetPrev());
        pNode->SetPrev(nullptr);
        pNode->SetNext(nullptr);
        --mSize;
    }

    BOOST_FORCEINLINE void InsertAfter(T* pPrev, T* pNode)
    {
        pNode->SetNext(pPrev->GetNext());
        pNode->SetPrev(pPrev);
        pPrev->GetNext->SetPrev(pNode);
        pPrev->SetNext(pNode);
        ++mSize;
    }

    BOOST_FORCEINLINE void InsertBefore(T* pNext, T* pNode)
    {
        pNode->SetNext(pNext);
        pNode->SetPrev(pNext->GetPrev());
        pNext->GetPrev()->SetNext(pNode);
        pNext->SetPrev(pNode);
        ++mSize;
    }

    BOOST_FORCEINLINE int32_t GetSize( void ) const
    {
        return mSize;
    }

    BOOST_FORCEINLINE bool Empty( void ) const
    {
        return mHead == mHead->GetNext();
    }

    BOOST_FORCEINLINE T* Front( void ) const
    {
        return mHead->GetNext();
    }

    BOOST_FORCEINLINE T* Back( void )
    {
        return mHead->GetPrev();
    }

    BOOST_FORCEINLINE T* Begin( void ) const
    {
        return mHead->GetNext();
    }

    BOOST_FORCEINLINE T* End( void ) const
    {
        return mHead;
    }

private:
    T* mHead{nullptr};
    int32_t mSize{0};
};
#endif //_INSTRUSIVE_LIST_H
