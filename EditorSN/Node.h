#ifndef NODE_H
#define NODE_H

template <class T>
struct Node {
    T data;
    Node* next;
    Node(const T& d): data(d), next(nullptr) {}
};

#endif // NODE_H
