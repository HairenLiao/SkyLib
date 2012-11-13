/** 
 *  @file   sky_doubly_linked_list.h 
 *  @brief  Implementation of doubly linked linear list with head node
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
 *  DoublyLinkedList
 *  双链表实现，带头结点(Head Node)
 */

#ifndef _SKY_DOUBLY_LINKED_LIST_H
#define _SKY_DOUBLY_LINKED_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/** 
 *  DoublyLinkedList定义, 本定义通过LinkedList修改得到，列出两种实现的异同
 *  
 */

template<typename T> class DoublyLinkedList : public sky::List<T> {
public:
	DoublyLinkedList() :
		len(0) {
		head = new Node;
	}
	DoublyLinkedList(int sz, const T& x);

	DoublyLinkedList(const DoublyLinkedList<T>& x); // 拷贝构造函数
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& x); // 运算符=重载
	~DoublyLinkedList() {
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
	bool setData(int i, const T& x); // 设置i位置元素的值为x
	bool insert(int i, const T& x); // 在i位置插入一个值x  !!!
	bool insertRear(const T& x); // 从末尾插入，相当于STL vector的push_back() !!!
	bool insertFront(const T& x); // 在链表头插入 !!!
	bool remove(int i, T& x); // 删除一个元素，删除的元素通过x返回 !!!
	bool erase(int i); // 删除i位置元素，不返回元素值 !!!
	void clear(); // 清空表,但不删除头结点
	void reverse(); // 链表反向

	bool operator==(const DoublyLinkedList<T>& x) const; // 由于Node定义为内部类，所以最好用成员函数而不是友元函数来重载==
	bool operator!=(const DoublyLinkedList<T>& x) const;
	//frined bool operator==(const LinkedList<T>& x, const LinkedList<T>& y);
	//frined bool operator!=(const LinkedList<T>& x, const LinkedList<T>& y);

private:
	/**
	 *  DoublyLinkedList Node定义，相对LinkedList定义，只是Node的定义改变
	 */
	struct Node {
		T data;
		/* 使用prev、next比使用left、right命名前驱节点、 后继节点更好 */
		Node* prev;
		Node* next;
		Node(const T& item = T(), Node* p = NULL, Node* n = NULL) :
			data(item), prev(p), next(n) {
		}
	};

	Node* head;
	/* 此tail节点的引入可使得insertRear(x)方法的时间复杂度变为O(1)
	 * 但是这里的实现与STL中使用tail稍有不同：初始化时head与tail是同一节点，
	 * 而STL中tail节点初始化时与head是两个节点
	 */
	// Node* tail;
	int len; // 表长度

	/*
	 *  init() 初始化链表，长度置0,创建头结点
	 */
	void init() {
		len = 0;
		head = new Node;
	}

	void removeAll(); // 清理所有数据结点及头结点
};

/**
 * @brief 清除所有结点及头结点
 *        与LinkedList完全一样
 */
template<class T> void DoublyLinkedList<T>::removeAll() {
	// Node* p; 简单命名为p
	Node* p;

	// 注意不是head->next != NULL， 因为同时要删除头结点
	while (head) { // 等价于while (head != NULL)
		p = head;
		head = head->next;
		delete p;
	}

}

/**
 * @brief 构造函数，N个相同值组成的双链表
 * @param sz 链表元素个数
 * @param x  每个链表元素的初始化值
 */
template<typename T> DoublyLinkedList<T>::DoublyLinkedList(int sz, const T& x) {
	init();
	if (sz > 0) {
		len = sz;

		// 从头部插入sz次新节点, 每个新节点的prev初始化为head, next初始化为head->next
		while (sz--) {
			Node* newNode = new Node(x, head, head->next);
			head->next = newNode;

			// 以下语句若没有，newNode下一节点的prev指针未设置好
			if (newNode->next)
				newNode->next->prev = newNode;
		}
	}
}

/**
 * @brief 拷贝构造函数
 * @param x 另一双链表
 * 这里的实现最重要是不要让两个链表都指向同样的数据，否则一个表的操作会影响另外一个表
 */
template<typename T> DoublyLinkedList<T>::DoublyLinkedList(
		const DoublyLinkedList<T>& x) {
	init();
	Node* p1 = x.head;
	Node* p2 = head;

	while (p1->next) { // 等价于while (p1->next != NULL)
		// 这里新节点的prev指针需要指向p2, next指针为NULL
		p2->next = new Node(p1->next->data, p2);
		p1 = p1->next;
		p2 = p2->next;
	}

	len = x.len;
}

/**
 * @brief 清空表，但不删除头结点
 * 与removeAll()私有方法的不同时它不删除头节点，表长度置0
 *  
 */
