/** @file   sky_linked_deque.h 
 *  @brief  Link-based Deque Implentation 
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

// ��ʽ˫�˶���,����ѭ��˫������ʵ��,ʵ���߼��ǳ���!

#ifndef _SKY_LINKED_DEQUE_H
#define _SKY_LINKED_DEQUE_H  1

#include <iostream>
#include <cassert>
#include "sky_deque.h"

namespace sky {

/** LinkedDeque
 *  ��ʽ˫�˶���
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
	// ��˫������Ľ�㶨����ͬ
	struct Node {
		 T data;
		 /* ʹ��prev��next��ʹ��left��right����ǰ���ڵ㡢 ��̽ڵ���� */
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
 * @brief ��ն�����,ͷ�ڵ㲻ɾ��
 * 
 */
template <typename T>
void LinkedDeque<T>::clear() {
	Node* p = head->next;
	while (p != head) {                  // ֻҪp��Ϊͷ�ڵ㣬�����
		Node* tmp = p;
		p = p->next;
		delete tmp;
	}
	
	head->next = head;
	head->prev = head;
	len = 0; 
}

/**
 * @brief �������캯��
 */
template <typename T>
LinkedDeque<T>::LinkedDeque(const LinkedDeque<T>& x) {
	init();
	Node* p1 = x.head->next;
	Node* p2 = head;    
		
	while (p1 != x.head ) { 
		// �����½ڵ��prevָ����Ҫָ��p2, nextָ��Ϊp2->next
		Node* newNode = new Node(p1->data, p2, p2->next);
		p2->next = newNode;
		newNode->next->prev = newNode;
		p1 = p1->next;
		p2 = p2->next;
	}
		
	len = x.len;
}

/**
 * @brief =���������
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
 * @brief �ж��Ƿ��пռ�new�½ڵ�
 */
template <typename T>
bool LinkedDeque<T>::isFull() const {
	Node* p = new Node;
	if (p) {         // ��������½ڵ�ɹ����򷵻�false
		delete p;
		return false;
	}
	return true;
}

/**
 * @brief ��˫�˶��е�ͷ����,�����벻�ɹ�������false�����򷵻�true
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
 * @brief ��˫�˶��е�β����,�����벻�ɹ�������false�����򷵻�true
 * 
 */
template <typename T>
bool LinkedDeque<T>::pushRear(const T& x) {
	Node* newNode = new Node(x, head->prev, head);  // ��pushFront��ȣ���һ�䲻ͬ
	if (!newNode)
		return false;
	
	// ����ָ��ĸı�Ҳ��ͬ
	head->prev = newNode;
	newNode->prev->next = newNode;
	len++;
	return true;
}

/**
 * @brief Ԫ�س�����ͷ��������пգ�����false, ���򷵻�true
 */
template <typename T>
bool LinkedDeque<T>::popFront(T& x) {
	if (isEmpty())
		return false;
	// ���зǿգ�Ԫ�س�����
	Node* p = head->next;
	x = p->data;
	head->next = p->next;
	p->next->prev = head;
	delete p;
	len--;
	return true;	
}

/**
 * @brief Ԫ�س�����β��������пգ�����false, ���򷵻�true
 */
template <typename T>
bool LinkedDeque<T>::popRear(T& x) {
	if (isEmpty())
		return false;
	// ���зǿգ�Ԫ�س�����
	Node* p = head->prev;
	x = p->data;
	p->prev->next = head;
	head->prev = p->prev;
	delete p;
	len--;
	return true;	
}

/**
 * @brief ��ȡͷԪ��,ֻ��Ԫ�ظ�������
 */
template <typename T>
bool LinkedDeque<T>::getFront(T& x) const {
	if (isEmpty())
		return false;
	// ���зǿգ���ȡͷԪ��
	x = head->next->data;
	return true;
}

/**
 * @brief ��ȡβԪ��,ֻ��Ԫ�ظ�������
 */
template <typename T>
bool LinkedDeque<T>::getRear(T& x) const {
	if (isEmpty())
		return false;
	// ���зǿգ���ȡͷԪ��
	x = head->prev->data;
	return true;
}

/**
 * @brief ��ӡ����Ԫ��
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
 * @brief �����<<����
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
