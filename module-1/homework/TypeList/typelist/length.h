#pragma once
#include "typelist.h"

template <typename TList> 
struct Length;

template <>
struct Length <NullType>
{
    const static size_t length = 0;
};

template <typename TList>
struct Length
{
    private:
        typedef typename TList::_tail tail;
        const static size_t temp = Length<tail>::length;
    public:
        const static size_t length = temp + 1;
};
