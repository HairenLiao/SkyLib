/** @file   sky_seq_queue.h 
 *  @brief  Array-based Queue Implentation 
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

// 顺序队列

#ifndef _SKY_SEQ_QUEUE_H
#define _SKY_SEQ_QUEUE_H  1

#include <iostream>
#include <cassert>
#include "sky_queue.h"

namespace sky {

/** SeqQueue
 *  基于数组的队列，不自动扩容，满后不能再入队列；初始化时可指定最大队列空间
 */
template <typename T>
class SeqQueue : public sky::Queue<T> {
public:
	SeqQueue(int sz = DEFAULT_MAX_QUEUE_SIZE);
	SeqQueue(const SeqQueue& x);
	SeqQueue& operator=(const SeqQueue& x);
	~SeqQueue() { delete[] elem; }
	
	bool isEmpty() const { return len == 0; }         // front == rear        
	bool isFull()  const { return len == maxSize;  }  // 满时front == rear,与队列空时相同
	int  length() const { return len;  }
	bool enQueue(const T& x);                        // 元素入队列
	bool deQueue(T& x);                              // 元素出队列
	bool getFront(T& x) const;                       // 返回队列头元素，但是元素不出队列
    void clear() { front = rear = 0; len = 0;}       // 队列清空，但不实际清除空间
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const SeqQueue<TT>& x);
private:
	T*  elem;
	int front, rear;    // 队头、队尾
	int len;            // 这里len非常必要，否则队列就只能装maxSize-1个元素
	int maxSize;
};

/**
 * @brief 构造函数，可指定最大队列空间
 */
template <typename T>
SeqQueue<T>::SeqQueue(int sz) : front(0), rear(0), len(0) {
	maxSize = (sz <= 0) ? DEFAULT_MAX_QUEUE_SIZE : sz;
	elem = new T[maxSize];
	assert(elem != NULL);
}

/**
 * @brief 拷贝构造函数
 */
template <typename T>
SeqQueue<T>::SeqQueue(const SeqQueue<T>& x) {
	len = x.len;
	maxSize = x.maxSize;
	front = x.front;
	rear = x.rear;
	elem = new T[maxSize];
	assert(elem != NULL);
	// 拷贝元素
	if (!x.isEmpty()) {
		int i = front;
		do {
			elem[i] = x.elem[i];
			i = (i + 1) % maxSize;
		} while (i != rear);	
	}
}

/**
 * @brief =运算符重载
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
		// 拷贝元素
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
 * @brief 元素入队列，如果队列满，返回false, 否则返回true
 */
template <typename T>
bool SeqQueue<T>::enQueue(const T& x) {
	if (isFull())
		return false;
	// 队列不满，元素入队列, rear的定义是表尾中第一个可插入空位
	elem[rear] = x;
	rear = (rear + 1) % maxSize;
	len++;
	return true;
}

/**
 * @brief 元素出队列，如果队列空，返回false, 否则返回true
 */
template <typename T>
bool SeqQueue<T>::deQueue(T& x) {
	if (isEmpty())
		return false;
	// 队列非空，元素出队列
	x = elem[front];
	front = (front + 1) % maxSize;
	len--;
	return true;
}

/**
 * @brief 获取头元素,只是元素个数不减
 */
template <typename T>
bool SeqQueue<T>::getFront(T& x) const {
	if (isEmpty())
		return false;
	// 队列非空，元素出队列
	x = elem[front];
	return true;
}

/**
 * @brief 打印所有元素
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
 * @brief 运算符<<重载
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
