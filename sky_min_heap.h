/** @file   sky_min_heap.h 
 *  @brief  Implementation of Min Heap     
 *  @author Hairen Liao(廖海仁） <liaohairen@gmail.com>
 *  
 *  Copyright (c) 2010
 * 
 *  This library is free software; you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software Foundation; 
 *  either version 2, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  本库为作者本人学习数据结构与算法所写，模拟STL标准库，并力求得其精神，不拘其细节。 同时也希望本库对其他初学
 *  数据结构与算法者有所帮助，因此写了相当多的注释和说明。本库属于自由软件，您基本可以自由使用，但作者不为本库的
 *  正确性及其使用做任何担保，包括使用此库完成作业时被视为抄袭。 同时作者也非常乐于听到您的反馈和改进意见。
 *  
 */

#ifndef _SKY_MIN_HEAP_H
#define _SKY_MIN_HEAP_H  1

#include <vector>
#include <iostream>

namespace sky {

template <typename T>
class MinHeap {
	std::vector<T> array;
	int currentSize;
	
	void buildHeap() {
		for (int i = currentSize / 2; i> 0; i--)
			percolateDown(i);
	}
	
	/**
	 * Internal method to percolate down in the heap
	 * hole is the index at which the percolate begins
	 */
	void percolateDown(int hole) {
		int child;
		T tmp = array[hole];
		
		for (; hole * 2 <= currentSize; hole = child) {
			child = hole * 2;
			if (child != currentSize && array[child+1] < array[child])
				child++;
			if (array[child] < tmp)
				array[hole] = array[child];
			else
				break;
		}
		array[hole] = tmp;
		
	}

public:
	explicit MinHeap(int capacity = 100) : array(capacity), currentSize(0) {}
	explicit MinHeap(const std::vector<T>&  items) : array(items.size() + 10), currentSize(items.size())
	{
		for (int i = 0; i < items.size(); i++)
			array[i+1] = items[i];
		buildHeap();
	}
	
	bool isEmpty() const { return currentSize == 0; }
	const T& findMin() const { return array[1]; }
	
	/** 
	 * Insert item x, allowing duplicates.
	 */
	void insert(const T& x) {
	    if (currentSize == array.size() - 1)
	    	array.resize(array.size() * 2);
	    
	    // Percolate up
	    int hole = ++currentSize;
	    for (; hole > 1 && x < array[hole / 2]; hole /= 2)
	    	array[hole] = array[hole / 2];
	    array[hole] = x;
	    
	}
	
	/**
	 * Remove the minimum item
	 * return false if it is empty.
	 */
	bool deleteMin() {
		if (isEmpty())
			return false;   // throw UnderflowExcepton
		
		array[1] = array[currentSize--];
		percolateDown(1);
		return true;
	}
	
	bool deleteMin( T& minItem) {
		if (isEmpty())
			return false;
		
		minItem = array[1];
		array[1] = array[currentSize--];
		percolateDown(1);
		
	}
	
	void makeEmpty() { currentSize = 0; }
	
	void print() {
		for (int i = 1; i <= currentSize; i++)
			std::cout << i << " ";
		std::cout << std::endl;
	}
	
};




}

#endif
