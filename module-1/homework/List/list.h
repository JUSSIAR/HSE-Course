#pragma once
#include <cstddef>

namespace task {


class list {

public:

    list();
    list(size_t count, const int& value = int());
    list(const list& other);

    ~list();
    list& operator=(const list& other);


    int& front();
    const int& front() const;

    int& back();
    const int& back() const;


    bool empty() const;
    size_t size() const;
    void clear();


    void push_back(const int& value);
    void pop_back();
    void push_front(const int& value);
    void pop_front();
    void resize(size_t count);
    void swap(list& other);


    void remove(const int& value);
    void unique();
    void sort();

private:

    bool operator ==(const list& other) const;
    
    bool push_one(const int& value);
    bool pop_one();
    template <typename T> void My_Swap(T& x, T& y);

    struct node {
        node* prev_node = nullptr;
        node* next_node = nullptr;
        int value;
        node();
        node(const node& other);
        node(int _value);
        ~node();
    };

    node* head;
    node* tail;
    size_t list_size;

};

}  // namespace task
