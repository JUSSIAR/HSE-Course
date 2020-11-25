#pragma once
#include "typelist.h"

template <typename TList, typename TargetType>
struct Erase;

template <typename TList, typename TargetType>
struct Erase
{
    private:
        typedef typename TList::_tail tail;
        typedef typename TList::_head head;
        typedef typename Erase<tail, TargetType>::NewTypeList NewTail;
    public:
        typedef TypeList<head, NewTail> NewTypeList;
};

template <typename TList>
struct Erase <TList, typename TList::_head>
{
    typedef typename TList::_tail NewTypeList;
};

template <typename TargetType>
struct Erase <NullType, TargetType>
{
    typedef NullType NewTypeList;
};
