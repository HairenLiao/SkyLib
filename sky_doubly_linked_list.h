/** 
 *  @file   sky_doubly_linked_list.h 
 *  @brief  Implementation of doubly linked linear list with head node
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
 *  DoublyLinkedList
 *  ˫����ʵ�֣���ͷ���(Head Node)
 */

#ifndef _SKY_DOUBLY_LINKED_LIST_H
#define _SKY_DOUBLY_LINKED_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/** 
 *  DoublyLinkedList����, ������ͨ��LinkedList�޸ĵõ����г�����ʵ�ֵ���ͬ
 *  
 */

template<typename T> class DoublyLinkedList : public sky::List<T> {
public:
	DoublyLinkedList() :
		len(0) {
		head = new Node;
	}
	DoublyLinkedList(int sz, const T& x);

	DoublyLinkedList(const DoublyLinkedList<T>& x); // �������캯��
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& x); // �����=����
	~DoublyLinkedList() {
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
	bool setData(int i, const T& x); // ����iλ��Ԫ�ص�ֵΪx
	bool insert(int i, const T& x); // ��iλ�ò���һ��ֵx  !!!
	bool insertRear(const T& x); // ��ĩβ���룬�൱��STL vector��push_back() !!!
	bool insertFront(const T& x); // ������ͷ���� !!!
	bool remove(int i, T& x); // ɾ��һ��Ԫ�أ�ɾ����Ԫ��ͨ��x���� !!!
	bool erase(int i); // ɾ��iλ��Ԫ�أ�������Ԫ��ֵ !!!
	void clear(); // ��ձ�,����ɾ��ͷ���
	void reverse(); // ������

	bool operator==(const DoublyLinkedList<T>& x) const; // ����Node����Ϊ�ڲ��࣬��������ó�Ա������������Ԫ����������==
	bool operator!=(const DoublyLinkedList<T>& x) const;
	//frined bool operator==(const LinkedList<T>& x, const LinkedList<T>& y);
	//frined bool operator!=(const LinkedList<T>& x, const LinkedList<T>& y);

private:
	/**
	 *  DoublyLinkedList Node���壬���LinkedList���壬ֻ��Node�Ķ���ı�
	 */
	struct Node {
		T data;
		/* ʹ��prev��next��ʹ��left��right����ǰ���ڵ㡢 ��̽ڵ���� */
		Node* prev;
		Node* next;
		Node(const T& item = T(), Node* p = NULL, Node* n = NULL) :
			data(item), prev(p), next(n) {
		}
	};

	Node* head;
	/* ��tail�ڵ�������ʹ��insertRear(x)������ʱ�临�Ӷȱ�ΪO(1)
	 * ���������ʵ����STL��ʹ��tail���в�ͬ����ʼ��ʱhead��tail��ͬһ�ڵ㣬
	 * ��STL��tail�ڵ��ʼ��ʱ��head�������ڵ�
	 */
	// Node* tail;
	int len; // ����

	/*
	 *  init() ��ʼ������������0,����ͷ���
	 */
	void init() {
		len = 0;
		head = new Node;
	}

	void removeAll(); // �����������ݽ�㼰ͷ���
};

/**
 * @brief ������н�㼰ͷ���
 *        ��LinkedList��ȫһ��
 */
template<class T> void DoublyLinkedList<T>::removeAll() {
	// Node* p; ������Ϊp
	Node* p;

	// ע�ⲻ��head->next != NULL�� ��ΪͬʱҪɾ��ͷ���
	while (head) { // �ȼ���while (head != NULL)
		p = head;
		head = head->next;
		delete p;
	}

}

/**
 * @brief ���캯����N����ֵͬ��ɵ�˫����
 * @param sz ����Ԫ�ظ���
 * @param x  ÿ������Ԫ�صĳ�ʼ��ֵ
 */
template<typename T> DoublyLinkedList<T>::DoublyLinkedList(int sz, const T& x) {
	init();
	if (sz > 0) {
		len = sz;

		// ��ͷ������sz���½ڵ�, ÿ���½ڵ��prev��ʼ��Ϊhead, next��ʼ��Ϊhead->next
		while (sz--) {
			Node* newNode = new Node(x, head, head->next);
			head->next = newNode;

			// ���������û�У�newNode��һ�ڵ��prevָ��δ���ú�
			if (newNode->next)
				newNode->next->prev = newNode;
		}
	}
}

/**
 * @brief �������캯��
 * @param x ��һ˫����
 * �����ʵ������Ҫ�ǲ�Ҫ����������ָ��ͬ�������ݣ�����һ����Ĳ�����Ӱ������һ����
 */
