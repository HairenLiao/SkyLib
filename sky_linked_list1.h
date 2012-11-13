/** 
 *  @file   sky_linked_list1.h 
 *  @brief  Implementation of linked linear list without head node
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
 *  LinkedList1
 *  �������Ա����ʽʵ�֣�����ͷ���(Head Node)
 *       ��ʵ�ִӴ�ͷ���İ汾�޸Ķ���
 */

#ifndef _SKY_LINKED_LIST1_H
#define _SKY_LINKED_LIST1_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/* 
 *  LinkedList1����, ������ͨ��LinkedList�޸ĵõ����г�����ʵ�ֵ���ͬ
 *  
 */

template <typename T>
class LinkedList1 : public sky::List<T> {
public:
	// LinkedList() : len(0) { head = new Node; }
	LinkedList1() : len(0), first(NULL) {}
	LinkedList1(int sz, const T& x);
	//SeqList() : len(0), maxSize(0), data(NULL) {};       // Ĭ�Ϲ��캯��
	//SeqList(int sz);                                     // ָ������
	//SeqList(int sz, const T& x);                         // ��ʼ�����ȣ�ÿһԪ�ظ�ֵx
	
	LinkedList1(const LinkedList1<T>& x);                    // �������캯��
	LinkedList1<T>& operator=(const LinkedList1<T>& x);      // �����=����
	~LinkedList1() { removeAll(); }                                       // ��������
	//~SeqList() { delete[] data; }                       

	int  length() const { return len; }                  // ���ȣ�Ԫ�ظ�����
	// int  capacity() const { return maxSize; }         ��ȡ��������������Ҫ
	bool isEmpty() const { return len == 0; }            // ���Ƿ�Ϊ��
	bool isIncreasing() const;                           // �ж�������Ԫ���Ƿ����
	//bool isFull() const { return len == maxSize; }     �ж�����Ŀռ��Ƿ�װ���ķ���Ҳ������Ҫ
	bool getData(int i, T& x) const;                     // ��ȡiλ�ã���i+1��Ԫ�أ���ֵ��ͨ��x����
	int  search(const T& x) const;	                     // �ڱ��в���x���ҵ�������λ�ã�δ�ҵ�����-1
	void output() const;                                 // ���������
	
	bool setData(int i, const T& x);                     // ����iλ��Ԫ�ص�ֵΪx
	bool insert(int i, const T& x);                      // ��iλ�ò���һ��ֵx
	bool insertRear(const T& x);                         // ��ĩβ���룬�൱��STL vector��push_back()
	bool insertFront(const T& x);                        // ������ͷ����
	bool remove(int i, T& x);                            // ɾ��һ��Ԫ�أ�ɾ����Ԫ��ͨ��x����
	bool erase(int i);	                                 // ɾ��iλ��Ԫ�أ�������Ԫ��ֵ
	void clear() { removeAll(); }                                        // ��ձ�,����ɾ��ͷ���
	void reverse();                                      // ������
	
    bool operator==(const LinkedList1<T>& x) const;       // ����Node����Ϊ�ڲ��࣬��������ó�Ա������������Ԫ����������==
	bool operator!=(const LinkedList1<T>& x) const;
	//frined bool operator==(const LinkedList<T>& x, const LinkedList<T>& y);
	//frined bool operator!=(const LinkedList<T>& x, const LinkedList<T>& y);
	
	template <typename TT>
	friend std::ostream& operator<< (std::ostream& os, const LinkedList<TT>& x);
	
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
		 Node(const T& item = T(), Node* ptrNext = NULL) : data(item), next(ptrNext) {}
		 // �����������캯������������һ������
		 // Node(const T& item, Node* ptrNext = NULL) : data(item), next(ptrNext) {}
		 // Node(Node* ptrNext = NULL) : next(ptrNext) {}
	 };
		
	 // Node* head;
	 // ���ڲ���ͷ��㣬������first����head,��ʾ�����ǵ�һ���ڵ㣬������ͷ���
	 Node* first;
	                                           
	// int maxSize;  ˳����е�maxSize������Ҫ����Ϊ������������������ĸ���                                       
	int len;                                             // ����
	
	/*
	 *  init() ��ʼ������������0,first��NULL
	 */
	
	void init() {
		len = 0;
		first = NULL;
	}
	//void init() : len(0), first(NULL) {} ֻ�й��캯���ſ�������ʹ��
	
	
	//   	len = 0;
	//	    head = new Node;   ��ʼ��ʱ����Ҫ�����½ڵ�    
	//	    first = NULL;
	//}
	
	void removeAll();                                    // �����������ݽ�㼰ͷ���
};


