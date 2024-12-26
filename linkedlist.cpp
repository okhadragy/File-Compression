#include "linkedlist.h"
#include <iostream>

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr);

template <typename T>
LinkedList<T>::~LinkedList()
{
    NodePointer current=head;
    while(current ! =nullptr)
    {
    NodePointer next = current->next;
    delete current;
    current = next;
    }
}

template <typename T>
LinkedList<T>::NodePointer LinkedList<T> :: search(T value)const
{
    NodePointer current = head;
    while(current->data ! =nullptr)
    {
        if(current->data==value)
        return value;
        current=current->next;
    }
        cout << "Value " << value << " not found in the list." << endl;
        return ;
}

template <typename T>
int LinkedList<T>::indexOf(T value)const
{
    NodePointer current = head;
    int index = 0;
    while(current->data ! =nullptr)
    {
        if(current->data==value)
        return index;
        current=current->next;
        index++;
    }
        cout << "Value " << value << " not found in the list." << endl;
        return -1;
}

template <typename T>
bool LinkedList <T>::isEmpty()const
{
    return head->data == nullptr;
}
template class LinkedList<int>;