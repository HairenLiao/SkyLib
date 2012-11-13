/** 
 *  @file   sky_linked_list.h 
 *  @brief  Implementation of linked linear list with head node
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
 *  LinkedList
 *  链表：线性表的链式实现，带头结点(Head Node)
 */

#ifndef _SKY_LINKED_LIST_H
#define _SKY_LINKED_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/* 
 *  LinkedList定义, 本定义通过SeqList修改得到，列出两种实现的异同
 *  
 */

template<typename T> class LinkedList : public sky::List<T> {
public:
	// LinkedList() : len(0), head(NULL) {} 错误！这样头结点没有建立！
	LinkedList() :
		len(0) {
		head = new Node;
	}
	LinkedList(int sz, const T& x);
	//SeqList() : len(0), maxSize(0), data(NULL) {};       // 默认构造函数
	//SeqList(int sz);                                     // 指定表长度
	//SeqList(int sz, const T& x);                         // 初始化表长度，每一元素赋值x

	LinkedList(const LinkedList<T>& x); // 拷贝构造函数
	LinkedList<T>& operator=(const LinkedList<T>& x); // 运算符=重载
	~LinkedList() {
		removeAll();
	} // 析构函数
	//~SeqList() { delete[] data; }                       

	int length() const {
		return len;
	} // 表长度（元素个数）
	// int  capacity() const { return maxSize; }         获取容量方法不再需要
	bool isEmpty() const {
		return len == 0;
	} // 表是否为空
	bool isIncreasing() const; // 判断链表中元素是否递增

	//bool isFull() const { return len == maxSize; }     判定分配的空间是否装满的方法也不再需要
	bool getData(int i, T& x) const; // 获取i位置（第i+1个元素）的值，通过x返回
	int search(const T& x) const; // 在表中查找x，找到返回其位置，未找到返回-1
	void output() const; // 输出表内容

	bool setData(int i, const T& x); // 设置i位置元素的值为x
	bool insert(int i, const T& x); // 在i位置插入一个值x
	bool insertRear(const T& x); // 从末尾插入，相当于STL vector的push_back()
	bool insertFront(const T& x); // 在链表头插入
	bool remove(int i, T& x); // 删除一个元素，删除的元素通过x返回
	bool erase(int i); // 删除i位置元素，不返回元素值
	void clear(); // 清空表,但不删除头结点
	void reverse(); // 链表反向

	bool operator==(const LinkedList<T>& x) const; // 由于Node定义为内部类，所以最好用成员函数而不是友元函数来重载==
	bool operator!=(const LinkedList<T>& x) const;
	//frined bool operator==(const LinkedList<T>& x, const LinkedList<T>& y);
	//frined bool operator!=(const LinkedList<T>& x, const LinkedList<T>& y);
	template<typename TT> friend std::ostream& operator<<(std::ostream& os,
			const LinkedList<TT>& x);

	// 以下两方法对于链表不需要
	// bool reserve(int newCapacity);                    
	// bool resize(int newSize);                         
	// T& operator[](int i);                                // 获取i位置元素引用
	// const T& operator[](int i) const;                    // 常函数版获取i位置元素引用

private:
	/*
	 *  有很多种定义Node类的方法，比如在外部定义； 定义成私有嵌套类的方式使得这一结构对外不可见，即隐藏其实现
	 */
	struct Node {
		T data;
		Node* next;
		Node(const T& item = T(), Node* ptrNext = NULL) :
			data(item), next(ptrNext) {
		}
		// 以下两个构造函数可以用上面一个代替
		// Node(const T& item, Node* ptrNext = NULL) : data(item), next(ptrNext) {}
		// Node(Node* ptrNext = NULL) : next(ptrNext) {}
	};

	// T* data;  顺序表中的数组指针被头结点所代替
	Node* head;

	// int maxSize;  顺序表中的maxSize不再需要，因为链表基本不再有容量的概念                                       
	int len; // 表长度
	//bool expandCapacity();                             // 扩容函数也不再需要 

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
 *  removeAll()私有方法，清除所有结点及头结点
 */
template<typename T> void LinkedList<T>::removeAll() {
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
 * @brief 构造函数，N个相同值组成的链表
 */
template<typename T> LinkedList<T>::LinkedList(int sz, const T& x) {
	init();
	if (sz > 0) {
		len = sz;

		// 从头部插入sz次新节点
		while (sz--) {
			Node* newNode = new Node(x, head->next);
			head->next = newNode;
		}
	}
}

/*
 *   拷贝构造函数
 *   这里的实现最重要是不要让两个链表都指向同样的数据，否则一个表的操作会影响另外一个表
 */
template<typename T> LinkedList<T>::LinkedList(const LinkedList<T>& x) {
	init();
	Node* p1 = x.head;
	Node* p2 = head;

	while (p1->next) { // 等价于while (p1->next != NULL)
		p2->next = new Node(p1->next->data);
		p1 = p1->next;
		p2 = p2->next;
	}
	// 以下实现错误！tmpNode1,tmpNode2都是结点指针，而不是结点！命名之重要！
	/*
	 Node* tmpNode1 = x.head;
	 Node* tmpNode2 = head;
	 while (tmpNode1.next != NULL) {
	 tmpNode2.next = new Node(tmpNode1.next.data);
	 tmpNode1 = tmpNode1.next;
	 tmpNode2 = tmpNode2.next;
	 }
	 */
	len = x.len;
}

/**
 *  @brief =运算符重载
 */
template<typename T> LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x) {
	if (this != &x) { // 若不检查是否自赋值，则clear()将所有数据都清除了！
		clear();
		Node* p1 = x.head;
		Node* p2 = head;

		while (p1->next) { // 等价于while (p1->next != NULL) 
			p2->next = new Node(p1->next->data);
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
bool LinkedList<T>::isIncreasing() const {
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
 */
template <typename T>
bool LinkedList<T>::getData(int i, T& x) const {
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
 */
template <typename T>
int LinkedList<T>::search(const T& x) const {
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
 *  
 */
template <typename T>
void LinkedList<T>::output() const {
	Node* p = head;
	while (p->next) {
		std::cout << p->next->data;
		if (p->next->next)
		std::cout << " ";
		p = p->next;
	}
}

/*
 *  setData(i, x)设置第i个节点的值为x
 *  注意与getData(i, x)方法的实现只有一句不同
 */
template <typename T>
bool LinkedList<T>::setData(int i, const T& x) {
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
 */
template <typename T>
bool LinkedList<T>::insert(int i, const T& x) {
	// 如果位置参数i不符合要求，直接返回false
	if (i < 0 || i >= len)
	return false;

	// 到这里说明i位置正确
	Node* p = head;

	// 数到i的位置，此循环运行完，p指向要插入的结点前一位置
	while (i--) {
		p = p->next;
	}

	Node* newNode = new Node(x, p->next);
	p->next = newNode;
	len++;
	return true;
}

/**
 *  @brief   在链表末尾插入新节点
 *  @param x 要插入的节点值
 *  @return  如果没有空间插入返回false,正确插入返回true
 * 
 *  由于本链表的实现没有定义末尾节点，所以此方法的时间效率是Theta(n)，效率较低
 */
template <typename T>
bool LinkedList<T>::insertRear(const T& x) {
	Node* p = head;

	// 循环到链表末尾
	while (p->next) {
		p = p->next;
	}

	// 生成新节点
	Node* newNode = new Node(x);

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
bool LinkedList<T>::insertFront(const T& x) {
	// 生成新节点
	Node* newNode = new Node(x, head->next);

	if (newNode) {
		head->next = newNode;
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
bool LinkedList<T>::remove(int i, T& x) {
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
bool LinkedList<T>::erase(int i) {
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

	delete nodeToErase; // 释放删除节点的空间
	len--;
	return true;
}

/**
 * @brief 清空表，但不删除头结点
 * 与removeAll()私有方法的不同时它不删除头节点，表长度置0
 *  
 */
template <typename T>
void LinkedList<T>::clear() {
	Node* p;

	while (head->next) { // 等价于while (head->next != NULL)
		p = head->next;
		head = head->next;
		delete p;
	}

	len = 0;
}

/**
 * @brief 链表反向,很有意思的练习
 *  
 */
template <typename T>
void LinkedList<T>::reverse() {

	Node* p1 = NULL; // 先将p1置NULL，可以省略许多代码
	Node* p2 = head->next; // p2指向第1个节点
	Node* p3;

	while (p2) {
		p3 = p2->next; // 存储下一节点
		p2->next = p1; // 本节点指针指向前驱节点，第1个节点指向NULL
		p1 = p2;
		p2 = p3;
	}

	head->next = p1;

	/* // 若len<=1, 则反不反向没有区别
	 if (len > 1) {
	 Node* p1 = head->next;
	 Node* p2 = p1->next;
	 Node* p3;
	 p1->next = NULL;         // 第一个节点的指针置0
	 while (p2) {
	 p3 = p2->next;
	 p2->next = p1;
	 p1 = p2;
	 p2 = p3;
	 }
	 
	 head->next = p1;        // 将头指针指向最后一个节点	
	 }
	 */
}

/**
 * @brief ==运算符重载，判断两个线性表是否相等
 */
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& x) const {
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
 */
template <typename T>
bool LinkedList<T>::operator!=(const LinkedList<T>& x) const {
	return !(this == x);
}

/**
 * @brief 重载运算符<<，使得可以方便地输出整个线性表
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& x) {
	out << "(";
	//x.output();  使用output()都输出到了std::cout!
	typename LinkedList<T>::Node* p = x.head;
	while (p->next) {
		out << p->next->data;
		if (p->next->next)
		out << " ";
		p = p->next;
	}
	out << ")";
	return out;
}

} // namespace sky 

#endif /* _SKY_LINKED_LIST_H */
