#include "list.h"

task::list::list() {
    init();
}

task::list::list(size_t count, const int& value) {
    init();
    for (size_t i = 0; i < count; ++i)
        this->push_back(value);
}

task::list::list(const list& other) {
    init();
    node* tmp_ptr = other.head;
    while (tmp_ptr != other.tail) {
        this->push_back(tmp_ptr->value);
        tmp_ptr = tmp_ptr->next_node;
    }
}

task::list::~list() {
    node* to_del = this->head;
    for (node* tmp_ptr = to_del; tmp_ptr != this->tail; ) {
        tmp_ptr = tmp_ptr->next_node;
        delete to_del;
        to_del = tmp_ptr;
    }
    delete to_del;
}

task::list& task::list::operator =(const list& other) {
    if (*this == other)
        return *this;
    this->clear();
    node* tmp_ptr = other.head;
    while (tmp_ptr != other.tail) {
        this->push_back(tmp_ptr->value);
        tmp_ptr = tmp_ptr->next_node;
    }
    return *this;
}


int& task::list::front() {
    return this->head->value;
}

const int& task::list::front() const {
    return this->head->value;
}

int& task::list::back() {
    return this->tail->prev_node->value;
}

const int& task::list::back() const {
    return this->tail->prev_node->value;
}

bool task::list::empty() const {
    return (this->head == this->tail);
}

size_t task::list::size() const {
    return this->list_size;
}


void task::list::clear() {
    if (this->empty())
        return;
    this->list_size = 0;
    node* temp_ptr = this->head;
    this->head = this->tail;
    while (temp_ptr != this->tail) {
        node* to_del = temp_ptr;
        temp_ptr = temp_ptr->next_node;
        delete to_del;
    }
}

void task::list::push_back(const int& value) {
    if (!this->push_one(value)) {
        node* NEW = new node(value);
        NEW->prev_node = this->tail->prev_node;
        NEW->next_node = this->tail;
        this->tail->prev_node->next_node = NEW;
        this->tail->prev_node = NEW;
        this->list_size++;
    }
}

void task::list::pop_back() {
    if (!this->pop_one()) {
        this->list_size--;
        node* to_del = this->tail->prev_node;
        to_del->prev_node->next_node = this->tail;
        this->tail->prev_node = to_del->prev_node;
        to_del->next_node = nullptr;
        to_del->prev_node = nullptr;
        delete to_del;
    }
}

void task::list::push_front(const int& value) {
    if (!this->push_one(value)) {
        node* NEW = new node(value);
        this->head->prev_node = NEW;
        NEW->next_node = this->head;
        this->head = NEW;
        this->list_size++;
    }
}

void task::list::pop_front() {
    if (!this->pop_one()) {
        this->list_size--;
        node* to_del = this->head;
        this->head = to_del->next_node;
        to_del->next_node->prev_node = nullptr;
        to_del->next_node = nullptr;
        to_del->prev_node = nullptr;
        delete to_del;
    }
}

void task::list::resize(size_t count) {
    while (this->size() > count)
        this->pop_back();
    while (this->size() < count)
        this->push_back(0);
}

void task::list::swap(list& other) {
    My_Swap(this->list_size, other.list_size);
    My_Swap(this->head, other.head);
    My_Swap(this->tail, other.tail);
}


void task::list::remove(const int& value) {
    int to_del_element = value;
    node* tmp_ptr = this->head;
    while (tmp_ptr != this->tail) {
        if (tmp_ptr->value != to_del_element) {
            tmp_ptr = tmp_ptr->next_node;
            continue;
        }
        if (tmp_ptr == this->head) {
            tmp_ptr = tmp_ptr->next_node;
            this->pop_front();
        } else {
            this->list_size--;
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
    if (this->empty())
        return;
    node* curr_ptr1 = this->head;
    node* curr_ptr2 = this->head->next_node;
    while (curr_ptr2 != this->tail) {
        if (curr_ptr1->value == curr_ptr2->value) {
            this->list_size--;
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
    if (this->empty())
        return;
    node* curr_ptr = this->head;
    while (curr_ptr != this->tail) {
        node* min_ptr = curr_ptr;
        node* tmp_ptr = curr_ptr;
        while (tmp_ptr != this->tail) {
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
    this->head = new node();
    this->tail = this->head;
    this->list_size = 0;
}

bool task::list::operator ==(const list& other) const {
    if (this->size() != other.size())
        return false;
    size_t len = this->size();
    node* this_ptr = this->head;
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
    if (this->empty()) {
        this->list_size++;
        this->head = new node(value);
        this->head->next_node = this->tail;
        this->tail->prev_node = this->head;
        return true;
    }
    return false;
}

bool task::list::pop_one() {
    if (this->empty())
        return true;
    if (this->size() == 1) {
        this->list_size--;
        node* to_del = this->head;
        this->head = this->tail;
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
    this->value = other.value;
    this->next_node = other.next_node;
    this->prev_node = other.prev_node;
}

task::list::node::node(int _value) {
    this->value = _value;
    this->prev_node = nullptr;
    this->next_node = nullptr;
}