template<typename T> void DoublyLinkedList<T>::clear() {
	Node* p;

	while (head->next) { // 等价于while (head->next != NULL)
		p = head->next;
		head = head->next;
		delete p;
	}

	// 这是双链表清空特别的地方，head->prev需要置NULL
	head->prev = NULL;

	len = 0;
}

/**
 *  @brief =运算符重载
 */
template<typename T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& x) {
	if (this != &x) { // 若不检查是否自赋值，则clear()将所有数据都清除了！
		clear();
		Node* p1 = x.head;
		Node* p2 = head;

		while (p1->next) { // 等价于while (p1->next != NULL) 
			p2->next = new Node(p1->next->data, p2);
			p1 = p1->next;
			p2 = p2->next;
		}

		len = x.len;
	}

	return *this;
}

/**
 * @brief 判断链表元素是否（非严格）递增，空表、只有一个元素的表均算递增 
 */
template <typename T>
bool DoublyLinkedList<T>::isIncreasing() const {
	Node* p1 = head->next;
	Node* p2;

	// 如果p1不为NULL,取p2为其后继
	if (p1) {
		while (p1->next) {
			p2 = p1->next;
			if (p1->data > p2->data) // 若在表中查到前驱元素大于后继元素，则返回false
			return false;
			else
			p1 = p2;
		}
	}

	return true;
}

/**
 *  @brief 得到第i个结点的值，记得是从0开始计数，到len-1个结点
 *  @param i 元素位置，从0开始计数
 *  @param x 第i个节点的值
 *  @return 如果i不满足要求，返回false, 正确取回返回true
 *  		与单链表相同
 */
template <typename T>
bool DoublyLinkedList<T>::getData(int i, T& x) const {
	// 如果位置参数i不符合要求，直接返回false
	if (i < 0 || i >= len)
	return false;

	// 到这里说明i位置正确
	Node* p = head;

	// 由于i用完后不再有用，所以直接用i--,不需要用一个额外的变量j
	// 数到i的位置，此循环运行完，p指向要取的结点前一位置
	while (i--) {
		p = p->next;
	}

	x = p->next->data;
	return true;
}

/**
 * @brief 在表中查找x,找到返回其位置，否则返回-1
 * @param x 待查找的元素值
 * @return 找到返回其位置，否则返回-1
 *         与单链表相同
 */
template <typename T>
int DoublyLinkedList<T>::search(const T& x) const {
	int i = 0;
	Node* p = head;
	while (p->next) { // 等价于 while (p->next != NULL）
		if (p->next->data == x)
		return i;
		i++;
		p = p->next;
	}

	return -1;
}

/**
 *  @brief 输出表元素，以空格分隔
 *         与单链表相同  
 */
template <typename T>
void DoublyLinkedList<T>::output() const {
	Node* p = head;
	while (p->next) {
		std::cout << p->next->data;
		if (p->next->next)
		std::cout << " ";
		p = p->next;
	}
}

/**
 * @brief 设置第i个节点的值为x
 * @param i 节点i,从0算起
 * @param x  设置的值
 * @return 如果设置成功，返回true, 如果i值越界，返回false
 *  注意与getData(i, x)方法的实现只有一句不同
 *  与单链表相同，因为此操作不需改变prev与next指针
 */
template <typename T>
bool DoublyLinkedList<T>::setData(int i, const T& x) {
	// 如果位置参数i不符合要求，直接返回false
	if (i < 0 || i >= len)
	return false;

	// 到这里说明i位置正确
	Node* p = head;

	// 由于i用完后不再有用，所以直接用i--,不需要用一个额外的变量j
	// 数到i的位置，此循环运行完，p指向要改变的结点前一位置
	while (i--) {
		p = p->next;
	}

	p->next->data = x; // 相比getData(i, x)方法的实现，只此一句不同！
	return true;
}

/** 
 *  @brief   在一给定位置插入值
 *  @param i 插入的位置，从0开始
 *  @param x 要插入的值
 *  @return  正确插入返回true，否则返回false
 *           注意此方法实现与单链表的差别
 */
template <typename T>
bool DoublyLinkedList<T>::insert(int i, const T& x) {
	// 如果位置参数i不符合要求，直接返回false
	if (i < 0 || i >= len)
	return false;

	// 到这里说明i位置正确
	Node* p = head;

	// 数到i的位置，此循环运行完，p指向要插入的结点前一位置
	while (i--) {
		p = p->next;
	}

	// p1指向要插入的结点的后一位置，有可能为NULL, 不需要p1
	// Node* p1 = p->next;

	// 新节点prev设为p, next设为p->next
	Node* newNode = new Node(x, p, p->next);
	p->next = newNode;

	// 如果p1不为NULL,将其prev指针置为newNode
	// p1可以用newNode->next代替
	// if (p1) 
	if (newNode->next)
	newNode->next->prev = newNode;

	len++;
	return true;
}

