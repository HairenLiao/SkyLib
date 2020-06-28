/** 
 *  @file   sky_sort.h 
 *  @brief  Implementation of sort
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

/** 
 *  Sky Sort 相关算法
 *  
 */

#ifndef _SKY_SORT_H
#define _SKY_SORT_H  1

#include <vector>
#include <iostream>

namespace sky {


// swap two elements of an array
void swap(int A[], int i, int j) {
    int t = A[i];
    A[i] = A[j];
    A[j] = t;
}

// partition 
int partition(int A[], int left, int right, int pivot_index) {
    int pivot_value = A[pivot_index];
    swap(A, pivot_index, right);

    int store_index = left;

    // 在循环的过程中，store_index的左边值都小于pivot_value，
    // store_index指向的值都大于pivot_value
    // 如果i指向的值小于pivot_value，那么将A中i与store_index的值互换，store_index++
    // 相当于将小于pivot_value的值移动到store_index的左边，store_index+1
    // 循环完毕，因为刚好有store_index个数小于pivot_value，store_index就是pivot_value
    // 需要插入的位置
    for (int i = left; i < right; i++) {
        if (A[i] < pivot_value) {
            swap(A, i, store_index);
            store_index++;
        }
    }

    swap(A, store_index, right);
    return store_index;
}

// quick_sort
void QuickSort(int A[], int left,  int right) {
     if (left < right) {
         // int pivot_index = (left + right) / 2;  This may cause overflow, if left and right is very big
         int pivotIndex = left + (right - left) / 2;
         int pivotNewIndex = partition(A, left, right, pivotIndex);
    
         QuickSort(A, left, pivotIewIndex - 1);
         QuickSort(A, pivotNewIndex + 1, right);
     }
}


template <typename T>
void MergeSort(std::vector<T>& a) {
	std::vector<T> tmpArray(a.size());
	MergeSort(a, tmpArray, 0, a.size()-1);
}


template <typename T>
void MergeSort(std::vector<T>& a, std::vector<T>& tmpArray, int left, int right) {
	if (left < right) {
		int center = (left + right) / 2;
		MergeSort(a, tmpArray, left, center);
		MergeSort(a, tmpArray, center+1, right);
		Merge(a, tmpArray, left, center+1, right);
	}
}

/**
 *  Internal method that merges two sorted halves of a subarray.
 *  a is an array of Comparable items
 */
template <typename T>
void Merge( std::vector<T>& a, std::vector<T>& tmpArray, int leftPos, int rightPos, int rightEnd) {
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;
	
	while (leftPos <= leftEnd && rightPos <= rightEnd) {
		if ( a[ leftPos ] <= a[ rightPos ])
			tmpArray[tmpPos++] = a[leftPos++];
		else 
			tmpArray[tmpPos++] = a[rightPos++];
		
		while (leftPos <= leftEnd)
			tmpArray[tmpPos++] = a[leftPos++];
		
		while (rightPos <= rightEnd)
			tmpArray[tmpPos++] = a[rightPos++];
		
		// Copy tmpArray back
		for (int i = 0; i < numElements; i++, rightEnd--)
			a[rightEnd] = tmpArray[rightEnd];
		
	}
}

template <typename T>
void ShellSort(std::vector<T>& a) {
	for (int gap = a.size() / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < a.size(); i++) {
			T tmp = a[i];
			int j = i;
			
			for (; j >= gap && tmp < a[j-gap]; j -= gap)
				a[j] = a[j-gap];
			a[j] = tmp;
		}
		
	    std::cout << gap << std::endl;
		for (int t=0; t<a.size(); t++)
			std::cout << a[t] << " ";
		std::cout << std::endl;
	}
}

} // namespace sky

#endif 
