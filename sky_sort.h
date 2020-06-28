/** 
 *  @file   sky_sort.h 
 *  @brief  Implementation of sort
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

/** 
 *  Sky Sort ����㷨
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

    // ��ѭ���Ĺ����У�store_index�����ֵ��С��pivot_value��
    // store_indexָ���ֵ������pivot_value
    // ���iָ���ֵС��pivot_value����ô��A��i��store_index��ֵ������store_index++
    // �൱�ڽ�С��pivot_value��ֵ�ƶ���store_index����ߣ�store_index+1
    // ѭ����ϣ���Ϊ�պ���store_index����С��pivot_value��store_index����pivot_value
    // ��Ҫ�����λ��
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
