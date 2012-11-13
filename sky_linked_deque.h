/** @file   sky_linked_deque.h 
 *  @brief  Link-based Deque Implentation 
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

// 链式双端队列,利用循环双向链表实现,实现逻辑非常简单!

#ifndef _SKY_LINKED_DEQUE_H
#define _SKY_LINKED_DEQUE_H  1

#include <iostream>
#include <cassert>
#include "sky_deque.h"

namespace sky {

/** LinkedDeque
 *  链式双端队列
 */
template <typename T>
class LinkedDeque : public sky::Deque<T> {
public:
	LinkedDeque(int sz = DEFAULT_MAX_DEQUE_SIZE) { init(); }
	LinkedDeque(const LinkedDeque& x);
	LinkedDeque& operator=(const LinkedDeque& x);
	~LinkedDeque() { clear(); delete head;}
	
	bool isEmpty() const { return len == 0; }             
	bool isFull()  const;
	int  length() const { return len;  }
	bool pushFront(const T& x);    
	bool pushRear(const T& x);
	bool popFront(T& x);
	bool popRear(T& x);                             
	bool getFront(T& x) const;                          
	bool getRear(T& x) const;             
    void clear();
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const LinkedDeque<TT>& x);
private:
	// 与双向链表的结点定义相同
	struct Node {
		 T data;
		 /* 使用prev、next比使用left、right命名前驱节点、 后继节点更好 */
		 Node* prev;
		 Node* next;
		 Node(const T& item = T(), Node* p = NULL, Node* n = NULL) : data(item), prev(p), next(n) {}
	};
	
	//Node* front;
	//Node* rear;
	Node* head;         
	int len;  
	void init() {
		len = 0;
		head = new Node;
		head->next = head;
		head->prev = head;
	}
};

/**
 * @brief 清空队列链,头节点不删除
 * 
 */
template <typename T>
void LinkedDeque<T>::clear() {
	Node* p = head->next;
	while (p != head) {                  // 只要p不为头节点，就清除
		Node* tmp = p;
		p = p->next;
		delete tmp;
	}
	
	head->next = head;
	head->prev = head;
	len = 0; 
}

/**
 * @brief 拷贝构造函数
 */
template <typename T>
LinkedDeque<T>::LinkedDeque(const LinkedDeque<T>& x) {
	init();
	Node* p1 = x.head->next;
	Node* p2 = head;    
		
	while (p1 != x.head ) { 
		// 这里新节点的prev指针需要指向p2, next指针为p2->next
		Node* newNode = new Node(p1->data, p2, p2->next);
		p2->next = newNode;
		newNode->next->prev = newNode;
		p1 = p1->next;
		p2 = p2->next;
	}
		
	len = x.len;
}

/**
 * @brief =运算符重载
 */
template <typename T>
LinkedDeque<T>& LinkedDeque<T>::operator =(const LinkedDeque<T>& x) {
	if (this != &x) {
		clear();
		Node* p1 = x.head->next;
		Node* p2 = head;
				
		while (p1 != x.head) { 
			Node* newNode = new Node(p1->data, p2, p2->next);
			p2->next = newNode;
			newNode->next->prev = newNode;
			p1 = p1->next;
			p2 = p2->next;	
		}
				
		len = x.len;
	}
	
	return *this;
}

/**
 * @brief 判定是否有空间new新节点
 */
template <typename T>
bool LinkedDeque<T>::isFull() const {
	Node* p = new Node;
	if (p) {         // 如果生成新节点成功，则返回false
		delete p;
		return false;
	}
	return true;
}

/**
 * @brief 在双端队列的头插入,若插入不成功，返回false，否则返回true
 * 
 */
template <typename T>
bool LinkedDeque<T>::pushFront(const T& x) {
	Node* newNode = new Node(x, head, head->next);
	if (!newNode)
		return false;
	head->next = newNode;
	newNode->next->prev = newNode;
	len++;
	return true;
}

/**
 * @brief 在双端队列的尾插入,若插入不成功，返回false，否则返回true
 * 
 */
template <typename T>
bool LinkedDeque<T>::pushRear(const T& x) {
	Node* newNode = new Node(x, head->prev, head);  // 与pushFront相比，这一句不同
	if (!newNode)
		return false;
	
	// 以下指针的改变也不同
	head->prev = newNode;
	newNode->prev->next = newNode;
	len++;
	return true;
}

/**
 * @brief 元素出队列头，如果队列空，返回false, 否则返回true
 */
template <typename T>
bool LinkedDeque<T>::popFront(T& x) {
	if (isEmpty())
		return false;
	// 队列非空，元素出队列
	Node* p = head->next;
	x = p->data;
	head->next = p->next;
	p->next->prev = head;
	delete p;
	len--;
	return true;	
}

/**
 * @brief 元素出队列尾，如果队列空，返回false, 否则返回true
 */
template <typename T>
bool LinkedDeque<T>::popRear(T& x) {
	if (isEmpty())
		return false;
	// 队列非空，元素出队列
	Node* p = head->prev;
	x = p->data;
	p->prev->next = head;
	head->prev = p->prev;
	delete p;
	len--;
	return true;	
}

/**
 * @brief 获取头元素,只是元素个数不减
 */
template <typename T>
bool LinkedDeque<T>::getFront(T& x) const {
	if (isEmpty())
		return false;
	// 队列非空，获取头元素
	x = head->next->data;
	return true;
}

/**
 * @brief 获取尾元素,只是元素个数不减
 */
template <typename T>
bool LinkedDeque<T>::getRear(T& x) const {
	if (isEmpty())
		return false;
	// 队列非空，获取头元素
	x = head->prev->data;
	return true;
}

/**
 * @brief 打印所有元素
 */
template <typename T>
void LinkedDeque<T>::output() const {
	std::cout << "[front--> ";
	Node* p = head->next;
	
	while (p != head) {
		std::cout << p->data << " ";
		p = p->next;
	}
		
	std::cout << "<--rear]" << std::endl;
}

/**
 * @brief 运算符<<重载
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const LinkedDeque<T>& x) {
	os << "[front--> ";
	typename LinkedDeque<T>::Node* p = x.head->next;
	
	while (p != x.head) {
	    os << p->data << " ";
		p = p->next;
	}
			
	os << "<--rear]";	
}

}  // namespace sky 

#endif /* _SKY_LINKED_DEQUE_H */