template<typename T> DoublyLinkedList<T>::DoublyLinkedList(
		const DoublyLinkedList<T>& x) {
	init();
	Node* p1 = x.head;
	Node* p2 = head;

	while (p1->next) { // �ȼ���while (p1->next != NULL)
		// �����½ڵ��prevָ����Ҫָ��p2, nextָ��ΪNULL
		p2->next = new Node(p1->next->data, p2);
		p1 = p1->next;
		p2 = p2->next;
	}

	len = x.len;
}

/**
 * @brief ��ձ�����ɾ��ͷ���
 * ��removeAll()˽�з����Ĳ�ͬʱ����ɾ��ͷ�ڵ㣬������0
 *  
 */
template<typename T> void DoublyLinkedList<T>::clear() {
	Node* p;

	while (head->next) { // �ȼ���while (head->next != NULL)
		p = head->next;
		head = head->next;
		delete p;
	}

	// ����˫��������ر�ĵط���head->prev��Ҫ��NULL
	head->prev = NULL;

	len = 0;
}

/**
 *  @brief =���������
 */
template<typename T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& x) {
	if (this != &x) { // ��������Ƿ��Ը�ֵ����clear()���������ݶ�����ˣ�
		clear();
		Node* p1 = x.head;
		Node* p2 = head;

		while (p1->next) { // �ȼ���while (p1->next != NULL) 
			p2->next = new Node(p1->next->data, p2);
			p1 = p1->next;
			p2 = p2->next;
		}

		len = x.len;
	}

	return *this;
}

/**
 * @brief �ж�����Ԫ���Ƿ񣨷��ϸ񣩵������ձ�ֻ��һ��Ԫ�صı������� 
 */
template <typename T>
bool DoublyLinkedList<T>::isIncreasing() const {
	Node* p1 = head->next;
	Node* p2;

	// ���p1��ΪNULL,ȡp2Ϊ����
	if (p1) {
		while (p1->next) {
			p2 = p1->next;
			if (p1->data > p2->data) // ���ڱ��в鵽ǰ��Ԫ�ش��ں��Ԫ�أ��򷵻�false
			return false;
			else
			p1 = p2;
		}
	}

	return true;
}

/**
 *  @brief �õ���i������ֵ���ǵ��Ǵ�0��ʼ��������len-1�����
 *  @param i Ԫ��λ�ã���0��ʼ����
 *  @param x ��i���ڵ��ֵ
 *  @return ���i������Ҫ�󣬷���false, ��ȷȡ�ط���true
 *  		�뵥������ͬ
 */
template <typename T>
bool DoublyLinkedList<T>::getData(int i, T& x) const {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len)
	return false;

	// ������˵��iλ����ȷ
	Node* p = head;

	// ����i����������ã�����ֱ����i--,����Ҫ��һ������ı���j
	// ����i��λ�ã���ѭ�������꣬pָ��Ҫȡ�Ľ��ǰһλ��
	while (i--) {
		p = p->next;
	}

	x = p->next->data;
	return true;
}

/**
 * @brief �ڱ��в���x,�ҵ�������λ�ã����򷵻�-1
 * @param x �����ҵ�Ԫ��ֵ
 * @return �ҵ�������λ�ã����򷵻�-1
 *         �뵥������ͬ
 */
template <typename T>
int DoublyLinkedList<T>::search(const T& x) const {
	int i = 0;
	Node* p = head;
	while (p->next) { // �ȼ��� while (p->next != NULL��
		if (p->next->data == x)
		return i;
		i++;
		p = p->next;
	}

	return -1;
}

/**
 *  @brief �����Ԫ�أ��Կո�ָ�
 *         �뵥������ͬ  
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
 * @brief ���õ�i���ڵ��ֵΪx
 * @param i �ڵ�i,��0����
 * @param x  ���õ�ֵ
 * @return ������óɹ�������true, ���iֵԽ�磬����false
 *  ע����getData(i, x)������ʵ��ֻ��һ�䲻ͬ
 *  �뵥������ͬ����Ϊ�˲�������ı�prev��nextָ��
 */
template <typename T>
bool DoublyLinkedList<T>::setData(int i, const T& x) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len)
	return false;

	// ������˵��iλ����ȷ
	Node* p = head;

	// ����i����������ã�����ֱ����i--,����Ҫ��һ������ı���j
	// ����i��λ�ã���ѭ�������꣬pָ��Ҫ�ı�Ľ��ǰһλ��
	while (i--) {
		p = p->next;
	}

	p->next->data = x; // ���getData(i, x)������ʵ�֣�ֻ��һ�䲻ͬ��
	return true;
}

/** 
 *  @brief   ��һ����λ�ò���ֵ
 *  @param i �����λ�ã���0��ʼ
 *  @param x Ҫ�����ֵ
 *  @return  ��ȷ���뷵��true�����򷵻�false
 *           ע��˷���ʵ���뵥����Ĳ��
 */
