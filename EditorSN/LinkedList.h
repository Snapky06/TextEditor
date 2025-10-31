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

    bool insert (size_t pos , const T& Value){

        if(pos > n) std::cout << "Esta Posicion No Existe" << std::endl; return false;

        if(pos == 0){

            Node<T> * tmp = new Node<T>(Value);
            tmp->next = head;
            head = tmp;
            ++n;
            return true;
        }

        Node<T>* tmp = head;
        for(int i = 0 ; i < pos ; i++) tmp = tmp->next;
        Node<T> tmp2 = new Node<T>(Value);
        tmp2.next = tmp->next;
        tmp->next = tmp2;
        ++n;
        return true;
    }

    bool erase (size_t pos, T* removedOut = nullptr){

        if( pos >= n) return false;
        if (pos==0){

            Node<T> del = head;
            if(removedOut) *removedOut = del.data;
            head= head->next;
            delete del;
            --n;
            return true;

        }

        Node<T>* tmp = head;
        for(size_t i = 0; i + 1< pos; i++)tmp = tmp->next;
        Node<T> del = tmp->next;
        if(removedOut) *removedOut = del.data;
        tmp->next = del.next;
        delete del;
        --n;
        return true;
}

    T& at(size_t pos){

        if(pos >= n) std::cout << "Posicion Invalida" << std::endl; return;
        Node<T>* tmp = head;
        for(size_t i = 0; i + 1< pos; i++)tmp = tmp->next;
        return tmp->data;
    }

    T& at(size_t pos) const{

        if(pos >= n) std::cout << "Posicion Invalida" << std::endl; return;
        Node<T>* tmp = head;
        for(size_t i = 0; i + 1< pos; i++)tmp = tmp->next;
        return tmp->data;
    }


};
#endif // LINKEDLIST_H
