/** 
 *  @file   sky_circular_doubly_linked_list.h 
 *  @brief  Implementation of circular doubly linked linear list with head node
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
 *  CircularDoublyLinkedList
 *  ѭ��˫����ʵ�֣���ͷ���(Head Node)
 */

#ifndef _SKY_CIRCULAR_DOUBLY_LINKED_LIST_H
#define _SKY_CIRCULAR_DOUBLY_LINKED_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/** 
 *  DoublyLinkedList����, ������ͨ��LinkedList�޸ĵõ����г�����ʵ�ֵ���ͬ
 *  
 */

template<typename T> class CircularDoublyLinkedList : public sky::List<T> {
public:
	CircularDoublyLinkedList() : len(0) {
		head = new Node;
		head->prev = head;
		head->next = head;
	}
	CircularDoublyLinkedList(int sz, const T& x);
	CircularDoublyLinkedList(const CircularDoublyLinkedList<T>& x); // �������캯��
	CircularDoublyLinkedList<T>
			& operator=(const CircularDoublyLinkedList<T>& x); // �����=����
	~CircularDoublyLinkedList() {
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
	void unique(); // ɾ�������е��ظ��ڵ�
	void merge(CircularDoublyLinkedList<T>& x); // �ϲ���һ����
	void sort(); // �������������ʹ��InsertionSort�㷨	

	bool operator==(const CircularDoublyLinkedList<T>& x) const; // ����Node����Ϊ�ڲ��࣬��������ó�Ա������������Ԫ����������==
	bool operator!=(const CircularDoublyLinkedList<T>& x) const;

private:
	/**
	 *  CircularDoublyLinkedList Node���壬���LinkedList���壬ֻ��Node�Ķ���ı�
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
	int len; // ����,ʹ��length()�������㷨���Ӷȱ�ΪO(1)

	/*
	 *  init() ��ʼ������������0,����ͷ���
	 */
	void init() {
		len = 0;
		head = new Node;
		head->next = head;
		head->prev = head;
	}

	void removeAll(); // �����������ݽ�㼰ͷ���
};

/**
 * @brief ������н�㼰ͷ���
 *        ��LinkedList��ȫһ��
 */
template<class T> void CircularDoublyLinkedList<T>::removeAll() {
	// Node* p; ������Ϊp
	Node* p = head->next;

	// ɾ����ͷ���������н��
	while (p != head) {
		Node* tmp = p;
		p = p->next;
		delete tmp;
	}

	delete head; // ɾ��ͷ���

}

/**
 * @brief ���캯����N����ֵͬ��ɵ�˫����
 * @param sz ����Ԫ�ظ���
 * @param x  ÿ������Ԫ�صĳ�ʼ��ֵ
 */
template<typename T> CircularDoublyLinkedList<T>::CircularDoublyLinkedList(
		int sz, const T& x) {
	init();
	if (sz > 0) {
		len = sz;

		// ��ͷ������sz���½ڵ�, ÿ���½ڵ��prev��ʼ��Ϊhead, next��ʼ��Ϊhead->next
		while (sz--) {
			Node* newNode = new Node(x, head, head->next);
			head->next = newNode;
			// �˴������ж�newNode->next�Ƿ�ΪNULL,��Ϊ��ض�����
			newNode->next->prev = newNode;
		}
	}
}

/**
 * @brief �������캯��
 * @param x ��һѭ��˫����
 * �����ʵ������Ҫ�ǲ�Ҫ����������ָ��ͬ�������ݣ�����һ����Ĳ�����Ӱ������һ����
 */
template<typename T> CircularDoublyLinkedList<T>::CircularDoublyLinkedList(
		const CircularDoublyLinkedList<T>& x) {
	init();
	Node* p1 = x.head->next;
	Node* p2 = head;

	while (p1 != x.head) {
		// �����½ڵ��prevָ����Ҫָ��p2, nextָ��ΪNULL
		Node* newNode = new Node(p1->data, p2, p2->next);
		p2->next = newNode;
		newNode->next->prev = newNode;
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
template<typename T> void CircularDoublyLinkedList<T>::clear() {
	Node* p = head->next;

	while (p != head) {
		Node* tmp = p;
		p = p->next;
		delete tmp;
	}

	// ѭ��˫����head֮prev��nextָ�뼰������Ҫ����
	head->next = head;
	head->prev = head;
	len = 0;
}

/**
 *  @brief =���������
 */
template<typename T> CircularDoublyLinkedList<T>& CircularDoublyLinkedList<T>::operator=(const CircularDoublyLinkedList<T>& x) {
	if (this != &x) { // ��������Ƿ��Ը�ֵ����clear()���������ݶ�����ˣ�
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
 * @brief �ж�����Ԫ���Ƿ񣨷��ϸ񣩵������ձ�ֻ��һ��Ԫ�صı������� 
 */
template <typename T>
bool CircularDoublyLinkedList<T>::isIncreasing() const {
	Node* p1 = head->next;
	Node* p2;

	while (p1->next != head) {
		p2 = p1->next;

		// ��p2��Ϊͷ�������ڱ��в鵽ǰ��Ԫ�ش��ں��Ԫ�أ��򷵻�false   		
		if (p1->data > p2->data)
		return false;
		else
		p1 = p2;
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
bool CircularDoublyLinkedList<T>::getData(int i, T& x) const {
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
int CircularDoublyLinkedList<T>::search(const T& x) const {
	int i = 0;
	Node* p = head->next;
	while (p != head) {
		if (p->data == x)
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
void CircularDoublyLinkedList<T>::output() const {
	Node* p = head->next;
	while (p != head) {
		std::cout << p->data;
		if (p->next != head)
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
bool CircularDoublyLinkedList<T>::setData(int i, const T& x) {
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
bool CircularDoublyLinkedList<T>::insert(int i, const T& x) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len)
	    return false;

	// ������˵��iλ����ȷ
	Node* p = head;

	// ����i��λ�ã���ѭ�������꣬pָ��Ҫ����Ľ��ǰһλ��
	while (i--) {
		p = p->next;
	}

	// �½ڵ�prev��Ϊp, next��Ϊp->next
	Node* newNode = new Node(x, p, p->next);
	p->next = newNode;
	newNode->next->prev = newNode;

	len++;
	return true;
}

/**
 *  @brief   ������ĩβ�����½ڵ�
 *  @param x Ҫ����Ľڵ�ֵ
 *  @return  ���û�пռ���뷵��false,��ȷ���뷵��true
 * 
 *  ѭ��˫��������ص��ǲ���Ҫ����tail��㣬�˲�����ʱ�临�Ӷȼ�ΪO(1)
 */
template <typename T>
bool CircularDoublyLinkedList<T>::insertRear(const T& x) {

	// �����½ڵ�, prev��Ϊhead->prev, next��Ϊhead
	Node* newNode = new Node(x, head->prev, head);

	// ������ɳɹ�����ԭ�����ĩ�ڵ�ָ����½ڵ�
	if (newNode) {
		head->prev = newNode;
		newNode->prev->next = newNode;
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
 *  ��������ʱ��Ч��ҲΪO(1)
 */
template <typename T>
bool CircularDoublyLinkedList<T>::insertFront(const T& x) {
	// �����½ڵ�, prev��Ϊhead, next��Ϊhead->next
	Node* newNode = new Node(x, head, head->next);

	if (newNode) {
		head->next = newNode;
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
bool CircularDoublyLinkedList<T>::remove(int i, T& x) {
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
bool CircularDoublyLinkedList<T>::erase(int i) {
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
	nodeToErase->next->prev = p;

	delete nodeToErase; // �ͷ�ɾ���ڵ�Ŀռ�
	len--;
	return true;
}

/**
 * @brief ������
 * ѭ��˫����ķ�����������б���ͨ˫������򵥵��߼���ɣ�
 * ��ÿ�����ڵ�֮���prev,nextָ��
 *  
 */
template <typename T>
void CircularDoublyLinkedList<T>::reverse() {
	Node* p1 = head;
	Node* p2 = head->next;
	Node* p3;

	while (p2 != head) {
		p3 = p2->next;
		p1->prev = p2;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
}

/**
 * @brief �������е���ͬ����Ԫ��ɾ��һ��
 */
template <typename T>
void CircularDoublyLinkedList<T>::unique() {
	Node* p1 = head->next;
	Node* p2;
	while (p1->next != head) {
		p2 = p1->next;
		// ���ǰ����ֵ��ͬ��ɾ��p2�ڵ�, ����p1ָ����ǰ��
		if (p1->data == p2->data) {
			p1->next = p2->next;
			p2->next->prev = p1;
			delete p2;
		}
		else {
			p1 = p1->next;
		}
	}
}

/**
 * @brief �ϲ���һ����
 */
template <typename T>
void CircularDoublyLinkedList<T>::merge(CircularDoublyLinkedList<T>& x) {
	Node* p1 = head->next;
	Node* p2 = x.head->next;
	Node* p;

	while (p1 != head && p2 != x.head) {
		// ���p2�ڵ�ֵС��p1��ֵ����p2�ڵ����p1�ڵ�ǰ����ɾ��x��p2�ڵ�
		if (p2->data < p1->data) {
			p = p2;
			p2 = p2->next;
			// x��ɾ��p�ڵ�
			p->prev->next = p->next;
			p->next->prev = p->prev;
			// ��p���뵽p1�ڵ�ǰ
			p1->prev->next = p;
			p->prev = p1->prev;

			p1->prev = p;
			p->next = p1;
		}
		else {
			p1 = p1->next;
		}
	}

	// ��x����ʣ��Ԫ�ؾ�����ĩβ
	if (p2 != x.head) {
		p1->prev->next = p2;
		p2->prev = p1->prev;

		p1->prev = x.head->prev;
		x.head->prev->next = p1;

		x.head->prev = x.head;
		x.head->next = x.head;
	}
}

/**
 * @brief ����, ʹ�ò��������㷨���ο������������Ͻ��еĲ�������
 */
/*       template <class T>
 void insertionSort(T a[], int n){
 for(int i=1;i<n;i++){
 T t=a[i];
 int j;
 for(j=i;j>0&&t<a[j-1];j--)
 a[j]=a[j-1];
 a[j]=t;
 }
 }
 */
template <typename T>
void CircularDoublyLinkedList<T>::sort() {
	// ����С��2��Ԫ�صı�ֱ�ӷ���
	if (len < 2) return;

	Node* pi = head->next->next; // i = 1
	Node* pj;
	Node* t;

	while (pi != head) {
		t = pi;
		pi = pi->next;

		pj = t;
		while ((pj->prev != head) && (t->data < pj->prev->data)) {
			pj = pj->prev;
		}

		if (pj != t) {
			t->prev->next = pi;
			pi->prev = t->prev;

			t->next = pj;
			t->prev = pj->prev;

			pj->prev = t;
			t->prev->next = t;
		}
	}
}

/**
 * @brief ==��������أ��ж��������Ա��Ƿ����
 *        �뵥����ʵ�ִ�����ȫ��ͬ
 */
template <typename T>
bool CircularDoublyLinkedList<T>::operator==(const CircularDoublyLinkedList<T>& x) const {
	if (len == x.len) {
		Node* p1 = head->next;
		Node* p2 = x.head->next;
		while (p1 != head) {
			if (p1->data != p2->data)
			return false;
			p1 = p1->next;
			p2 = p2->next;
		}
		return true; // ���������ȣ�����ÿ��Ԫ������ͬ������˳������
	}

	return false;

}

/**
 * @brief !=��������أ��ж��������Ա��Ƿ����
 *        �뵥����ʵ����ȫ��ͬ
 */
template <typename T>
bool CircularDoublyLinkedList<T>::operator!=(const CircularDoublyLinkedList<T>& x) const {
	return !(this == x);
}

/**
 * @brief ���������<<��ʹ�ÿ��Է��������������Ա�
 *        �뵥����ʵ����ȫ��ͬ
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const CircularDoublyLinkedList<T>& x) {
	out << "(";
	x.output();
	out << ")";
	return out;
}

} // namespace sky 

#endif /* _SKY_CIRCULAR_DOUBLY_LINKED_LIST_H */
