/** @file   sky_seq_queue.h 
 *  @brief  Array-based Queue Implentation 
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

// ˳�����

#ifndef _SKY_SEQ_QUEUE_H
#define _SKY_SEQ_QUEUE_H  1

#include <iostream>
#include <cassert>
#include "sky_queue.h"

namespace sky {

/** SeqQueue
 *  ��������Ķ��У����Զ����ݣ�������������У���ʼ��ʱ��ָ�������пռ�
 */
template <typename T>
class SeqQueue : public sky::Queue<T> {
public:
	SeqQueue(int sz = DEFAULT_MAX_QUEUE_SIZE);
	SeqQueue(const SeqQueue& x);
	SeqQueue& operator=(const SeqQueue& x);
	~SeqQueue() { delete[] elem; }
	
	bool isEmpty() const { return len == 0; }         // front == rear        
	bool isFull()  const { return len == maxSize;  }  // ��ʱfront == rear,����п�ʱ��ͬ
	int  length() const { return len;  }
	bool enQueue(const T& x);                        // Ԫ�������
	bool deQueue(T& x);                              // Ԫ�س�����
	bool getFront(T& x) const;                       // ���ض���ͷԪ�أ�����Ԫ�ز�������
    void clear() { front = rear = 0; len = 0;}       // ������գ�����ʵ������ռ�
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const SeqQueue<TT>& x);
private:
	T*  elem;
	int front, rear;    // ��ͷ����β
	int len;            // ����len�ǳ���Ҫ��������о�ֻ��װmaxSize-1��Ԫ��
	int maxSize;
};

/**
 * @brief ���캯������ָ�������пռ�
 */
template <typename T>
SeqQueue<T>::SeqQueue(int sz) : front(0), rear(0), len(0) {
	maxSize = (sz <= 0) ? DEFAULT_MAX_QUEUE_SIZE : sz;
	elem = new T[maxSize];
	assert(elem != NULL);
}

/**
 * @brief �������캯��
 */
template <typename T>
SeqQueue<T>::SeqQueue(const SeqQueue<T>& x) {
	len = x.len;
	maxSize = x.maxSize;
	front = x.front;
	rear = x.rear;
	elem = new T[maxSize];
	assert(elem != NULL);
	// ����Ԫ��
	if (!x.isEmpty()) {
		int i = front;
		do {
			elem[i] = x.elem[i];
			i = (i + 1) % maxSize;
		} while (i != rear);	
	}
}

/**
 * @brief =���������
 */
template <typename T>
SeqQueue<T>& SeqQueue<T>::operator =(const SeqQueue<T>& x) {
	if (this != &x) {
		delete[] elem;
		len = x.len;
		maxSize = x.maxSize;
		front = x.front;
		rear = x.rear;
		elem = new T[maxSize];
		assert(elem != NULL);
		// ����Ԫ��
		if (!x.isEmpty()) {
			int i = front;
			do {
				elem[i] = x.elem[i];
				i = (i + 1) % maxSize;
			}while (i != rear);	
		}	
	}
	
	return *this;
}

/**
 * @brief Ԫ������У����������������false, ���򷵻�true
 */
template <typename T>
bool SeqQueue<T>::enQueue(const T& x) {
	if (isFull())
		return false;
	// ���в�����Ԫ�������, rear�Ķ����Ǳ�β�е�һ���ɲ����λ
	elem[rear] = x;
	rear = (rear + 1) % maxSize;
	len++;
	return true;
}

/**
 * @brief Ԫ�س����У�������пգ�����false, ���򷵻�true
 */
template <typename T>
bool SeqQueue<T>::deQueue(T& x) {
	if (isEmpty())
		return false;
	// ���зǿգ�Ԫ�س�����
	x = elem[front];
	front = (front + 1) % maxSize;
	len--;
	return true;
}

/**
 * @brief ��ȡͷԪ��,ֻ��Ԫ�ظ�������
 */
template <typename T>
bool SeqQueue<T>::getFront(T& x) const {
	if (isEmpty())
		return false;
	// ���зǿգ�Ԫ�س�����
	x = elem[front];
	return true;
}

/**
 * @brief ��ӡ����Ԫ��
 */
template <typename T>
void SeqQueue<T>::output() const {
	std::cout << "[front--> ";
	if (!isEmpty()) {		
		int i = front;
		do {
			std::cout << elem[i] << " ";
			i = (i + 1) % maxSize;
		} while (i != rear);
	}
		
	std::cout << "<--rear]" << std::endl;
}

/**
 * @brief �����<<����
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const SeqQueue<T>& x) {
	os << "[front--> ";
	if (!x.isEmpty()) {	
		int i = x.front;
		do {
			os << x.elem[i] << " ";
			i = (i + 1) % x.maxSize;
		} while (i != x.rear);	
	}
			
	os << "<--rear]";	
}

}  // namespace sky 

#endif /* _SKY_SEQ_QUEUE_H */