/**
 *  removeAll()˽�з�����������нڵ�
 */
template <class T>
void LinkedList1<T>::removeAll() {
	// Node* p; ������Ϊp
	Node* p;
	
	while (first) {         
		p = first;
		first = first->next;
		delete p;
	}
	
	len = 0;
}

/**
 * @brief ���캯����N����ֵͬ��ɵ�����
 */
template <typename T>
LinkedList1<T>::LinkedList1(int sz, const T& x) : len(0), first(NULL) {
	if (sz > 0) {
		len = sz;
		
		// ��һ���ڵ��������Դ�
		first = new Node(x);
		sz--;
		
		// ��ͷ������sz���½ڵ�
		while (sz--) {
			Node* newNode = new Node(x, first->next);
			first->next = newNode;
		}
	}
}

/*
 *   �������캯��
 *   �����ʵ������Ҫ�ǲ�Ҫ����������ָ��ͬ�������ݣ�����һ����Ĳ�����Ӱ������һ����
 */
template <typename T>
LinkedList1<T>::LinkedList1(const LinkedList1<T>& x) {
	init();
	Node* p1 = x.first;
	
	// ���p1�ǿգ����ȿ���first�ڵ�
	if (p1) 
		first = new Node(p1->data);
	
	Node* p2 = first;
	p1 = p1->next;
		
	while (p1) {     // �����LinkedList��while (p1->next), �����Ϊwhile (p1)�� ��Ϊû��ͷ���
		p2->next = new Node(p1->data); 
		p1 = p1->next;
		p2 = p2->next;
	}
	
	len = x.len;
}

/*
 *  =���������
 */
template <typename T>
LinkedList1<T>& LinkedList1<T>::operator=(const LinkedList1<T>& x) {
	if (this != &x) {         // ��������Ƿ��Ը�ֵ����clear()���������ݶ�����ˣ�
		removeAll();
		Node* p1 = x.first;
		if (p1) 
			first = new Node(p1->data);
			
		Node* p2 = first;
		p1 = p1->next;
				
		while (p1) {     // �����LinkedList��while (p1->next), �����Ϊwhile (p1)�� ��Ϊû��ͷ���
			p2->next = new Node(p1->data); 
			p1 = p1->next;
			p2 = p2->next;
		}
			
		len = x.len;
	}

	return *this;
}

/**
 * @brief �ж�����Ԫ���Ƿ񣨷��ϸ񣩵������ձ�ֻ��һ��Ԫ�صı�������
 * 
 */
template <typename T>
bool LinkedList1<T>::isIncreasing() const {
    Node* p1 = first;
    Node* p2;
    
    // ���p1��ΪNULL,ȡp2Ϊ����
    if (p1) {
    	while (p1->next) {
    		p2 = p1->next;
    		if (p1->data > p2->data)  // ���ڱ��в鵽ǰ��Ԫ�ش��ں��Ԫ�أ��򷵻�false
    			return false;
    		else 
    			p1 = p2;
    	}
    }
    
    return true;             
}

/*
 *  getData(i, x)�õ���i������ֵ���ǵ��Ǵ�0��ʼ��������len-1�����
 *  ���ֵͨ��x���أ����i������Ҫ�󣬷���false, ��ȷȡ�ط���true
 */
template <typename T>
bool LinkedList1<T>::getData(int i, T& x) const {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len) 
		return false;
	
	// ������˵��iλ����ȷ
	Node* p = first;
	
	// ����i����������ã�����ֱ����i--,����Ҫ��һ������ı���j
	// ����i��λ�ã���ѭ�������꣬pָ��Ҫȡ�Ľ��ǰһλ��
	while (i--) {  
		p = p->next;
	}
	
	// x = p->next->data;
	x = p->data;           // ������ͷ�ڵ�������ֱ��ȡ��ǰ�ڵ��ֵ��������һ�ڵ�
	return true;
}

/*
 *  search(x) �ڱ��в���x,�ҵ�������λ�ã����򷵻�-1
 */
