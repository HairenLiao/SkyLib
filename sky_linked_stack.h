/** @file   sky_linked_stack.h 
 *  @brief  Array-based Stack Implentation 
 *  @author Hairen Liao(�κ��ʣ� <liaohairen@gmail.com>
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
 *  ����Ϊ���߱���ѧϰ���ݽṹ���㷨��д��ģ��STL��׼�⣬��������侫�񣬲�����ϸ�ڡ� ͬʱҲϣ�������������ѧ
 *  ���ݽṹ���㷨���������������д���൱���ע�ͺ�˵�����������������������������������ʹ�ã������߲�Ϊ�����
 *  ��ȷ�Լ���ʹ�����κε���������ʹ�ô˿������ҵʱ����Ϊ��Ϯ�� ͬʱ����Ҳ�ǳ������������ķ����͸Ľ������
 *  
 */

// ˳��ջ

#ifndef _SKY_LINKED_STACK_H
#define _SKY_LINKED_STACK_H  1

#include <iostream>
#include <cassert>
#include "sky_stack.h"

namespace sky {

/** LinkedStack 
 *  ��ջ
 */
template <typename T>
class LinkedStack : public sky::Stack<T> {
public:
	LinkedStack(int sz = DEFAULT_MAX_STACK_SIZE) : top(NULL), len(0) {} // ���캯�������������Ч
	LinkedStack(const LinkedStack& x);
	LinkedStack& operator=(const LinkedStack& x);
	~LinkedStack() { clear(); }
	
	bool isEmpty() const { return top == NULL;  }               
	bool isFull()  const;
	int  length() const { return len;  }
	bool push(const T& x);                              // Ԫ����ջ
	bool pop(T& x);                                     // Ԫ�س�ջ
	bool getTop(T& x) const;                            // ����ջ��Ԫ�أ����ǲ���Ԫ�ش�ջ��
    void clear();    
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const LinkedStack<TT>& x);
private:
	// ��ʽջ�ĵײ����ݽṹ����������ͬ�ģ�ֻ����top����head�ڵ㣬����ջ������Ҫͷ�ڵ㣬��Ϊ�����ڱ�ͷ����
	struct Node {
		T data;
		Node* next;
		Node(const T& item = T(), Node* ptrNext = NULL) : data(item), next(ptrNext) {}
	} ;
	
	Node*  top;
	int len;
}; 

/**
 * @brief ���ջ
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
 * @brief �Ƿ���, ������new Node������������
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
 * @brief �������캯��
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
 * @brief =���������
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
 * @brief Ԫ����ջ, һ����void push(x)�Ķ��壬����ʹ��bool���ͷ���ֵ�Ա�����new�ڵ�δ�ɹ�ʱʱ����false
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
 * @brief Ԫ�س�ջ�����ջ�գ�����false������Ԫ�س�ջ������true
 *        һ��������� T pop(), ���Ƕ���sky�����ֲ��ṩ������Ŀ⣬�������Դ���ջ�յ����
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
 * @brief ��ȡջ��Ԫ�أ�����top����1����pop��ȫ��ͬ
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
 * @brief output()���ջ���ݣ�����ʶջ��
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
 * <<�������,����ʶջ��
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const LinkedStack<T>& x) {
	//x.output();
	
	os << "[top-->";
	// �˴�����ʹ��typename, ��ȻNode���ᱻ����Ϊһ������!
	typename LinkedStack<T>::Node* p = x.top;
	while (p) {
		os << p->data << " ";
		p = p->next;
	}
			
	os << "]" ;	
	
}

}  // namespace sky 

#endif /* _SKY_LINKED_STACK_H */
