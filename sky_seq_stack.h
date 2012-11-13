/** @file   sky_seq_stack.h 
 *  @brief  Array-based Stack Implentation 
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

// ˳��ջ

#ifndef _SKY_SEQ_STACK_H
#define _SKY_SEQ_STACK_H  1

#include <iostream>
#include <cassert>
#include "sky_stack.h"

namespace sky {

/** SeqStack 
 *  ���������ջ�����Զ����ݣ��ɲ����������ʼ��ʱ��ָ�����ջ�ռ�
 */
template <typename T>
class SeqStack : public sky::Stack<T> {
public:
	SeqStack(int sz = DEFAULT_MAX_STACK_SIZE);
	SeqStack(const SeqStack& x);
	SeqStack& operator=(const SeqStack& x);
	~SeqStack() { delete[] elem; }
	
	bool isEmpty() const { return top == -1; }               
	bool isFull()  const { return top == (maxSize - 1);  } 
	int  length() const { return top + 1;  }
	bool push(const T& x);                        // Ԫ����ջ
	bool pop(T& x);                               // Ԫ�س�ջ
	bool getTop(T& x) const;                            // ����ջ��Ԫ�أ����ǲ���Ԫ�ش�ջ��
    void clear() { top = -1; }    
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const SeqStack<TT>& x);
private:
	T*  elem;
	int top;
	int maxSize;
};

/**
 * @brief ���캯��
 *        ���ṩ��Ĭ��sizeֵС�ڵ���0���ռ��СҲ�ᱻ����ΪĬ�ϴ�С
 */
template <typename T>
SeqStack<T>::SeqStack(int sz) : top(-1) {
	maxSize = (sz <= 0) ? DEFAULT_MAX_STACK_SIZE : sz;	
	elem = new T[maxSize];	
	assert(elem != NULL);
}

/**
 * @brief �������캯��
 */
template <typename T>
SeqStack<T>::SeqStack(const SeqStack<T>& x) {
	maxSize = x.maxSize;
	elem = new T[maxSize];
	top = x.top;
	for (int i = 0; i <= top; i++) {
		elem[i] = x.elem[i];
	}
}

/**
 * @brief =���������
 */
template <typename T>
SeqStack<T>& SeqStack<T>::operator =(const SeqStack<T>& x) {
	if (this != &x) {
		delete[] elem;
		maxSize = x.maxSize;
		elem = new T[maxSize];
		top = x.top;
		for (int i = 0; i <= top; i++) {
			elem[i] = x.elem[i];
		}	
	}
	return *this;
}
/**
 * @brief Ԫ����ջ�����ջ��������false������Ԫ����ջ������true
 *        һ�����void push(x)�Ķ��壬����ʹ��bool���ͷ���ֵ�Ա�����ջ��ʱ����false
 * 
 */
template <typename T>
bool SeqStack<T>::push(const T& x) {
	if (isFull()) 
		return false;
	else {
		elem[++top] = x;
		return true;
	}		
}

/**
 * @brief Ԫ�س�ջ�����ջ�գ�����false������Ԫ�س�ջ������true
 *        һ��������� T pop(), ���Ƕ���sky�����ֲ��ṩ������Ŀ⣬�������Դ���ջ�յ����
 * 
 */
template <typename T>
bool SeqStack<T>::pop(T& x) {
	if (isEmpty())
		return false;
	else {
		x = elem[top--];
		return true;
	}
}

/**
 * @brief ��ȡջ��Ԫ�أ�����top����1����pop��ȫ��ͬ
 */
template <typename T>
bool SeqStack<T>::getTop(T& x) const {
	if (isEmpty())
		return false;
	else {
		x = elem[top];    
		return true;
	}
}

/**
 * @brief output()���ջ���ݣ�����ʶջ��
 */
template <typename T>
void SeqStack<T>::output() const {
	std::cout << "[";
	for (int i = 0; i <= top; i++)
		std::cout << elem[i] << " ";
	std::cout << "<--top]" << std::endl;
}

/**
 * <<�������,����ʶջ��
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const SeqStack<T>& x) {
	os << "[";
	for (int i = 0; i <= x.top; i++)
		os << " " << x.elem[i];
	os << " ]";
	
}

}  // namespace sky 

#endif /* _SKY_SEQ_STACK_H */
