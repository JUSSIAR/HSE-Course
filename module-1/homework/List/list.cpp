#include "list.h"

task::list::list() {
    init();
}

task::list::list(size_t count, const int& value) {
    init();
    for (size_t i = 0; i < count; ++i)
        push_back(value);
}

task::list::list(const list& other) {
    init();
    node* tmp_ptr = other.head;
    while (tmp_ptr != other.tail) {
        push_back(tmp_ptr->value);
        tmp_ptr = tmp_ptr->next_node;
    }
}

task::list::~list() {
    node* to_del = head;
    for (node* tmp_ptr = to_del; tmp_ptr != tail; ) {
        tmp_ptr = tmp_ptr->next_node;
        delete to_del;
        to_del = tmp_ptr;
    }
    delete to_del;
}

task::list& task::list::operator =(const list& other) {
    if (*this == other)
        return *this;
    clear();
    node* tmp_ptr = other.head;
    while (tmp_ptr != other.tail) {
        push_back(tmp_ptr->value);
        tmp_ptr = tmp_ptr->next_node;
    }
    return *this;
}


int& task::list::front() {
    return head->value;
}

const int& task::list::front() const {
    return head->value;
}

int& task::list::back() {
    return tail->prev_node->value;
}

const int& task::list::back() const {
    return tail->prev_node->value;
}

bool task::list::empty() const {
    return (head == tail);
}

size_t task::list::size() const {
    return list_size;
}


void task::list::clear() {
    if (empty())
        return;
    list_size = 0;
    node* temp_ptr = head;
    head = tail;
    while (temp_ptr != tail) {
        node* to_del = temp_ptr;
        temp_ptr = temp_ptr->next_node;
        delete to_del;
    }
}

void task::list::push_back(const int& value) {
    if (!push_one(value)) {
        node* NEW = new node(value);
        NEW->prev_node = tail->prev_node;
        NEW->next_node = tail;
        tail->prev_node->next_node = NEW;
        tail->prev_node = NEW;
        list_size++;
    }
}

void task::list::pop_back() {
    if (!pop_one()) {
        list_size--;
        node* to_del = tail->prev_node;
        to_del->prev_node->next_node = tail;
        tail->prev_node = to_del->prev_node;
        to_del->next_node = nullptr;
        to_del->prev_node = nullptr;
        delete to_del;
    }
}

void task::list::push_front(const int& value) {
    if (!push_one(value)) {
        node* NEW = new node(value);
        head->prev_node = NEW;
        NEW->next_node = head;
        head = NEW;
        list_size++;
    }
}

void task::list::pop_front() {
    if (!pop_one()) {
        list_size--;
        node* to_del = head;
        head = to_del->next_node;
        to_del->next_node->prev_node = nullptr;
        to_del->next_node = nullptr;
        to_del->prev_node = nullptr;
        delete to_del;
    }
}

void task::list::resize(size_t count) {
    while (size() > count)
        pop_back();
    while (size() < count)
        push_back(0);
}

void task::list::swap(list& other) {
    My_Swap(list_size, other.list_size);
    My_Swap(head, other.head);
    My_Swap(tail, other.tail);
}


void task::list::remove(const int& value) {
    int to_del_element = value;
    node* tmp_ptr = head;
    while (tmp_ptr != tail) {
        if (tmp_ptr->value != to_del_element) {
            tmp_ptr = tmp_ptr->next_node;
            continue;
        }
        if (tmp_ptr == head) {
            tmp_ptr = tmp_ptr->next_node;
            pop_front();
        } else {
            list_size--;
            node* to_del = tmp_ptr;
            tmp_ptr->prev_node->next_node = to_del->next_node;
            tmp_ptr = tmp_ptr->next_node;
            tmp_ptr->prev_node = to_del->prev_node;
            to_del->prev_node = nullptr;
            to_del->next_node = nullptr;
            delete to_del;
        }
    }
}

void task::list::unique() {
    if (empty())
        return;
    node* curr_ptr1 = head;
    node* curr_ptr2 = head->next_node;
    while (curr_ptr2 != tail) {
        if (curr_ptr1->value == curr_ptr2->value) {
            list_size--;
            node* to_del = curr_ptr2;
            curr_ptr2->prev_node->next_node = to_del->next_node;
            curr_ptr2 = curr_ptr2->next_node;
            curr_ptr2->prev_node = to_del->prev_node;
            to_del->prev_node = nullptr;
            to_del->next_node = nullptr;
            delete to_del;
        } else {
            curr_ptr2 = curr_ptr2->next_node;
            curr_ptr1 = curr_ptr1->next_node;
        }
    }
}

void task::list::sort() {
    if (empty())
        return;
    node* curr_ptr = head;
    while (curr_ptr != tail) {
        node* min_ptr = curr_ptr;
        node* tmp_ptr = curr_ptr;
        while (tmp_ptr != tail) {
            if (tmp_ptr->value < min_ptr->value)
                min_ptr = tmp_ptr;
            tmp_ptr = tmp_ptr->next_node;
        }
        int temp_val = curr_ptr->value;
        curr_ptr->value = min_ptr->value;
        min_ptr->value = temp_val;
        curr_ptr = curr_ptr->next_node;
    }
}

void task::list::init() {
    head = new node();
    tail = head;
    list_size = 0;
}

bool task::list::operator ==(const list& other) const {
    if (size() != other.size())
        return false;
    size_t len = size();
    node* this_ptr = head;
    node* other_ptr = other.head;
    for (size_t i = 0; i < len; ++i) {
        if (this_ptr->value != other_ptr->value)
            return false;
        this_ptr = this_ptr->next_node;
        other_ptr = other_ptr->next_node;
    }
    return true;
}

bool task::list::push_one(const int& value) {
    if (empty()) {
        list_size++;
        head = new node(value);
        head->next_node = tail;
        tail->prev_node = head;
        return true;
    }
    return false;
}

bool task::list::pop_one() {
    if (empty())
        return true;
    if (size() == 1) {
        list_size--;
        node* to_del = head;
        head = tail;
        to_del->next_node = nullptr;
        to_del->prev_node = nullptr;
        delete to_del;
        return true;
    }
    return false;
}

template <typename T> void task::list::My_Swap(T& x, T& y) {
    T z = x;
    x = y;
    y = z;
}

task::list::node::node() = default;
task::list::node::~node() = default;

task::list::node::node(const node& other) {
    value = other.value;
    next_node = other.next_node;
    prev_node = other.prev_node;
}

task::list::node::node(int _value) {
    value = _value;
    prev_node = nullptr;
    next_node = nullptr;
}