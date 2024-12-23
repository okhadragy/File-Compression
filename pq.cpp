#include "pq.h"


template <typename t, typename y, typename comparator>
PQ<typename t, typename y, typename comparator>::PQ() :heapsize(0) {
	heap = new t[1024]; // further edits
}

template <typename t, typename y, typename comparator>
int PQ<typename t, typename y, typename comparator>::parent(int& i) const{
	return ((i-1)/2);
}

template <typename t, typename y, typename comparator>
int PQ<typename t, typename y, typename comparator>::leftchild(int& i) const{
	return ((2 * i) - 1);
}

template <typename t, typename y, typename comparator>
int PQ<typename t, typename y, typename comparator>::rightchild(int& i) const{
	return ((2 * i) + 1);
}

template <typename t, typename y, typename comparator>
void PQ<typename t, typename y, typename comparator>::bubbleup(int& i) {
	int index = i;
	while (index > 0 && compare(heap[parent(index)], heap[index]) {
		t temp = heap[index];
		heap[index] = heap[parent(index)];
		heap[parent(index)] = temp;
		index = parent(index);
	}
}

template <typename t, typename y, typename comparator>
void PQ<typename t, typename y, typename comparator>::bubbledown(int& i) {
	int parent = i;
	while (1) {
		int left = leftchild(parent), right = rightchild(parent);
		int toSwap = parent;
		if (left < heapsize && compare(heap[toSwap], heap[left]))
			toSwap = left;
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

template <typename t, typename y, typename comparator>
t PQ<typename t, typename y, typename comparator>::top() const{
	if (heapsize > 0) {
		return heap[0];
	}else
		throw new std::runtime_error("[!] Queue is empty!")
}

template <typename t, typename y, typename comparator>
void PQ<typename t, typename y, typename comparator>::push(t& element) {
	if (heapsize < 1024) { // further edits
		heap[heapsize++] = element;
		bubbleup(heapsize - 1);
	}
	else
		throw new std::runtime_error("[!] Maximum size reached");
	
}

template <typename t, typename y, typename comparator>
void PQ<typename t, typename y, typename comparator>::pop() {
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
