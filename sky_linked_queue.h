/** @file   sky_linked_queue.h 
 *  @brief  Link-based Queue Implentation 
 *  @author Hairen Liao(�κ��ʣ� <liaohairen@gmail.com>
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
 *  ����Ϊ���߱���ѧϰ���ݽṹ���㷨��д��ģ��STL��׼�⣬��������侫�񣬲�����ϸ�ڡ� ͬʱҲϣ�������������ѧ
 *  ���ݽṹ���㷨���������������д���൱���ע�ͺ�˵�����������������������������������ʹ�ã������߲�Ϊ�����
 *  ��ȷ�Լ���ʹ�����κε���������ʹ�ô˿������ҵʱ����Ϊ��Ϯ�� ͬʱ����Ҳ�ǳ������������ķ����͸Ľ������
 *  
 */

// ��ʽ����

#ifndef _SKY_LINKED_QUEUE_H
#define _SKY_LINKED_QUEUE_H  1

#include <iostream>
#include <cassert>
#include "sky_queue.h"

namespace sky {

/** LinkedQueue
 *  ��ʽ����
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
	bool enQueue(const T& x);                        // Ԫ�������
	bool deQueue(T& x);                              // Ԫ�س�����
	bool getFront(T& x) const;                             // ���ض���ͷԪ�أ�����Ԫ�ز�������
    void clear();
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const LinkedQueue<TT>& x);
private:
	// �뵥����Ľ�㶨����ͬ
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
 * @brief ��ն�����
 * 
 */
template <typename T>
void LinkedQueue<T>::clear() {
	while (front) {                  // ֻҪfront��Ϊ�գ������
		rear = front;                // ����rear�洢��ɾ���ڵ�ָ��    
		front = front->next;
		delete rear;	
	}
	
	rear = NULL;
	len = 0;
}

/**
 * @brief �������캯��
 */
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& x) : front(NULL), rear(NULL) {
	len = x.len;
	Node* p = x.front;
	if (p) { // �ǿ�������
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
 * @brief =���������
 */
template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator =(const LinkedQueue<T>& x) {
	if (this != &x) {
		clear();
		len = x.len;
		Node* p = x.front;
		if (p) { // �ǿ�������
			front = new Node(p->data);
			rear = front;
			while (p->next) {          
				rear->next = new Node(p->next->data);  // ע������Ӧ����p->next->data��������p->data
				p = p->next;
					rear = rear->next;
				}
			}	
	}
	
	return *this;
}

/**
 * @brief �ж��Ƿ��пռ�new�½ڵ�
 */
template <typename T>
bool LinkedQueue<T>::isFull() const {
	Node* p = new Node;
	if (p) {         // ��������½ڵ�ɹ����򷵻�false
		delete p;
		return false;
	}
	return true;
}

/**
 * @brief Ԫ������У������ӳ�������false
 * 
 */
template <typename T>
bool LinkedQueue<T>::enQueue(const T& x) {
	// ���ʹ���������䣬�����Ч�ʾͻ�ܵ�
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
 * @brief Ԫ�س����У�������пգ�����false, ���򷵻�true
 */
template <typename T>
bool LinkedQueue<T>::deQueue(T& x) {
	if (isEmpty())
		return false;
	// ���зǿգ�Ԫ�س�����
	Node* p = front;
	front = front->next;
	if (front == NULL)   // ��һ�����Ҫ��һЩ���ڽ̲���û�С���ֻ��һ���ڵ㣬deQueue��rearӦ��ΪNULL
		rear = NULL;
	x = p->data;
	delete p;
	len--;
	return true;
	
}

/**
 * @brief ��ȡͷԪ��,ֻ��Ԫ�ظ�������
 */
template <typename T>
bool LinkedQueue<T>::getFront(T& x) const {
	if (isEmpty())
		return false;
	// ���зǿգ���ȡͷԪ��
	x = front->data;
	return true;
}

/**
 * @brief ��ӡ����Ԫ��
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
 * @brief �����<<����
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
