#pragma once
#include "erase.h"
#include "eraseall.h"
#include "typelist.h"

template <typename TList>
struct NoDuplicates;

template <typename TList>
struct NoDuplicates
{
    private:
        typedef typename TList::_tail tail;
        typedef typename TList::_head head;
        typedef typename EraseAll<tail, head>::NewTypeList NewTail;
    public:
        typedef TypeList<head, typename NoDuplicates<NewTail>::NewTypeList> NewTypeList;
};

template <>
struct NoDuplicates <NullType>
{
    typedef NullType NewTypeList;
};
