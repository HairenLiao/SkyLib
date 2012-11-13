/** 
 *  @file   sky_circular_list.h 
 *  @brief  Implementation of circular linked linear list with head node
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
 *  CircularList
 *  链表：线性表的循环单链式实现，带头结点(Head Node)与尾节点(Tail Node)
 */

#ifndef _SKY_CIRCULAR_LINKED_LIST_H
#define _SKY_CIRCULAR_LINKED_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/**
 * @brief CircularLinkedListNode 循环单链表节点，采取外部定义的方式
 * 
 */
template<typename T> struct CircularLinkedListNode {
	T data;
	CircularLinkedListNode* next;
	CircularLinkedListNode(const T& item = T(), CircularLinkedListNode* ptrNext = NULL) :
		data(item), next(ptrNext) {
	}
};

/**
 * @brief CircularList 循环单链表定义 CircularList为CircularLinkedList之简称
 * 
 */
template<typename T> class CircularList : public sky::List<T> {
public:
	CircularList() :
		len(0) {
		head = tail = current = new CircularLinkedListNode<T>;
		head->next = tail;
	}
	CircularList(int sz, const T& x);
	CircularList(const CircularList<T>& x); // 拷贝构造函数
	CircularList<T>& operator=(const CircularList<T>& x); // 运算符=重载
	~CircularList() {
		removeAll();
	} // 析构函数

	int length() const {
		return len;
	} // 表长度（元素个数）
	bool isEmpty() const {
		return len == 0;
	} // 表是否为空
	bool isIncreasing() const; // 判断链表中元素是否递增
	bool getData(int i, T& x) const; // 获取i位置（第i+1个元素）的值，通过x返回
	int search(const T& x) const; // 在表中查找x，找到返回其位置，未找到返回-1
	void output() const; // 输出表内容

	bool atEnd() const {
		return current == tail;
	}
	void setBegin() {
		current = head;
	}
	void setEnd() {
		current = tail;
	}
	//void prev();
	void next();
	bool setPos(int pos);
	bool getData(T& x) const;
	bool setData(int i, const T& x); // 设置i位置元素的值为x
	bool setData(const T& x);
	bool insert(const T& x);
	bool remove(T& x);

	bool insert(int i, const T& x); // 在i位置插入一个值x
	// 此方法若提供，时间复杂度为Theta(n),故不提供
	//bool insertRear(const T& x);                       // 从末尾插入，相当于STL vector的push_back()
	bool insertFront(const T& x); // 在链表头插入
	bool remove(int i, T& x); // 删除一个元素，删除的元素通过x返回
	bool erase(int i); // 删除i位置元素，不返回元素值
	void clear(); // 清空表,但不删除头结点


	template<typename TT> friend bool operator==(const CircularList<TT>& x,
			const CircularList<TT>& y); // 由于Node定义为内部类，所以最好用成员函数而不是友元函数来重载==
	template<typename TT> friend bool operator!=(const CircularList<TT>& x,
			const CircularList<TT>& y);

private:
	CircularLinkedListNode<T>* head;
	CircularLinkedListNode<T>* tail;
	CircularLinkedListNode<T>* current;
	int len;

	/*
	 *  init() 初始化链表，长度置0,创建头结点
	 */
	void init() {
		len = 0;
		head = tail = current = new CircularLinkedListNode<T>;
		head->next = tail;
	}

	void removeAll(); // 清理所有数据结点及头结点
};

/**
 * @brief 清除所有节点
 * 
 */
template<typename T> void CircularList<T>::removeAll() {
	while (head != tail) {
		current = head;
		head = head->next;
		delete current;
	}

	delete head;
}

/**
 * @brief 构造函数，初始化为sz个相同元素x
 * 
 */
template<typename T> CircularList<T>::CircularList(int sz, const T& x) {
	init();

	while (--sz >= 0) {
		CircularLinkedListNode<T>* p = new CircularLinkedListNode<T>(x, head->next);
		head->next = p;
		len++;
	}
}

/**
 * @brief 拷贝构造函数
 * 
 */
template<typename T> CircularList<T>::CircularList(const CircularList<T>& x) {
	init();
	CircularLinkedListNode<T>* p = x.head;
	CircularLinkedListNode<T>* p1 = head;

	while (p->next != x.tail) {
		p1->next = new CircularLinkedListNode<T>(p->next->data, tail);
		if (p == x.current)
			current = p1;

		p = p->next;
		p1 = p1->next;
	}

	len = x.len;
}

/**
 * @brief 运算符=重载
 * 
 */
template<typename T> CircularList<T>& CircularList<T>::operator=(const CircularList<T>& x) {
	if (this != &x) {
		clear();
		CircularLinkedListNode<T>* p = x.head;
		CircularLinkedListNode<T>* p1 = head;

		while (p->next != x.tail) {
			p1->next = new CircularLinkedListNode<T>(p->next->data, tail);
			if (p == x.current)
			current = p1;

			p = p->next;
			p1 = p1->next;
		}

		len = x.len;
	}

	return *this;
}

/**
 * @brief 判断链表是否为排序
 * 
 */
