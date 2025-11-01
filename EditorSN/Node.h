#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
public:
    T value;
    Node* next;

    Node(const T& data) : value(data), next(nullptr) {}
};

#endif //NODE_H

