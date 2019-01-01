#ifndef _INSTRUSIVE_LIST_H
#define _INSTRUSIVE_LIST_H

template<typename T>
class InstrusiveList
{
public:
    InstrusiveList()
    :mHead(new T())
    {}
        
    InstrusiveList(const InstrusiveList&) = delete;
    InstrusiveList(InstrusiveList&& o)
    :mHead(o.mHead)
    {
        o.mHead = nullptr;
    }

    ~InstrusiveList()
    {
        delete mHead;
    }

    void PushFront(T* pNode)
    {
        InsertAfter(mHead, pNode);
    }

    void PushBack(T* pNode)
    {
        InsertBefore(mHead, pNode);
    }

    T* PopFront( void )
    {
        auto pNode = mHead->mNext;
        Erase(pNode);
        return pNode;
    }

    T* PopBack( void )
    {
        auto pNode = mHead->mPrev;
        Erase(pNode);
        return pNode;
    }

    static void Erase(T* pNode)
    {
        pNode->mPrev->mNext = pNode->mNext;
        pNode->mNext->mPrev = pNode->mPrev;
        pNode->mPrev = nullptr;
        pNode->mNext = nullptr;
    }

    void InsertAfter(T* pPrev, T* pNode)
    {
        pNode->mNext = pPrev->mNext;
        pNode->mPrev = pPrev;
        pPrev->mNext->mPrev = pNode;
        pPrev->mNext = pNode;
    }

    void InsertBefore(T* pNext, T* pNode)
    {
        pNode->mNext = pNext;
        pNode->mPrev = pNext->mPrev;
        pNext->mPrev->mNext = pNode;
        pNext->mPrev = pNode;
    }


    bool Empty( void ) const
    {
        return mHead == mHead->mNext;
    }

    T* Front( void ) const
    {
        return mHead->mNext;
    }

    T* Back( void )
    {
        return mHead->mPrev;
    }

    bool TraverseEnd(T *pNode) const { return mHead == pNode; }

private:
    T* mHead{nullptr};
};
#endif //_INSTRUSIVE_LIST_H
