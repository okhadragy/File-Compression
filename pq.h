#include <iostream>
using namespace std;

#ifndef PQ_H
#define PQ_H

template <typename t>
class PQ {
private:
	t* heap;
	int heapsize;
	int parent(const int& i)const;
	int leftchild(const int& i)const;
	int rightchild(const int& i)const;
	void bubbleup(const int& i);
	void bubbledown(const int& i);
	bool compare(t f, t s)const;
public:
	PQ();
	~PQ();
	t top() const;
	void push(const t& element);
	void pop();
	int getSize();
};
#endif 
