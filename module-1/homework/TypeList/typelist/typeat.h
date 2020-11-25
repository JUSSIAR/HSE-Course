#pragma once
#include "typelist.h"

template <typename TList, unsigned int index>
struct TypeAt;

template <typename TList, unsigned int index>
struct TypeAt
{
    private:
        typedef typename TList::_tail tail;
    public:
        typedef typename TypeAt<tail, index - 1>::TargetType TargetType;
};

template <typename TList>
struct TypeAt <TList, 0>
{
    typedef typename TList::_head TargetType;
};

