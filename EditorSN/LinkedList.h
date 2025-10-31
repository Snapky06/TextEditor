#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
template <class T>

class LinkedList
{
    Node<T> * head = nullptr;
    size_t n = 0;

public:
    ~LinkedList(){ clear(); }

    void clear(){

        Node<T> * tmp = head;
        while(tmp){

            Node<T> * tmp2 = tmp->next;
            delete tmp;
            tmp = tmp2;
        }
        head = nullptr;
        n=0;
    }

    size_t size()const {return n;};

    void push_back(const T& Value){

        if(!head){

            head = new Node<T>(Value);

        }else{

            Node<T>* tmp = head;
            while(tmp->next) tmp = tmp->next;
            tmp->next = new Node<T>(Value);

        }
        n++;
    }
};
#endif // LINKEDLIST_H