template <typename T>
bool CircularList<T>::isIncreasing() const {
	CircularLinkedListNode<T>* p1 = head->next;
	CircularLinkedListNode<T>* p2;

	while (p1->next != tail) {
		p2 = p1->next;

		if (p1->data > p2->data)
		return false;

		p1 = p2; // p1 = p1->next;
	}

	return true;
}

/**
 * @brief 获取某一节点之值
 * 
 */
template <typename T>
bool CircularList<T>::getData(int i, T& x) const {
	if (i < 0 || i >= len)
	    return false;

	// 由于是常函数，不能使current变量变化
	CircularLinkedListNode<T>* p = head->next;
	while (i--)
	p = p->next;

	x = p->data;
	return true;
}

template <typename T>
bool CircularList<T>::setData(int i, const T& x) {
	if (i < 0 || i >= len)
	return false;

	current = head;
	while (i--)
	current = current->next;

	current->data = x;
	return true;
}

/**
 * @brief 查找值位置
 * 
 */
template <typename T>
int CircularList<T>::search(const T& x) const {
	CircularLinkedListNode<T>* p = head->next;

	int i = 0;
	while (p != tail) {
		if (p->data == x)
		return i;
		i++;
		p = p->next;
	}

	return -1;
}

/**
 * @brief 输出链表元素
 * 
 */
template <typename T>
void CircularList<T>::output() const {
	CircularLinkedListNode<T>* p = head->next;

	while (p != tail) {
		std::cout << p->data;
		if (p->next != tail)
		std::cout << " ";
		p = p->next;
	}
}

/**
 * @brief current指针移到下一位置
 * 
 */
template <typename T>
void CircularList<T>::next() {
	if (len <= 1) {
		current = head;
		return;
	}

	if (current->next == tail)
	current = head;
	current = current->next;
}

template <typename T>
bool CircularList<T>::setPos(int i) {
	if (i < 0 || i >= len)
	    return false;
	current = head;
	while (i--) {
		current = current->next;
	}
	return true;
}

template <typename T>
bool CircularList<T>::getData(T& x) const {
	if (isEmpty())
	    return false;
	CircularLinkedListNode<T>* p = current->next;
	//if (p == tail) 
	//	p = head->next;
	x = p->data;
	return true;
}

template <typename T>
bool CircularList<T>::setData(const T& x) {
	if (isEmpty())
	    return false;
	CircularLinkedListNode<T>* p = current;
	if (p->next == tail)
	p = head;
	p->next->data = x;
	return true;
}

template <typename T>
bool CircularList<T>::insert(const T& x) {
	CircularLinkedListNode<T>* p = new CircularLinkedListNode<T>(x, current->next);
	if (p) {
		current->next = p;
		current = p;
		len++;
		return true;
	}
	return false;
}

template <typename T>
bool CircularList<T>::insert(int i, const T& x) {
	if (i < 0 || i >= len)
	    return false;
	current = head;
	while (i--) {
		current = current->next;
	}
	CircularLinkedListNode<T>* p = new CircularLinkedListNode<T>(x, current->next);
	if (p) {
		current->next = p;
		current = p;
		len++;
		return true;
	}
	else {
		return false;
	}
}

template <typename T>
bool CircularList<T>::insertFront(const T& x) {
	CircularLinkedListNode<T>* p = new CircularLinkedListNode<T>(x, head->next);
	if (p) {
		head->next = p;
		current = head;
		len++;
		return true;
	}
	return false;
}

template <typename T>
bool CircularList<T>::remove(T& x) {
	if (isEmpty())
	    return false;

	CircularLinkedListNode<T>* p = current->next;
	if (p == tail) {
		p = head->next;
		current = head;
	}
	current->next = p->next;
	x = p->data;
	len--;
	delete p;
	return true;
}

template <typename T>
bool CircularList<T>::remove(int i, T& x) {
	if (i < 0 || i >= len)
	    return false;
	current = head;
	while (i--)
	current = current->next;
	CircularLinkedListNode<T>* p = current->next;
	x = p->data;
	current->next = p->next;
	len--;
	delete p;
	return true;
}

template <typename T>
bool CircularList<T>::erase(int i) {
	if (i < 0 || i >= len)
	    return false;
	current = head;
	while (i--)
	current = current->next;
	CircularLinkedListNode<T>* p = current->next;
	current->next = p->next;
	len--;
	delete p;
	return true;
}

template <typename T>
void CircularList<T>::clear() {
	while (head->next != tail) {
		current = head;
		head = head->next;
		delete current;
	}
	current = head;
}

template <typename T>
bool operator==(const CircularList<T>& x, const CircularList<T>& y) {
	if (x.length() != y.length())
	    return false;
	CircularLinkedListNode<T>* px = x.head->next;
	CircularLinkedListNode<T>* py = y.head->next;

	while (px != x.tail) {
		if (px->data != py->data)
		return false;
		px = px->next;
		py = py->next;
	}

	return true;
}

template <typename T>
bool operator!=(const CircularList<T>& x, const CircularList<T>& y) {
	return !(x == y);
}

} // namespace sky

#endif /* _SKY_CIRCULAR_LINKED_LIST_H */

