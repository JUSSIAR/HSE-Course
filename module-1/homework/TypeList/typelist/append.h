#pragma once
#include "typelist.h"

template <typename TList, typename NewType>
struct Append;

template <typename TList, typename NewType>
struct Append
{
    private:
        typedef typename TList::_tail tail;
        typedef typename TList::_head head;
        typedef typename Append<tail, NewType>::NewTypeList NewTail;
    public:
        typedef TypeList<head, NewTail> NewTypeList;
};

template <typename NewType>
struct Append <NullType, NewType>
{
    typedef TypeList <NewType, NullType> NewTypeList;
};

template <>
struct Append <NullType, NullType>
{
    typedef NullType NewTypeList;
};

