/** 
 *  @file   sky_circular_list.h 
 *  @brief  Implementation of circular linked linear list with head node
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

/** 
 *  CircularList
 *  �������Ա��ѭ������ʽʵ�֣���ͷ���(Head Node)��β�ڵ�(Tail Node)
 */

#ifndef _SKY_CIRCULAR_LINKED_LIST_H
#define _SKY_CIRCULAR_LINKED_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/**
 * @brief CircularLinkedListNode ѭ��������ڵ㣬��ȡ�ⲿ����ķ�ʽ
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
 * @brief CircularList ѭ���������� CircularListΪCircularLinkedList֮���
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
	CircularList(const CircularList<T>& x); // �������캯��
	CircularList<T>& operator=(const CircularList<T>& x); // �����=����
	~CircularList() {
		removeAll();
	} // ��������

	int length() const {
		return len;
	} // ���ȣ�Ԫ�ظ�����
	bool isEmpty() const {
		return len == 0;
	} // ���Ƿ�Ϊ��
	bool isIncreasing() const; // �ж�������Ԫ���Ƿ����
	bool getData(int i, T& x) const; // ��ȡiλ�ã���i+1��Ԫ�أ���ֵ��ͨ��x����
	int search(const T& x) const; // �ڱ��в���x���ҵ�������λ�ã�δ�ҵ�����-1
	void output() const; // ���������

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
	bool setData(int i, const T& x); // ����iλ��Ԫ�ص�ֵΪx
	bool setData(const T& x);
	bool insert(const T& x);
	bool remove(T& x);

	bool insert(int i, const T& x); // ��iλ�ò���һ��ֵx
	// �˷������ṩ��ʱ�临�Ӷ�ΪTheta(n),�ʲ��ṩ
	//bool insertRear(const T& x);                       // ��ĩβ���룬�൱��STL vector��push_back()
	bool insertFront(const T& x); // ������ͷ����
	bool remove(int i, T& x); // ɾ��һ��Ԫ�أ�ɾ����Ԫ��ͨ��x����
	bool erase(int i); // ɾ��iλ��Ԫ�أ�������Ԫ��ֵ
	void clear(); // ��ձ�,����ɾ��ͷ���


	template<typename TT> friend bool operator==(const CircularList<TT>& x,
			const CircularList<TT>& y); // ����Node����Ϊ�ڲ��࣬��������ó�Ա������������Ԫ����������==
	template<typename TT> friend bool operator!=(const CircularList<TT>& x,
			const CircularList<TT>& y);

private:
	CircularLinkedListNode<T>* head;
	CircularLinkedListNode<T>* tail;
	CircularLinkedListNode<T>* current;
	int len;

	/*
	 *  init() ��ʼ������������0,����ͷ���
	 */
	void init() {
		len = 0;
		head = tail = current = new CircularLinkedListNode<T>;
		head->next = tail;
	}

	void removeAll(); // �����������ݽ�㼰ͷ���
};

/**
 * @brief ������нڵ�
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
 * @brief ���캯������ʼ��Ϊsz����ͬԪ��x
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
 * @brief �������캯��
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
 * @brief �����=����
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
 * @brief �ж������Ƿ�Ϊ����
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
 * @brief ��ȡĳһ�ڵ�ֵ֮
 * 
 */
template <typename T>
bool CircularList<T>::getData(int i, T& x) const {
	if (i < 0 || i >= len)
	    return false;

	// �����ǳ�����������ʹcurrent�����仯
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
 * @brief ����ֵλ��
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
 * @brief �������Ԫ��
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
 * @brief currentָ���Ƶ���һλ��
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

