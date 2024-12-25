#include "pq.h"

template <typename t>
PQ<t>::PQ() :heapsize(0) {
	heap = new t[1024]; // further edits
}

template <typename t>
PQ<t>::~PQ(){
	delete heap;
}

template <typename t>
int PQ<t>::parent(const int& i) const{
	return ((i-1)/2);
}

template <typename t>
int PQ<t>::leftchild(const int& i) const{
	return ((2 * i) + 1);
}

template <typename t>
int PQ<t>::rightchild(const int& i) const{
	return ((2 * i) + 2);
}

template <typename t>
bool PQ<t>::compare(t f, t s) const {
	return (f->frequency > s->frequency);
}

template <typename t>
void PQ<t>::bubbleup(const int& i) {
	int index = i;
	while (index > 0 && compare(heap[parent(index)], heap[index])) {
		t temp = heap[index];
		heap[index] = heap[parent(index)];
		heap[parent(index)] = temp;
		index = parent(index);
	}
}

template <typename t>
void PQ<t>::bubbledown(const int& i) {
	int parent = i, left, right, toSwap;
	while (1) {
		left = leftchild(parent), right = rightchild(parent);
		toSwap = parent;

		if (left < heapsize && compare(heap[toSwap], heap[left])){
			toSwap = left;
		}
			
		if (right < heapsize && compare(heap[toSwap], heap[right]))
			toSwap = right;
		if (toSwap == parent)
			break;
		

		t temp = heap[toSwap];
		heap[toSwap] = heap[parent];
		heap[parent] = temp;
		parent = toSwap;
	}
}

template <typename t>
t PQ<t>::top() const{
	if (heapsize > 0) {
		return heap[0];
	}else
		throw new std::runtime_error("[!] Queue is empty!");
}

template <typename t>
void PQ<t>::push(const t& element) {
	if (heapsize < 1024) { // further edits
		heap[heapsize++] = element;
		bubbleup(heapsize - 1);
	}
	else
		throw new std::runtime_error("[!] Maximum size reached");
}

template <typename t>
void PQ<t>::pop() {
	if (heapsize > 0) {

		t temp = heap[0];
		heap[0] = heap[heapsize - 1];
		heap[heapsize - 1] = temp;
		heapsize--;		
		bubbledown(0);
	}
	else
	{
		throw new runtime_error("[!] Queue is empty!");
	}
}

template <typename t>
int PQ<t>::getSize(){
	return heapsize;
}