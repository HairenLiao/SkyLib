/** 
 *  @file   sky_linked_list.h 
 *  @brief  Implementation of linked linear list with head node
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
 *  LinkedList
 *  �������Ա����ʽʵ�֣���ͷ���(Head Node)
 */

#ifndef _SKY_LINKED_LIST_H
#define _SKY_LINKED_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/* 
 *  LinkedList����, ������ͨ��SeqList�޸ĵõ����г�����ʵ�ֵ���ͬ
 *  
 */

template<typename T> class LinkedList : public sky::List<T> {
public:
	// LinkedList() : len(0), head(NULL) {} ��������ͷ���û�н�����
	LinkedList() :
		len(0) {
		head = new Node;
	}
	LinkedList(int sz, const T& x);
	//SeqList() : len(0), maxSize(0), data(NULL) {};       // Ĭ�Ϲ��캯��
	//SeqList(int sz);                                     // ָ������
	//SeqList(int sz, const T& x);                         // ��ʼ�����ȣ�ÿһԪ�ظ�ֵx

	LinkedList(const LinkedList<T>& x); // �������캯��
	LinkedList<T>& operator=(const LinkedList<T>& x); // �����=����
	~LinkedList() {
		removeAll();
	} // ��������
	//~SeqList() { delete[] data; }                       

	int length() const {
		return len;
	} // ���ȣ�Ԫ�ظ�����
	// int  capacity() const { return maxSize; }         ��ȡ��������������Ҫ
	bool isEmpty() const {
		return len == 0;
	} // ���Ƿ�Ϊ��
	bool isIncreasing() const; // �ж�������Ԫ���Ƿ����

	//bool isFull() const { return len == maxSize; }     �ж�����Ŀռ��Ƿ�װ���ķ���Ҳ������Ҫ
	bool getData(int i, T& x) const; // ��ȡiλ�ã���i+1��Ԫ�أ���ֵ��ͨ��x����
	int search(const T& x) const; // �ڱ��в���x���ҵ�������λ�ã�δ�ҵ�����-1
	void output() const; // ���������

	bool setData(int i, const T& x); // ����iλ��Ԫ�ص�ֵΪx
	bool insert(int i, const T& x); // ��iλ�ò���һ��ֵx
	bool insertRear(const T& x); // ��ĩβ���룬�൱��STL vector��push_back()
	bool insertFront(const T& x); // ������ͷ����
	bool remove(int i, T& x); // ɾ��һ��Ԫ�أ�ɾ����Ԫ��ͨ��x����
	bool erase(int i); // ɾ��iλ��Ԫ�أ�������Ԫ��ֵ
	void clear(); // ��ձ�,����ɾ��ͷ���
	void reverse(); // ������

	bool operator==(const LinkedList<T>& x) const; // ����Node����Ϊ�ڲ��࣬��������ó�Ա������������Ԫ����������==
	bool operator!=(const LinkedList<T>& x) const;
	//frined bool operator==(const LinkedList<T>& x, const LinkedList<T>& y);
	//frined bool operator!=(const LinkedList<T>& x, const LinkedList<T>& y);
	template<typename TT> friend std::ostream& operator<<(std::ostream& os,
			const LinkedList<TT>& x);

	// ��������������������Ҫ
	// bool reserve(int newCapacity);                    
	// bool resize(int newSize);                         
	// T& operator[](int i);                                // ��ȡiλ��Ԫ������
	// const T& operator[](int i) const;                    // ���������ȡiλ��Ԫ������

private:
	/*
	 *  �кܶ��ֶ���Node��ķ������������ⲿ���壻 �����˽��Ƕ����ķ�ʽʹ����һ�ṹ���ⲻ�ɼ�����������ʵ��
	 */
	struct Node {
		T data;
		Node* next;
		Node(const T& item = T(), Node* ptrNext = NULL) :
			data(item), next(ptrNext) {
		}
		// �����������캯������������һ������
		// Node(const T& item, Node* ptrNext = NULL) : data(item), next(ptrNext) {}
		// Node(Node* ptrNext = NULL) : next(ptrNext) {}
	};

	// T* data;  ˳����е�����ָ�뱻ͷ���������
	Node* head;

	// int maxSize;  ˳����е�maxSize������Ҫ����Ϊ������������������ĸ���                                       
	int len; // ����
	//bool expandCapacity();                             // ���ݺ���Ҳ������Ҫ 

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
 *  removeAll()˽�з�����������н�㼰ͷ���
 */
template<typename T> void LinkedList<T>::removeAll() {
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
 * @brief ���캯����N����ֵͬ��ɵ�����
 */
template<typename T> LinkedList<T>::LinkedList(int sz, const T& x) {
	init();
	if (sz > 0) {
		len = sz;

		// ��ͷ������sz���½ڵ�
		while (sz--) {
			Node* newNode = new Node(x, head->next);
			head->next = newNode;
		}
	}
}

/*
 *   �������캯��
 *   �����ʵ������Ҫ�ǲ�Ҫ����������ָ��ͬ�������ݣ�����һ����Ĳ�����Ӱ������һ����
 */
template<typename T> LinkedList<T>::LinkedList(const LinkedList<T>& x) {
	init();
	Node* p1 = x.head;
	Node* p2 = head;

	while (p1->next) { // �ȼ���while (p1->next != NULL)
		p2->next = new Node(p1->next->data);
		p1 = p1->next;
		p2 = p2->next;
	}
	// ����ʵ�ִ���tmpNode1,tmpNode2���ǽ��ָ�룬�����ǽ�㣡����֮��Ҫ��
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
 *  @brief =���������
 */
template<typename T> LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x) {
	if (this != &x) { // ��������Ƿ��Ը�ֵ����clear()���������ݶ�����ˣ�
		clear();
		Node* p1 = x.head;
		Node* p2 = head;

		while (p1->next) { // �ȼ���while (p1->next != NULL) 
			p2->next = new Node(p1->next->data);
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
bool LinkedList<T>::isIncreasing() const {
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
 */
template <typename T>
bool LinkedList<T>::getData(int i, T& x) const {
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
 */
template <typename T>
int LinkedList<T>::search(const T& x) const {
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
 *  setData(i, x)���õ�i���ڵ��ֵΪx
 *  ע����getData(i, x)������ʵ��ֻ��һ�䲻ͬ
 */
template <typename T>
bool LinkedList<T>::setData(int i, const T& x) {
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
 */
template <typename T>
bool LinkedList<T>::insert(int i, const T& x) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len)
	return false;

	// ������˵��iλ����ȷ
	Node* p = head;

	// ����i��λ�ã���ѭ�������꣬pָ��Ҫ����Ľ��ǰһλ��
	while (i--) {
		p = p->next;
	}

	Node* newNode = new Node(x, p->next);
	p->next = newNode;
	len++;
	return true;
}

/**
 *  @brief   ������ĩβ�����½ڵ�
 *  @param x Ҫ����Ľڵ�ֵ
 *  @return  ���û�пռ���뷵��false,��ȷ���뷵��true
 * 
 *  ���ڱ������ʵ��û�ж���ĩβ�ڵ㣬���Դ˷�����ʱ��Ч����Theta(n)��Ч�ʽϵ�
 */
template <typename T>
bool LinkedList<T>::insertRear(const T& x) {
	Node* p = head;

	// ѭ��������ĩβ
	while (p->next) {
		p = p->next;
	}

	// �����½ڵ�
	Node* newNode = new Node(x);

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
bool LinkedList<T>::insertFront(const T& x) {
	// �����½ڵ�
	Node* newNode = new Node(x, head->next);

	if (newNode) {
		head->next = newNode;
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
bool LinkedList<T>::remove(int i, T& x) {
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
bool LinkedList<T>::erase(int i) {
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

	delete nodeToErase; // �ͷ�ɾ���ڵ�Ŀռ�
	len--;
	return true;
}

/**
 * @brief ��ձ�����ɾ��ͷ���
 * ��removeAll()˽�з����Ĳ�ͬʱ����ɾ��ͷ�ڵ㣬������0
 *  
 */
template <typename T>
void LinkedList<T>::clear() {
	Node* p;

	while (head->next) { // �ȼ���while (head->next != NULL)
		p = head->next;
		head = head->next;
		delete p;
	}

	len = 0;
}

/**
 * @brief ������,������˼����ϰ
 *  
 */
template <typename T>
void LinkedList<T>::reverse() {

	Node* p1 = NULL; // �Ƚ�p1��NULL������ʡ��������
	Node* p2 = head->next; // p2ָ���1���ڵ�
	Node* p3;

	while (p2) {
		p3 = p2->next; // �洢��һ�ڵ�
		p2->next = p1; // ���ڵ�ָ��ָ��ǰ���ڵ㣬��1���ڵ�ָ��NULL
		p1 = p2;
		p2 = p3;
	}

	head->next = p1;

	/* // ��len<=1, �򷴲�����û������
	 if (len > 1) {
	 Node* p1 = head->next;
	 Node* p2 = p1->next;
	 Node* p3;
	 p1->next = NULL;         // ��һ���ڵ��ָ����0
	 while (p2) {
	 p3 = p2->next;
	 p2->next = p1;
	 p1 = p2;
	 p2 = p3;
	 }
	 
	 head->next = p1;        // ��ͷָ��ָ�����һ���ڵ�	
	 }
	 */
}

/**
 * @brief ==��������أ��ж��������Ա��Ƿ����
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
		return true; // ���������ȣ�����ÿ��Ԫ������ͬ������˳������
	}
	else {
		return false;
	}
}

/**
 * @brief !=��������أ��ж��������Ա��Ƿ����
 */
template <typename T>
bool LinkedList<T>::operator!=(const LinkedList<T>& x) const {
	return !(this == x);
}

/**
 * @brief ���������<<��ʹ�ÿ��Է��������������Ա�
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& x) {
	out << "(";
	//x.output();  ʹ��output()���������std::cout!
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
