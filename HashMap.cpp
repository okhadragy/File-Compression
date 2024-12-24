
#include "HashMap.h"
#include <iostream>

template <typename K, typename V>
HashMap<K, V>::HashMap(int capacity)
    : capacity(capacity), size(0) {
    table = new Pair<K, V>*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

template <typename K, typename V>
HashMap<K, V>::~HashMap() {
    for (int i = 0; i < capacity; i++) {
        Pair<K, V>* current = table[i];
        while (current) {
            Pair<K, V>* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

template <typename K, typename V>
Pair<K, V>** HashMap<K, V>::getTable(){
    return table;
}

template <typename K, typename V>
int HashMap<K, V>::hashFunction(const K& key) const {
    return std::hash<K>()(key) % capacity;
}

template <typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value) {
    int index = hashFunction(key);
    Pair<K, V>* current = table[index];

    while (current) {
        if (current->key == key) {
            current->value = value; 
            return;
        }
        current = current->next;
    }
    Pair<K, V>* newPair = new Pair<K, V>(key, value);
    newPair->next = table[index];
    table[index] = newPair;
    size++;
}

template <typename K, typename V>
bool HashMap<K, V>::get(const K& key, V& value) const {
    int index = hashFunction(key);
    Pair<K, V>* current = table[index];

    while (current) {
        if (current->key == key) {
            value = current->value;
            return true;
        }
        current = current->next;
    }
    return false;
}
template <typename K, typename V>
bool HashMap<K, V>::remove(const K& key) {
    int index = hashFunction(key);
    Pair<K, V>* current = table[index];
    Pair<K, V>* prev = nullptr;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next; 
            } else {
                table[index] = current->next;
            }
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false; 
}
template <typename K, typename V>
int HashMap<K, V>::getSize() const {
    return size;
}