template <typename T>
int LinkedList1<T>::search(const T& x) const {
	int i = 0;
    Node* p = first;
    while (p) { 
    	if (p->data == x)
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
void LinkedList1<T>::output() const {
	Node* p = first;
	while (p) {
		std::cout << p->data;
		if (p->next) 
			std::cout << " ";
		p = p->next;
	}
}

/*
 *  setData(i, x)���õ�i���ڵ��ֵΪx
 *  ע����getData(i, x)������ʵ��ֻ��һ�䲻ͬ
 */
template <typename T>
bool LinkedList1<T>::setData(int i, const T& x) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len) 
		return false;
		
	// ������˵��iλ����ȷ
	Node* p = first;
		
	// ����i����������ã�����ֱ����i--,����Ҫ��һ������ı���j
	// ����i��λ�ã���ѭ�������꣬pָ��Ҫ�ı�Ľ��ǰһλ��
	while (i--) {  
		p = p->next;
	}
	
	p->data = x;   // ���getData(i, x)������ʵ�֣�ֻ��һ�䲻ͬ��
	return true;
}

/**
 *  @brief   ��һ����λ�ò���ֵ
 *  @param i �����λ�ã���0��ʼ
 *  @param x Ҫ�����ֵ
 *  @return  ��ȷ���뷵��true�����򷵻�false
 */
template <typename T>
bool LinkedList1<T>::insert(int i, const T& x) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len) 
		return false;
			
	// ������˵��iλ����ȷ
	Node* p1 = first;
	Node* p2 = p1;
	// ����i��λ�ã���ѭ�������꣬pָ��Ҫ����Ľ��ǰһλ��
	while (i--) {
		p2 = p1;
		p1 = p1->next;
	}
	
	// �˴������ж�first�ڵ��Ƿ�Ϊ�գ�����first�ڵ�֮ǰ���룬�������first�ڵ�
	Node* newNode = new Node(x);
	
	if (!first) {
		first = newNode;
	}
	else if (i == 0) {
		newNode->next = first;
		first = newNode;
	}
	else {
	    newNode->next = p1;
	    p2->next = newNode;
	    
	}
	
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
bool LinkedList1<T>::insertRear(const T& x) {
	Node*  newNode = new Node(x);
	
	if (newNode) {
		if (!first) {
			first = newNode;
		}
		else {
			Node* p = first;
			
			while (p->next) {
				p = p->next;
			}
			
			p->next = newNode;
		}
		
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
bool LinkedList1<T>::insertFront(const T& x) {
	// �����½ڵ�
	Node* newNode = new Node(x, first);
	
	if (newNode) {
		first = newNode;
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
bool LinkedList1<T>::remove(int i, T& x) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len)
		return false;
	
	Node* p1 = first;
	Node* p2 = p1;
	
	if (i == 0) {
		x = first->data;
		first = first->next;
	}
	else {
		// ����i��λ�ã���ѭ�������꣬pָ��Ҫ����Ľ��ǰһλ��
		while (i--) {
			p2 = p1;
			p1 = p1->next;
		}
		
		x = p1->data;
		p2->next = p1->next;		
	}
	
	delete p1;	
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
bool LinkedList1<T>::erase(int i) {
	// ���λ�ò���i������Ҫ��ֱ�ӷ���false
	if (i < 0 || i >= len)
		return false;
	
	Node* p1 = first;
	Node* p2 = p1;
		
	if (i == 0) {
		    first = first->next;
	}
	else {
		// ����i��λ�ã���ѭ�������꣬p2ָ��Ҫ����Ľ��ǰһλ��
		while (i--) {
			p2 = p1;
			p1 = p1->next;
		}
			
		p2->next = p1->next;		
	}
		
	delete p1;	
	len--;
	return true;
}

/**
 * @brief ������,������˼����ϰ
 *  
 */
template <typename T>
void LinkedList1<T>::reverse() {
	
	Node* p1 = NULL;
	Node* p2 = first;
	Node* p3;
	
	while (p2) {
		p3 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
	
	first = p1;
}


/**
 * @brief ==��������أ��ж��������Ա��Ƿ����
 */
template <typename T>
bool LinkedList1<T>::operator==(const LinkedList1<T>& x) const {
	if (len == x.len) {
		Node* p1  = first;
		Node* p2  = x.first;
		while (p1) {
			if (p1->data != p2->data)
				return false;
			p1 = p1->next;
			p2 = p2->next;
		}
		return true;     // ���������ȣ�����ÿ��Ԫ������ͬ������˳������
	}
	else {
		return false;
	}
}

/**
 * @brief !=��������أ��ж��������Ա��Ƿ����
 */
template <typename T>
bool LinkedList1<T>::operator!=(const LinkedList1<T>& x) const {
	return !(this == x);
}

/**
 * @brief ���������<<��ʹ�ÿ��Է��������������Ա�
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList1<T>& x){
    out << "(";
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


}  // namespace sky 

#endif /* _SKY_LINKED_LIST1_H */
