#ifndef STACK_H
#define STACK_H

#include <vector>
template<class T>
class Stack
{
    std::vector<T> v ;

public :
    void push(const T& x) {v.push_back(x);}
    void pop() {if(!v.empty()) v.pop_back();}
    T& top() {return v.back();}
    const T& top() const{return v.back;}
    bool empty(){return v.empty();}
    size_t size() const{ return v.size(); }
    void clear() {v.clear();}
};
#endif // STACK_H
