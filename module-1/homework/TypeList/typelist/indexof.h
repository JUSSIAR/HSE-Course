#pragma once
#include "typelist.h"

template <typename TList, typename TargetType>
struct IndexOf;

template <typename Head, typename Tail, typename TargetType>
struct IndexOf <TypeList <Head, Tail>, TargetType>
{
    private:
        const static int next = IndexOf<Tail, TargetType>::pos;
    public:
        const static int pos = (next == -1) ? -1 : 1 + next;
};

template <typename Tail, typename TargetType>
struct IndexOf <TypeList <TargetType, Tail>, TargetType>
{
    const static int pos = 0;
};

template <typename TargetType>
struct IndexOf <NullType, TargetType>
{
    const static int pos = -1;
};