/**
 *  @brief   在链表末尾插入新节点
 *  @param x 要插入的节点值
 *  @return  如果没有空间插入返回false,正确插入返回true
 * 
 *  由于本链表的实现没有定义末尾节点，所以此方法的时间效率是Theta(n)，效率较低 
 *  可以通过增加一个tail节点使得此操作的时间复杂度变为O(1)
 */
template <typename T>
bool DoublyLinkedList<T>::insertRear(const T& x) {
	Node* p = head;

	// 循环到链表末尾
	while (p->next) {
		p = p->next;
	}

	// 生成新节点, prev设为p
	Node* newNode = new Node(x, p);
	//Node*  newNode = new Node(x); 与LinkedList只有此句不同

	// 如果生成成功，将原链表的末节点指向此新节点
	if (newNode) {
		p->next = newNode;
		len++;
		return true;
	}

	// 如果未生成成功，返回false
	return false;
}

/**
 *  @brief   在链表头插入新节点
 *  @param x 要插入的节点值
 *  @return  如果没有空间插入返回false,正确插入返回true
 * 
 *  本方法的时间效率为O(1),效率高
 */
template <typename T>
bool DoublyLinkedList<T>::insertFront(const T& x) {
	// 生成新节点, prev设为head, next设为head->next
	//Node* newNode = new Node(x, head->next);
	Node* newNode = new Node(x, head, head->next);

	if (newNode) {
		head->next = newNode;
		if (newNode->next)
		newNode->next->prev = newNode;
		len++;
		return true;
	}

	return false;
}

/**
 * @brief   删除某一位置的结点,删除元素通过引用返回
 * @param i 插入的位置，从0开始
 * @param x 删除的值通过引用返回
 * @return  正确删除返回true，否则返回false
 * 
 */
template <typename T>
bool DoublyLinkedList<T>::remove(int i, T& x) {
	// 如果位置参数i不符合要求，直接返回false
	if (i < 0 || i >= len)
	return false;

	Node* p = head;

	// 数到i的位置，此循环运行完，p指向要删除的结点前一位置
	while (i--) {
		p = p->next;
	}

	Node* nodeToRemove = p->next;
	p->next = nodeToRemove->next;

	if (nodeToRemove->next)
	nodeToRemove->next->prev = p;

	x = nodeToRemove->data;
	delete nodeToRemove;
	len--;
	return true;
}

/**
 * @brief   删除某一位置的结点
 * @param i 插入的位置，从0开始
 * @param x 删除的值通过引用返回
 * @return  正确删除返回true，否则返回false
 * 
 */
template <typename T>
bool DoublyLinkedList<T>::erase(int i) {
	// 如果位置参数i不符合要求，直接返回false
	if (i < 0 || i >= len)
	return false;

	Node* p = head;

	// 数到i的位置，此循环运行完，p指向要删除的结点前一位置
	while (i--) {
		p = p->next;
	}

	Node* nodeToErase = p->next;
	p->next = p->next->next;

	if (nodeToErase->next)
	nodeToErase->next->prev = p;

	delete nodeToErase; // 释放删除节点的空间
	len--;
	return true;
}

/**
 * @brief 链表反向
 *  
 */
template <typename T>
void DoublyLinkedList<T>::reverse() {
	Node* p1 = NULL;
	Node* p2 = head->next;
	Node* p3;

	while (p2) {
		p3 = p2->next;
		p2->next = p1;
		p2->prev = p3;
		p1 = p2;
		p2 = p3;
	}

	// 将head指向末节点
	head->next = p1;
	p1->prev = head;
}

/**
 * @brief ==运算符重载，判断两个线性表是否相等
 *        与单链表实现代码完全相同
 */
template <typename T>
bool DoublyLinkedList<T>::operator==(const DoublyLinkedList<T>& x) const {
	if (len == x.len) {
		Node* p1 = head;
		Node* p2 = x.head;
		while (p1->next) {
			if (p1->next->data != p2->next->data)
			return false;
			p1 = p1->next;
			p2 = p2->next;
		}
		return true; // 如果长度相等，而且每个元素又相同，则两顺序表相等
	}
	else {
		return false;
	}
}

/**
 * @brief !=运算符重载，判断两个线性表是否相等
 *        与单链表实现完全相同
 */
template <typename T>
bool DoublyLinkedList<T>::operator!=(const DoublyLinkedList<T>& x) const {
	return !(this == x);
}

/**
 * @brief 重载运算符<<，使得可以方便地输出整个线性表
 *        与单链表实现完全相同
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<T>& x) {
	out << "(";
	x.output();
	out << ")";
	return out;
}

} // namespace sky 

#endif /* _SKY_DOUBLY_LINKED_LIST_H */
