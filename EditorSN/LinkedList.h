#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <ostream>
#include <cstddef>

template <class T>
class LinkedList {
    Node<T>* head = nullptr;
    size_t n = 0;

public:
    ~LinkedList() { clear(); }

    void clear() {
        Node<T>* cur = head;
        while (cur) {
            Node<T>* nx = cur->next;
            delete cur;
            cur = nx;
        }
        head = nullptr;
        n = 0;
    }

    size_t size() const { return n; }

    bool insert(size_t pos, const T& value) {
        if (pos > n) return false;
        Node<T>* nuevo = new Node<T>(value);
        if (pos == 0) {
            nuevo->next = head;
            head = nuevo;
        } else {
            Node<T>* cur = head;
            for (size_t i = 0; i + 1 < pos; ++i)
                cur = cur->next;
            nuevo->next = cur->next;
            cur->next = nuevo;
        }
        ++n;
        return true;
    }

    bool erase(size_t pos, T* removedOut = nullptr) {
        if (pos >= n) return false;
        Node<T>* del;
        if (pos == 0) {
            del = head;
            head = head->next;
        } else {
            Node<T>* cur = head;
            for (size_t i = 0; i + 1 < pos; ++i)
                cur = cur->next;
            del = cur->next;
            cur->next = del->next;
        }
        if (removedOut) *removedOut = del->data;
        delete del;
        --n;
        return true;
    }

    T& at(size_t pos) {
        if (pos >= n) std::cout<< "Posicion Invalida" << std::endl; return;
        Node<T>* cur = head;
        for (size_t i = 0; i < pos; ++i)
            cur = cur->next;
        return cur->data;
    }

    const T& at(size_t pos) const {
        if (pos >= n) std::cout<< "Posicion Invalida" << std::endl; return;
        Node<T>* cur = head;
        for (size_t i = 0; i < pos; ++i)
            cur = cur->next;
        return cur->data;
    }
};

#endif // LINKEDLIST_H

