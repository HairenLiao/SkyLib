/** @file   sky_seq_deque.h 
 *  @brief  Array-based Deque Implentation 
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
 *  数据结构与算法者有所帮助，因此写了相当多的注释和说明。本库属于自由软件，基本可以自由使用，但作者不为本库的
 *  正确性及其使用做任何担保，包括使用此库完成作业时被视为抄袭。 同时作者也非常乐于听到各种反馈和改进意见。
 *  
 */

// 双端队列,利用数组实现

#ifndef _SKY_SEQ_DEQUE_H
#define _SKY_SEQ_DEQUE_H 1
#include "sky_deque.h"

namespace sky {

/** SeqDeque
 *  顺序双端队列
 *  特别应注意pushFront(), popRear(), getRear()操作，这些是单端队列没有的
 */
template <typename T>
class SeqDeque : public sky::Deque<T> {
public:
	SeqDeque(int sz = DEFAULT_MAX_DEQUE_SIZE) : front(0), rear(0), len(0) {
		maxSize = (sz <= 0) ? DEFAULT_MAX_DEQUE_SIZE : sz;
		elem = new T[maxSize];
	}
	SeqDeque(const SeqDeque& x);
	SeqDeque& operator=(const SeqDeque& x);
	~SeqDeque() { delete[] elem; }
	
	bool isEmpty() const { return len == 0; }             
	bool isFull()  const { return len == maxSize; }
	int  length() const { return len;  }
	bool pushFront(const T& x);    
	bool pushRear(const T& x);
	bool popFront(T& x);
	bool popRear(T& x);                             
	bool getFront(T& x) const;                          
	bool getRear(T& x) const;             
    void clear() { front = rear = len = 0; }
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const SeqDeque<TT>& x);
private:
	T*  elem;
	int front, rear;      
	int len;  
	int maxSize;
};


/**
 * @brief 拷贝构造函数
 */
template <typename T>
SeqDeque<T>::SeqDeque(const SeqDeque<T>& x) {
	len = x.len;
	maxSize = x.maxSize;
	front = x.front;
	rear = x.rear;
	elem = new T[maxSize];
	
	int i = front;
	// 拷贝len个元素
	for (int num = 0; num < len; num++) {
		elem[i] = x.elem[i];
		i = (i + 1) % maxSize;	
	}
}

/**
 * @brief =运算符重载
 */
template <typename T>
SeqDeque<T>& SeqDeque<T>::operator =(const SeqDeque<T>& x) {
	if (this != &x) {
		delete[] elem;
		len = x.len;
		maxSize = x.maxSize;
		front = x.front;
		rear = x.rear;
		elem = new T[maxSize];
			
		int i = front;
		// 拷贝len个元素
		for (int num = 0; num < len; num++) {
			elem[i] = x.elem[i];
			i = (i + 1) % maxSize;	
		}
	}
	
	return *this;
}

/**
 * @brief 在双端队列的头插入,若队列满，返回false，否则插入元素，返回true
 * 
 */
template <typename T>
bool SeqDeque<T>::pushFront(const T& x) {
	if (isFull())
		return false;
	front = (front + maxSize - 1) % maxSize;        // 相当于循环front--
	elem[front] = x;                                // front定义是队头第一个可用元素，所以是先自减后插入，因为rear不能改变
	len++;
	return true;
}

/**
 * @brief 在双端队列的尾插入,若插入不成功，返回false，否则返回true
 * 
 */
template <typename T>
bool SeqDeque<T>::pushRear(const T& x) {
	if (isFull())
		return false;
	elem[rear] = x;                     // rear是队列第一个可插入的空位
	rear = (rear + 1) % maxSize;        // 相当于循环rear++
	len++;
	return true;
}

/**
 * @brief 元素出队列头，如果队列空，返回false, 否则返回true
 */
template <typename T>
bool SeqDeque<T>::popFront(T& x) {
	if (isEmpty())
		return false;
	x = elem[front];
	front = (front + 1) % maxSize;
	len--;
	return true;	
}

/**
 * @brief 元素出队列尾，如果队列空，返回false, 否则返回true
 */
template <typename T>
bool SeqDeque<T>::popRear(T& x) {
	if (isEmpty())
		return false;	
	rear = (rear + maxSize - 1) % maxSize;           // loop rear--
	x = elem[rear];
	len--;
	return true;	
}

/**
 * @brief 获取头元素,只是元素个数不减
 */
template <typename T>
bool SeqDeque<T>::getFront(T& x) const {
	if (isEmpty())
		return false;
	x = elem[front];
	return true;
}

/**
 * @brief 获取尾元素,只是元素个数不减
 */
template <typename T>
bool SeqDeque<T>::getRear(T& x) const {
	if (isEmpty())
		return false;
	// 队列非空，获取头元素
	//x = elem[rear];  rear是空位置 , --rear才是队尾元素地址！
	x = elem[(rear + maxSize - 1) % maxSize];
	return true;
}

/**
 * @brief 打印所有元素
 */
template <typename T>
void SeqDeque<T>::output() const {
	std::cout << "[front--> ";
	
	int i = front;
	for (int num = 0; num < len; num++) {
		std::cout << elem[i] << " ";
		i = (i + 1) % maxSize;	
	}
	
	std::cout << "<--rear]" << std::endl;
}

/**
 * @brief 运算符<<重载
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const SeqDeque<T>& x) {
	os << "[front--> ";
	
	int i = x.front;
	for (int num = 0; num < x.len; num++) {
		std::cout << x.elem[i] << " ";
		i = (i + 1) % x.maxSize;	
	}
			
	os << "<--rear]";	
}

}  // namespace sky 

#endif /* _SKY_SEQ_DEQUE_H */
