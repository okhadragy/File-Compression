#pragma once
#include <iostream>
template <typename T>
class LinkedList
{
    
    public:
    class Node
    {
        public:
        T data;
        Node *next;

    };
    using NodePointer = Node*;
    private:
    Nodepointer head;

    public:

    LinkedList();
    ~LinkedList();
    NodePointer search(T value)const;
    int indexOf(T value)const;
    bool isEmpty()const;


};
