#ifndef STACK_H
#define STACK_H

#include <vector>

template <class T>
class Stack {
    std::vector<T> data;

public:
    void push(const T& v) { data.push_back(v); }
    void pop() { if (!data.empty()) data.pop_back(); }
    T& top() { return data.back(); }
    const T& top() const { return data.back(); }
    bool empty() const { return data.empty(); }
    void clear() { data.clear(); }
};

#endif // STACK_H
