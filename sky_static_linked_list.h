/** 
 *  @file   sky_static_linked_list.h 
 *  @brief  Implementation of static linked linear list with head node
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
 *  StaticLinkedList
 *  静态链表：用数组方式表示的链表，节点next项为数组指标，而非指针
 */

#ifndef _SKY_STATIC_LINKED_LIST_H
#define _SKY_STATIC_LINKED_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

// 预先分配的可用静态链表空间大小
const int MAX_STATIC_LINKED_LIST_SIZE = 1000;

/**
 * @brief StaticLinkedListNode 静态链表节点定义
 * 
 */
template <typename T>
struct StaticLinkedListNode {
	T data;
	int next;               // next项是int类型，而不是指针，这是静态链表与普通链表的主要区别
};

/**
 * @brief StaticLinkedList 静态链表
 * 
 */
template <typename T>
class StaticLinkedList : public sky::List<T> {
public:
	// 构造函数、析构函数
	StaticLinkedList() { init(); }
	~StaticLinkedList() {}  
	
	// 访问表
	int  length() const;
	bool isEmpty() const { return elem[0].next == -1; }
	bool getData(int i, T& x) const;
	int  search(const T& x) const;
	
	// 更改表
	bool setData(int i, const T& x); 
	bool insert(int i, const T& x); 
	bool remove(int i, T& x);
	bool erase(int i); 
	void clear();
	void output();
private:
	StaticLinkedListNode<T> elem[MAX_STATIC_LINKED_LIST_SIZE];
	int available;
	
	void init();
};

/**
 * @brief 初始化静态链表
 *        包括建立头结点和空闲链接表
 */
template <typename T>
void StaticLinkedList<T>::init() {
	elem[0].next = -1;
	available = 1;
	
	for (int i = 1; i < MAX_STATIC_LINKED_LIST_SIZE-1; i++)
		elem[i].next = i+1;
	elem[MAX_STATIC_LINKED_LIST_SIZE-1].next = -1;         	
}

/**
 * @brief 求表长度
 */
template <typename T> 
int StaticLinkedList<T>::length() const {
	int len = 0;
	int p = 0;
	while (elem[p].next != -1) {
		p = elem[p].next;
		len++;
	}
	
	return len;
}

/**
 * @brief 获取某一节点的值
 */
template <typename T> 
bool StaticLinkedList<T>::getData(int i, T& x) const {
	if (i < 0)
		return false;
	int p = elem[p].next;
	
	while (i--) {
		if (p != -1)
			p = elem[p].next;
		else
			return false;
	}
	
	if (p != -1)
		x = elem[p].data;
	else
		return false;
}

/**
 * @brief 查找某一值是否存在
 */
template <typename T>
int StaticLinkedList<T>::search(const T& x) const {
	int p = elem[0].next;
	
	int i = 0;
	while (p != -1) {
		if (elem[p].data == x)
			return i;
		i++;
		p = elem[p].next;
	}
	
	return -1;
}

/**
 * @brief 设置某一节点的值
 */
template <typename T> 
bool StaticLinkedList<T>::setData(int i, const T& x) {
	if (i < 0)
		return false;
	int p = elem[p].next;
	
	while (i--) {
		if (p != -1)
			p = elem[p].next;
		else
			return false;
	}
	
	if (p != -1)
		elem[p].data = x;
	else
		return false;
}

/**
 * @brief 插入一节点的值
 */
template <typename T> 
bool StaticLinkedList<T>::insert(int i, const T& x) {
	if (i < 0)
		return false;
	//int p = elem[p].next;
	int p = 0;        // 定位到需插入节点前一节点
	
	while (i--) {
		if (p != -1)
			p = elem[p].next;
		else
			return false;
	}
	
	if (p != -1 &&  available != -1) {
		int q = available;
		available = elem[available].next;
		elem[q].data = x;
		elem[q].next = elem[p].next;
		elem[p].next = q;
		return true;
	}
	else
		return false;
}

/**
 * @brief 删除某一节点的值
 */
template <typename T> 
bool StaticLinkedList<T>::remove(int i, T& x) {
	if (i < 0)
		return false;
	//int p = elem[p].next;
	int p = 0;        // 定位到需删除节点前一节点
	
	while (i--) {
		if (p != -1)
			p = elem[p].next;
		else
			return false;
	}
	
	if (p != -1 && elem[p].next != -1) {
		int q = elem[p].next;
		elem[p].next = elem[q].next;   
		x = elem[q].data;   
		
		// 将待删除节点加到空闲链表头部
		elem[q].next = available;
		available = q;
		return true;
	}
	else
		return false;
}

/**
 * @brief 删除某一节点的值
 */
template <typename T> 
bool StaticLinkedList<T>::erase(int i) {
	if (i < 0)
		return false;
	//int p = elem[p].next;
	int p = 0;        // 定位到需删除节点前一节点
	
	while (i--) {
		if (p != -1)
			p = elem[p].next;
		else
			return false;
	}
	
	if (p != -1 && elem[p].next != -1) {
		int q = elem[p].next;
		elem[p].next = elem[q].next;   
		//x = elem[q].data;      相对remove只删除此一句
		
		// 将待删除节点加到空闲链表头部
		elem[q].next = available;
		available = q;
		return true;
	}
	else
		return false;
}

/**
 * @brief 清除表到初始状态
 * 
 */
template <typename T>
void StaticLinkedList<T>::clear() {
	int p = 0;
	
	while (elem[p].next != -1) 
		p = elem[p].next;
	
	elem[p].next = available;  // 将自由空间与链空间连起来
	available = elem[0].next;  // 重置available变量
	elem[0].next = -1;         // 清空表
}

/**
 * @brief 输出表内容
 */
template <typename T>
void StaticLinkedList<T>::output() {
	int p = elem[0].next;
	
	while (p != -1) {
		std::cout << elem[p].data;
		if (elem[p].next != -1)
			std::cout << " ";
		p = elem[p].next;
	}
}



} // namespace sky

#endif  /* _SKY_STATIC_LINKED_LIST_H */


	
