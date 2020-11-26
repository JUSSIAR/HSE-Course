#pragma once

template <typename Head, typename Tail> 
struct TypeList;

struct NullType {};

template <typename Head, typename Tail> 
struct TypeList
{
    typedef Head _head;
    typedef Tail _tail; 
};