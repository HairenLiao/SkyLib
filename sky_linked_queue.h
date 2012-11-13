/** @file   sky_linked_queue.h 
 *  @brief  Link-based Queue Implentation 
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

// 链式队列

#ifndef _SKY_LINKED_QUEUE_H
#define _SKY_LINKED_QUEUE_H  1

#include <iostream>
#include <cassert>
#include "sky_queue.h"

namespace sky {

/** LinkedQueue
 *  链式队列
 */
template <typename T>
class LinkedQueue : public sky::Queue<T> {
public:
	LinkedQueue(int sz = DEFAULT_MAX_QUEUE_SIZE) : front(NULL), rear(NULL), len(0) {}
	LinkedQueue(const LinkedQueue& x);
	LinkedQueue& operator=(const LinkedQueue& x);
	~LinkedQueue() { clear(); }
	
	bool isEmpty() const { return len == 0; }         // front == rear  = NULL      
	bool isFull()  const;
	int  length() const { return len;  }
	bool enQueue(const T& x);                        // 元素入队列
	bool deQueue(T& x);                              // 元素出队列
	bool getFront(T& x) const;                             // 返回队列头元素，但是元素不出队列
    void clear();
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const LinkedQueue<TT>& x);
private:
	// 与单链表的结点定义相同
	struct Node {
		T data;
		Node* next;
		Node(const T& item = T(), Node* ptrNext = NULL) : data(item), next(ptrNext) {}
	};
	
	Node* front;
	Node* rear;
	int len;            
};

/**
 * @brief 清空队列链
 * 
 */
template <typename T>
void LinkedQueue<T>::clear() {
	while (front) {                  // 只要front不为空，就清除
		rear = front;                // 借用rear存储待删除节点指针    
		front = front->next;
		delete rear;	
	}
	
	rear = NULL;
	len = 0;
}

/**
 * @brief 拷贝构造函数
 */
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& x) : front(NULL), rear(NULL) {
	len = x.len;
	Node* p = x.front;
	if (p) { // 非空链队列
		front = new Node(p->data);
		rear = front;
		while (p->next) {           
			rear->next = new Node(p->data);
			p = p->next;
			rear = rear->next;
		}
	}
}

/**
 * @brief =运算符重载
 */
template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator =(const LinkedQueue<T>& x) {
	if (this != &x) {
		clear();
		len = x.len;
		Node* p = x.front;
		if (p) { // 非空链队列
			front = new Node(p->data);
			rear = front;
			while (p->next) {          
				rear->next = new Node(p->next->data);  // 注意这里应该是p->next->data，而不是p->data
				p = p->next;
					rear = rear->next;
				}
			}	
	}
	
	return *this;
}

/**
 * @brief 判定是否有空间new新节点
 */
template <typename T>
bool LinkedQueue<T>::isFull() const {
	Node* p = new Node;
	if (p) {         // 如果生成新节点成功，则返回false
		delete p;
		return false;
	}
	return true;
}

/**
 * @brief 元素入队列，如果入队出错，返回false
 * 
 */
template <typename T>
bool LinkedQueue<T>::enQueue(const T& x) {
	// 如果使用以下两句，则入队效率就会很低
	//if (isFull())
	//	return false;
	if (isEmpty()) {
		front = rear = new Node(x);
		if (front == NULL)
			return false;
		
	}
	else {
		rear->next = new Node(x);
		if (rear->next == NULL)
			return false;
		rear = rear->next;
	}
	
	len++;
	return true;
}

/**
 * @brief 元素出队列，如果队列空，返回false, 否则返回true
 */
template <typename T>
bool LinkedQueue<T>::deQueue(T& x) {
	if (isEmpty())
		return false;
	// 队列非空，元素出队列
	Node* p = front;
	front = front->next;
	if (front == NULL)   // 这一句很重要！一些国内教材里没有。若只有一个节点，deQueue后rear应改为NULL
		rear = NULL;
	x = p->data;
	delete p;
	len--;
	return true;
	
}

/**
 * @brief 获取头元素,只是元素个数不减
 */
template <typename T>
bool LinkedQueue<T>::getFront(T& x) const {
	if (isEmpty())
		return false;
	// 队列非空，获取头元素
	x = front->data;
	return true;
}

/**
 * @brief 打印所有元素
 */
template <typename T>
void LinkedQueue<T>::output() const {
	std::cout << "[front--> ";
	Node* p = front;
	
	while (p) {
		std::cout << p->data << " ";
		p = p->next;
	}
		
	std::cout << "<--rear]" << std::endl;
}

/**
 * @brief 运算符<<重载
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const LinkedQueue<T>& x) {
	os << "[front--> ";
	typename LinkedQueue<T>::Node* p = x.front;
	
	while (p) {
	    os << p->data << " ";
		p = p->next;
	}
			
	os << "<--rear]";	
}

}  // namespace sky 

#endif /* _SKY_LINKED_QUEUE_H */
