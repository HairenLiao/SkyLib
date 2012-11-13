/** @file   sky_min_heap.h 
 *  @brief  Implementation of Min Heap     
 *  @author Hairen Liao(�κ��ʣ� <liaohairen@gmail.com>
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
 *  ����Ϊ���߱���ѧϰ���ݽṹ���㷨��д��ģ��STL��׼�⣬��������侫�񣬲�����ϸ�ڡ� ͬʱҲϣ�������������ѧ
 *  ���ݽṹ���㷨���������������д���൱���ע�ͺ�˵�����������������������������������ʹ�ã������߲�Ϊ�����
 *  ��ȷ�Լ���ʹ�����κε���������ʹ�ô˿������ҵʱ����Ϊ��Ϯ�� ͬʱ����Ҳ�ǳ������������ķ����͸Ľ������
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
