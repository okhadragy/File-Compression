#ifndef HASHMAP_H
#define HASHMAP_H

template <typename K, typename V>
struct Pair {
    K key;
    V value;
    Pair* next;

    Pair(const K& key, const V& value) : key(key), value(value), next(nullptr) {}
};

template <typename K, typename V>
class HashMap {
private:
    Pair<K, V>** table; 
    int capacity;       
    int size;          
    int hashFunction(const K& key) const; 

public:
    HashMap(int capacity);
    ~HashMap();
    Pair<K, V>** getTable();
    void insert(const K& key, const V& value); 
    bool get(const K& key, V& value) const;   
    bool remove(const K& key);                
    int getSize() const;    
    int getCapacity() const;                  
};
#endif 