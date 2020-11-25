#pragma once
#include "typelist.h"

template <typename TList, typename TargetType>
struct EraseAll;

template <typename TList, typename TargetType>
struct EraseAll
{
    private:
        typedef typename TList::_tail tail;
        typedef typename TList::_head head;
        typedef typename EraseAll<tail, TargetType>::NewTypeList NewTail;
    public:
        typedef TypeList<head, NewTail> NewTypeList;
};

template <typename TList>
struct EraseAll <TList, typename TList::_head>
{
    private:
        typedef typename TList::_tail tail;
        typedef typename TList::_head head;
    public:
        typedef typename EraseAll<tail, head>::NewTypeList NewTypeList;
};

template <typename TargetType>
struct EraseAll <NullType, TargetType>
{
    typedef NullType NewTypeList;
};
