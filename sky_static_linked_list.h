/** 
 *  @file   sky_static_linked_list.h 
 *  @brief  Implementation of static linked linear list with head node
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
 *  StaticLinkedList
 *  ��̬���������鷽ʽ��ʾ�������ڵ�next��Ϊ����ָ�꣬����ָ��
 */

#ifndef _SKY_STATIC_LINKED_LIST_H
#define _SKY_STATIC_LINKED_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

// Ԥ�ȷ���Ŀ��þ�̬����ռ��С
const int MAX_STATIC_LINKED_LIST_SIZE = 1000;

/**
 * @brief StaticLinkedListNode ��̬����ڵ㶨��
 * 
 */
template <typename T>
struct StaticLinkedListNode {
	T data;
	int next;               // next����int���ͣ�������ָ�룬���Ǿ�̬��������ͨ�������Ҫ����
};

/**
 * @brief StaticLinkedList ��̬����
 * 
 */
template <typename T>
class StaticLinkedList : public sky::List<T> {
public:
	// ���캯������������
	StaticLinkedList() { init(); }
	~StaticLinkedList() {}  
	
	// ���ʱ�
	int  length() const;
	bool isEmpty() const { return elem[0].next == -1; }
	bool getData(int i, T& x) const;
	int  search(const T& x) const;
	
	// ���ı�
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
 * @brief ��ʼ����̬����
 *        ��������ͷ���Ϳ������ӱ�
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
 * @brief �����
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
 * @brief ��ȡĳһ�ڵ��ֵ
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
 * @brief ����ĳһֵ�Ƿ����
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
 * @brief ����ĳһ�ڵ��ֵ
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
 * @brief ����һ�ڵ��ֵ
 */
template <typename T> 
bool StaticLinkedList<T>::insert(int i, const T& x) {
	if (i < 0)
		return false;
	//int p = elem[p].next;
	int p = 0;        // ��λ�������ڵ�ǰһ�ڵ�
	
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
 * @brief ɾ��ĳһ�ڵ��ֵ
 */
template <typename T> 
bool StaticLinkedList<T>::remove(int i, T& x) {
	if (i < 0)
		return false;
	//int p = elem[p].next;
	int p = 0;        // ��λ����ɾ���ڵ�ǰһ�ڵ�
	
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
		
		// ����ɾ���ڵ�ӵ���������ͷ��
		elem[q].next = available;
		available = q;
		return true;
	}
	else
		return false;
}

/**
 * @brief ɾ��ĳһ�ڵ��ֵ
 */
template <typename T> 
bool StaticLinkedList<T>::erase(int i) {
	if (i < 0)
		return false;
	//int p = elem[p].next;
	int p = 0;        // ��λ����ɾ���ڵ�ǰһ�ڵ�
	
	while (i--) {
		if (p != -1)
			p = elem[p].next;
		else
			return false;
	}
	
	if (p != -1 && elem[p].next != -1) {
		int q = elem[p].next;
		elem[p].next = elem[q].next;   
		//x = elem[q].data;      ���removeֻɾ����һ��
		
		// ����ɾ���ڵ�ӵ���������ͷ��
		elem[q].next = available;
		available = q;
		return true;
	}
	else
		return false;
}

/**
 * @brief �������ʼ״̬
 * 
 */
template <typename T>
void StaticLinkedList<T>::clear() {
	int p = 0;
	
	while (elem[p].next != -1) 
		p = elem[p].next;
	
	elem[p].next = available;  // �����ɿռ������ռ�������
	available = elem[0].next;  // ����available����
	elem[0].next = -1;         // ��ձ�
}

/**
 * @brief ���������
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


	
