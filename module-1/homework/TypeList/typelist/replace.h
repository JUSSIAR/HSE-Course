#pragma once
#include "typelist.h"

template <typename TList, typename OldType, typename NewType> 
struct Replace;

template <typename TList, typename OldType, typename NewType>
struct Replace
{
    private:
        typedef typename TList::_tail tail;
        typedef typename TList::_head head;
        typedef typename Replace<tail, OldType, NewType>::NewTypeList NewTail;
    public:
        typedef TypeList<head, NewTail> NewTypeList;
};

template <typename TList, typename NewType>
struct Replace <TList, typename TList::_head, NewType>
{
    private:
        typedef typename TList::_tail tail;
        typedef typename TList::_head head;
        typedef typename Replace<tail, head, NewType>::NewTypeList NewTail;
    public:
        typedef TypeList<NewType, NewTail> NewTypeList;
}; 

template <typename OldType, typename NewType>
struct Replace <NullType, OldType, NewType>
{
    typedef NullType NewTypeList;
}; 
