#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <cstddef>
#include "Node.h"

template <class T>
class LinkedList {
    Node<T>* head;
    size_t count;

public:

    LinkedList() {
        head = nullptr;
        count = 0;
    }

    ~LinkedList() { clear(); }

    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        count = 0;
    }

    size_t size() const { return count; }

    bool insert(size_t index, const T& value) {
        if (index > count) return false;

        Node<T>* node = new Node<T>(value);

        if (index == 0) {
            node->next = head;
            head = node;
        } else {
            Node<T>* current = head;
            for (size_t i = 0; i + 1 < index; ++i) current = current->next;
            node->next = current->next;
            current->next = node;
        }

        ++count;
        return true;
    }

    bool remove(size_t index, T* removed = nullptr) {
        if (index >= count) return false;

        Node<T>* del;

        if (index == 0) {
            del = head;
            head = head->next;
        } else {
            Node<T>* current = head;
            for (size_t i = 0; i + 1 < index; ++i) current = current->next;
            del = current->next;
            current->next = del->next;
        }

        if (removed) *removed = del->value;
        delete del;
        --count;
        return true;
    }

    T& at(size_t index) {
        if (index >= count) throw std::out_of_range("index out of range");
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) current = current->next;
        return current->value;
    }

    const T& at(size_t index) const {
        if (index >= count) throw std::out_of_range("index out of range");
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) current = current->next;
        return current->value;
    }
};
#endif //LINKEDLIST_H
