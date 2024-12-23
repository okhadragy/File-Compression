#include <iostream>
using namespace std;

#ifndef PQ_H
#define PQ_H

template <typename t,typename y,typename comparator>
class PQ {
private:
	t* heap;
	comparator compare;
	int heapsize;
	int parent(int& i)const;
	int leftchild(int& i)const;
	int rightchild(int& i)const;
	void bubbleup(int& i);
	void bubbledown(int& i);
public:
	PQ();
	t top() const;
	void push(t& element);
	void pop();
};


#endif 
