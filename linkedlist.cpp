#include "linkedlist.h"
#include <iostream>

template <typename T>
LinkedList<typename T> :: LinkedList() : head(nullptr);

template <typename T>
LinkedList<typename T> :: ~LinkedList()
{
    Nodepointer current=head;
    while(current ! =nullptr)
    {
    Nodepointer next = current->next;
    delete current;
    current = next;
    }
}

template <typename T>
LinkedList<typename T> :: NodePointer LinkedList<T> :: search(T value)const
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
int LinkedList<typename T> :: indexOf(T value)const
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
bool LinkedList <typename T> :: isEmpty()const
{
    return head->data == nullptr;
}
template class LinkedList<int>;