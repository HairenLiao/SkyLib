/** @file   sky_linked_stack.h 
 *  @brief  Array-based Stack Implentation 
 *  @author Hairen Liao(廖海仁） <liaohairen@gmail.com>
 *  
 *  Copyleft (c) 2010
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

// 顺序栈

#ifndef _SKY_LINKED_STACK_H
#define _SKY_LINKED_STACK_H  1

#include <iostream>
#include <cassert>
#include "sky_stack.h"

namespace sky {

/** LinkedStack 
 *  链栈
 */
template <typename T>
class LinkedStack : public sky::Stack<T> {
public:
	LinkedStack(int sz = DEFAULT_MAX_STACK_SIZE) : top(NULL), len(0) {} // 构造函数，输入参数无效
	LinkedStack(const LinkedStack& x);
	LinkedStack& operator=(const LinkedStack& x);
	~LinkedStack() { clear(); }
	
	bool isEmpty() const { return top == NULL;  }               
	bool isFull()  const;
	int  length() const { return len;  }
	bool push(const T& x);                              // 元素入栈
	bool pop(T& x);                                     // 元素出栈
	bool getTop(T& x) const;                            // 返回栈顶元素，但是不将元素从栈中
    void clear();    
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const LinkedStack<TT>& x);
private:
	// 链式栈的底层数据结构与链表是相同的，只是用top代替head节点，对于栈，不需要头节点，因为都是在表头操作
	struct Node {
		T data;
		Node* next;
		Node(const T& item = T(), Node* ptrNext = NULL) : data(item), next(ptrNext) {}
	} ;
	
	Node*  top;
	int len;
}; 

/**
 * @brief 清空栈
 */
template <typename T> 
void LinkedStack<T>::clear() {
	while (top) {
		Node* p = top;
		top = top->next;
		delete p;
	}
	len = 0;
}

/**
 * @brief 是否满, 还可以new Node则不满，否则满
 */
template <typename T> 
bool LinkedStack<T>::isFull() const {
	Node* p = new Node;
	if (p) {
		delete p;
		return false;
	}
	return true;
}


/**
 * @brief 拷贝构造函数
 */
template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& x) : top(NULL) {
	if (x.top) {
		top = new Node(x.top->data);
		Node* p = x.top->next;
		Node* p1 = top;
		while (p) {
			p1->next = new Node(p->data);
			p = p->next;
			p1 = p1->next;
		}
	}
	
	len = x.len;
}

/**
 * @brief =运算符重载
 */
template <typename T>
LinkedStack<T>& LinkedStack<T>::operator =(const LinkedStack<T>& x) {
	if (this != &x) {
		clear();
		len = x.len;
		if (x.top) {
			top = new Node(x.top->data);
			Node* p = x.top->next;
			Node* p1 = top;
			while (p) {
				p1->next = new Node(p->data);
				p = p->next;
				p1 = p1->next;
			}
		}
	}
	return *this;
}
/**
 * @brief 元素入栈, 一般用void push(x)的定义，这里使用bool类型返回值以便于在new节点未成功时时返回false
 * 
 */
template <typename T>
bool LinkedStack<T>::push(const T& x) {
	Node* p = new Node(x, top);
	if (p) {                 
		top = p;
		len++;
		return true;
	}
	return false;   
	
}

/**
 * @brief 元素出栈，如果栈空，返回false，否则元素出栈，返回true
 *        一般库的设计是 T pop(), 但是对于sky库这种不提供出错处理的库，这里难以处理栈空的情况
 * 
 */
template <typename T>
bool LinkedStack<T>::pop(T& x) {
	if (isEmpty())
		return false;
	else {
		Node* p = top;
		top = top->next;
		len--;
		x = p->data;
		delete p;
		return true;
	}
}

/**
 * @brief 获取栈顶元素，除了top不减1外与pop完全相同
 */
template <typename T>
bool LinkedStack<T>::getTop(T& x) const {
	if (isEmpty())
		return false;
	else {
		x = top->data;  
		return true;
	}
}

/**
 * @brief output()输出栈内容，并标识栈顶
 */
template <typename T>
void LinkedStack<T>::output() const {
	std::cout << "[top-->";
	Node* p = top;
	while (p) {
		std::cout << p->data << " ";
		p = p->next;
	}
		
	std::cout << "]" << std::endl;
}

/**
 * <<输出重载,不标识栈顶
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const LinkedStack<T>& x) {
	//x.output();
	
	os << "[top-->";
	// 此处必须使用typename, 不然Node不会被解析为一个类型!
	typename LinkedStack<T>::Node* p = x.top;
	while (p) {
		os << p->data << " ";
		p = p->next;
	}
			
	os << "]" ;	
	
}

}  // namespace sky 

#endif /* _SKY_LINKED_STACK_H */
