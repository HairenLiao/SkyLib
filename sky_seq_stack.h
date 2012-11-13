/** @file   sky_seq_stack.h 
 *  @brief  Array-based Stack Implentation 
 *  @author Hairen Liao(廖海仁） <liaohairen@gmail.com>
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
 *  本库为作者本人学习数据结构与算法所写，模拟STL标准库，并力求得其精神，不拘其细节。 同时也希望本库对其他初学
 *  数据结构与算法者有所帮助，因此写了相当多的注释和说明。本库属于自由软件，您基本可以自由使用，但作者不为本库的
 *  正确性及其使用做任何担保，包括使用此库完成作业时被视为抄袭。 同时作者也非常乐于听到您的反馈和改进意见。
 *  
 */

// 顺序栈

#ifndef _SKY_SEQ_STACK_H
#define _SKY_SEQ_STACK_H  1

#include <iostream>
#include <cassert>
#include "sky_stack.h"

namespace sky {

/** SeqStack 
 *  基于数组的栈，不自动扩容，可产生溢出；初始化时可指定最大栈空间
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
	bool push(const T& x);                        // 元素入栈
	bool pop(T& x);                               // 元素出栈
	bool getTop(T& x) const;                            // 返回栈顶元素，但是不将元素从栈中
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
 * @brief 构造函数
 *        若提供的默认size值小于等于0，空间大小也会被设置为默认大小
 */
template <typename T>
SeqStack<T>::SeqStack(int sz) : top(-1) {
	maxSize = (sz <= 0) ? DEFAULT_MAX_STACK_SIZE : sz;	
	elem = new T[maxSize];	
	assert(elem != NULL);
}

/**
 * @brief 拷贝构造函数
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
 * @brief =运算符重载
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
 * @brief 元素入栈，如果栈满，返回false，否则元素入栈，返回true
 *        一般库用void push(x)的定义，这里使用bool类型返回值以便于在栈满时返回false
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
 * @brief 元素出栈，如果栈空，返回false，否则元素出栈，返回true
 *        一般库的设计是 T pop(), 但是对于sky库这种不提供出错处理的库，这里难以处理栈空的情况
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
 * @brief 获取栈顶元素，除了top不减1外与pop完全相同
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
 * @brief output()输出栈内容，并标识栈顶
 */
template <typename T>
void SeqStack<T>::output() const {
	std::cout << "[";
	for (int i = 0; i <= top; i++)
		std::cout << elem[i] << " ";
	std::cout << "<--top]" << std::endl;
}

/**
 * <<输出重载,不标识栈顶
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
