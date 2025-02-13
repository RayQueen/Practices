#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

template <typename T>
class Stack: DLList<T>{
    public:
    Stack(): DLList::DLList() {};

    bool isEmpty(){
        return DLList::isEmpty();
    }

    int getCounter(){
        return DLList::getCounter();
    }

    void push(T valid){
        DLList::preInsert(DLList::first(), valid);
    }

    T* first(){
        if(this->isEmpty()) return nullptr;
        return &(first())->payload;
    }

    T* pop(){
        T* x=this->first();
        DLList::remove(DLList::first());
        return x;
    }
};