template <typename T>
bool DoublyLinkedList<T>::insert(int i, const T& x) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len)
	return false;

	// ������˵��iλ����ȷ
	Node* p = head;

	// ����i��λ�ã���ѭ�������꣬pָ��Ҫ����Ľ��ǰһλ��
	while (i--) {
		p = p->next;
	}

	// p1ָ��Ҫ����Ľ��ĺ�һλ�ã��п���ΪNULL, ����Ҫp1
	// Node* p1 = p->next;

	// �½ڵ�prev��Ϊp, next��Ϊp->next
	Node* newNode = new Node(x, p, p->next);
	p->next = newNode;

	// ���p1��ΪNULL,����prevָ����ΪnewNode
	// p1������newNode->next����
	// if (p1) 
	if (newNode->next)
	newNode->next->prev = newNode;

	len++;
	return true;
}

/**
 *  @brief   ������ĩβ�����½ڵ�
 *  @param x Ҫ����Ľڵ�ֵ
 *  @return  ���û�пռ���뷵��false,��ȷ���뷵��true
 * 
 *  ���ڱ������ʵ��û�ж���ĩβ�ڵ㣬���Դ˷�����ʱ��Ч����Theta(n)��Ч�ʽϵ� 
 *  ����ͨ������һ��tail�ڵ�ʹ�ô˲�����ʱ�临�Ӷȱ�ΪO(1)
 */
template <typename T>
bool DoublyLinkedList<T>::insertRear(const T& x) {
	Node* p = head;

	// ѭ��������ĩβ
	while (p->next) {
		p = p->next;
	}

	// �����½ڵ�, prev��Ϊp
	Node* newNode = new Node(x, p);
	//Node*  newNode = new Node(x); ��LinkedListֻ�д˾䲻ͬ

	// ������ɳɹ�����ԭ�����ĩ�ڵ�ָ����½ڵ�
	if (newNode) {
		p->next = newNode;
		len++;
		return true;
	}

	// ���δ���ɳɹ�������false
	return false;
}

/**
 *  @brief   ������ͷ�����½ڵ�
 *  @param x Ҫ����Ľڵ�ֵ
 *  @return  ���û�пռ���뷵��false,��ȷ���뷵��true
 * 
 *  ��������ʱ��Ч��ΪO(1),Ч�ʸ�
 */
template <typename T>
bool DoublyLinkedList<T>::insertFront(const T& x) {
	// �����½ڵ�, prev��Ϊhead, next��Ϊhead->next
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
 * @brief   ɾ��ĳһλ�õĽ��,ɾ��Ԫ��ͨ�����÷���
 * @param i �����λ�ã���0��ʼ
 * @param x ɾ����ֵͨ�����÷���
 * @return  ��ȷɾ������true�����򷵻�false
 * 
 */
template <typename T>
bool DoublyLinkedList<T>::remove(int i, T& x) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len)
	return false;

	Node* p = head;

	// ����i��λ�ã���ѭ�������꣬pָ��Ҫɾ���Ľ��ǰһλ��
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
 * @brief   ɾ��ĳһλ�õĽ��
 * @param i �����λ�ã���0��ʼ
 * @param x ɾ����ֵͨ�����÷���
 * @return  ��ȷɾ������true�����򷵻�false
 * 
 */
template <typename T>
bool DoublyLinkedList<T>::erase(int i) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len)
	return false;

	Node* p = head;

	// ����i��λ�ã���ѭ�������꣬pָ��Ҫɾ���Ľ��ǰһλ��
	while (i--) {
		p = p->next;
	}

	Node* nodeToErase = p->next;
	p->next = p->next->next;

	if (nodeToErase->next)
	nodeToErase->next->prev = p;

	delete nodeToErase; // �ͷ�ɾ���ڵ�Ŀռ�
	len--;
	return true;
}

/**
 * @brief ������
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

	// ��headָ��ĩ�ڵ�
	head->next = p1;
	p1->prev = head;
}

/**
 * @brief ==��������أ��ж��������Ա��Ƿ����
 *        �뵥����ʵ�ִ�����ȫ��ͬ
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
		return true; // ���������ȣ�����ÿ��Ԫ������ͬ������˳������
	}
	else {
		return false;
	}
}

/**
 * @brief !=��������أ��ж��������Ա��Ƿ����
 *        �뵥����ʵ����ȫ��ͬ
 */
template <typename T>
bool DoublyLinkedList<T>::operator!=(const DoublyLinkedList<T>& x) const {
	return !(this == x);
}

/**
 * @brief ���������<<��ʹ�ÿ��Է��������������Ա�
 *        �뵥����ʵ����ȫ��ͬ
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
