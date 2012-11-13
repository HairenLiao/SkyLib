/** 
 *  @file   sky_seq_list.h 
 *  @brief  Implementation of Seqential Linear List     
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

/** 
 *  SeqList
 *  顺序表：线性表基于数组的存储表示顺序表
 */

#ifndef _SKY_SEQ_LIST_H
#define _SKY_SEQ_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/* 很多教科书的实现都定义一个类似下面的变量，初始化表时给容量(maxSize)赋值，但这种实现使得线性表有原始开销：
 * 即不管线性表是否有元素，都必须分配至少如此大的空间。 这里仿照STL vector的实现，初始容量为0
 */
// const int DEFAULT_MAX_LIST_SIZE = 10;

template <typename T>
class SeqList: public sky::List<T> {
public:
	SeqList() : len(0), maxSize(0), data(NULL) {};       // 默认构造函数
	SeqList(int sz);                                     // 指定表长度
	SeqList(int sz, const T& x);                         // 初始化表长度，每一元素赋值x
	SeqList(const SeqList<T>& x);                        // 拷贝构造函数
	SeqList<T>& operator=(const SeqList<T>& x);          // 运算符=重载
	~SeqList() { delete[] data; }                        // 析构函数

	int  length() const { return len; }                  // 表长度（元素个数）
	int  capacity() const { return maxSize; }            // 表容量（目前分配的空间大小） 
	bool isEmpty() const { return len == 0; }            // 表是否为空
	bool isFull() const { return len == maxSize; }       // 目前分配的空间是否装满
	bool getData(int i, T& x) const;                     // 获取i位置（第i+1个元素）的值，通过x返回
	int  search(const T& x) const;	                     // 在表中查找x，找到返回其位置，未找到返回-1
	void output() const;                                 // 输出表
	
	bool setData(int i, const T& x);                     // 设置i位置元素的值为x
	bool insert(int i, const T& x);                      // 在i位置插入一个值x
	bool insertRear(const T& x);                         // 从末尾插入，相当于STL vector的push_back()
	bool remove(int i, T& x);                            // 删除一个元素，删除的元素通过x返回
	bool erase(int i);	                                 // 删除i位置元素，不返回元素值
	void clear();                                        // 清空表
	bool reserve(int newCapacity);                       // 预设表容量，仿照STL vector的reserve()方法
	bool resize(int newSize);                            // 改变表长度
	T& operator[](int i);                                // 获取i位置元素引用
	const T& operator[](int i) const;                    // 常函数版获取i位置元素引用
	
private:
	T* data;                                             // 真正数据存放地址
	int maxSize;                                         // 容量，本来想命名为capacity,但是由于有capacity方法，故使用maxSize
	int len;                                             // 表长度
	bool expandCapacity();                               // 扩容，通常在len等于maxSize，而又需要插入新的元素使使用
};

/*
 *  @brief 扩展容量
 */
template <typename T>
bool SeqList<T>::expandCapacity() {
	int oldLen = len;
	maxSize = (oldLen != 0) ? 2 * oldLen : 1;            // STL vector中使用的扩容方式
	T* newData = new T[maxSize];
	if (newData == NULL)
		return false;
	// 拷贝旧数据
	for (int i = 0; i < len; ++i) {
		newData[i] = data[i];
	}
	
	delete[] data;                                      //  清除原数据空间
	data = newData;
	return true;
}

/**
 * @brief 构造函数
 * @param sz 空间大小
 */
template <typename T>
SeqList<T>::SeqList(int sz) : len(0), maxSize(0), data(NULL) {
	if (sz > 0) {
		len = maxSize = sz;
	    data = new T[maxSize];
	}
}

/**
 * @brief 构造函数
 * @param sz 空间、容量大小
 * @param x 所以空间元素初始化为此值
 */
template <typename T>
SeqList<T>::SeqList(int sz, const T& x) : len(0), maxSize(0), data(NULL) {
	if (sz > 0) {
		len = maxSize = sz;
	    data = new T[maxSize];
	    for (int i = 0; i < len; ++i) {
	    	data[i] = x;
	    }	
	}
}

/**
 * @brief 拷贝构造函数
 */
template <typename T>
SeqList<T>::SeqList(const SeqList& x) {
	maxSize = x.maxSize;
	len = x.len;
	data = new T[maxSize];
	for (int i = 0; i < len; ++i) {
		data[i] = x.data[i];
	}
}

/**
 * @brief =运算符重载
 */
template <typename T>
SeqList<T>& SeqList<T>::operator=(const SeqList<T>& x) {
	if (this != &x) {
		delete[] data;                               // 清除原数据，很重要，否则可能产生内存泄露
		maxSize = x.maxSize;
		len = x.len;
		data = new T[maxSize];
		for (int i = 0; i < len; ++i) {
			data[i] = x.data[i];
		}
	}
	return *this;
}

/**
 *  @brief 得到第i个元素，记得是从0开始计数
 *  @param i 元素位置，从0开始计数
 *  @param x 第i个节点的值
 *  @return 如果i不满足要求，返回false, 正确取回返回true
 */
template <typename T>
bool SeqList<T>::getData(int i, T& x) const {
	if (i >= 0 && i < len) {
		x = data[i];
		return true;
	}
	return false;
}

/**
 * @brief 在表中查找x,找到返回其位置，否则返回-1
 * @param x 待查找的元素值
 * @return 找到返回其位置，否则返回-1
 */
template <typename T>
int SeqList<T>::search(const T& x) const {
	for (int i = 0; i < len; ++i) {
		if (data[i] == x) 
			return i;
	}
	return -1;
}

/**
 * @brief 输出表内容重载运算符<<，使得可以方便地输出整个线性表
 */
template <typename T>
void SeqList<T>::output() const {
    for (int i = 0; i < len; ++i) {
    	std::cout << data[i] << " ";
    }
}

/**
 * @brief 运算符[]重载
 */
template <typename T>
inline T& SeqList<T>::operator[](int i) {
	return data[i];
}

/**
 * @brief 运算符[]重载，const函数
 */
template <typename T>
inline const T& SeqList<T>::operator[](int i) const {
	return data[i];
}

/**
 * @brief 设置第i个节点的值
 */
template <typename T>
bool SeqList<T>::setData(int i, const T& x) {
	if (i >= 0 && i < len) {
		data[i] = x;
		return true;
	}
	return false;
}

/**
 * @brief 插入元素
 * 注意此方法需要检查空间是否足够插入新元素
 */

template <typename T>
bool SeqList<T>::insert(int i, const T& x) {
    // 如果i不在0~(len-1)范围内，则不做操作，返回false,表示未插入成功
    // 注意这里的或条件是i>=len,而不是i>len，因为若要在len处插入，可以使用insertRear()方法
    if (i < 0 || i >= len) 
    	return false;
    // 条件满足，需要插入。先检查是否满，若已经满，则需要新增空间，并且拷贝旧元素
    if (isFull()) {
    	//  如果扩容未成功，返回false
    	if (!expandCapacity()) 
    		return false;
    }
    // 将所有i位置后元素向后挪动一个位置，为了不使覆盖有用元素，从len-1位置开始向后移
    for (int j = len-1; j >= i; j--) {
	    data[j+1] = data[j];
    }
    data[i] = x;
	return true;
}

/**
 * @brief 在线性表末尾插入元素 
 */
template <typename T>
bool SeqList<T>::insertRear(const T& x) {
	if (isFull()) {
		if (!expandCapacity())
			return false;
	}
	data[len] = x;
	len++;
	return true;
}

/**
 * @brief 删除第i个元素，通过x返回
 */
template <typename T>
bool SeqList<T>::remove(int i, T& x) {
	if (i < 0 || i >= len)
		return false;
	x = data[i];
	for (int j = i; j < len - 1; ++j) {
		data[j] = data[j+1];
	}
	len--;
	return true;
}

/**
 * @brief 直接删除第i个元素，不返回值
 */
template <typename T>
bool SeqList<T>::erase(int i) {
	if (i < 0 || i >= len)
		return false;
	for (int j = i; j < len-1; ++j) {
		data[j] = data[j+1];
	}
	len--;
	return true;
}

/**
 * @brief 清空表
 */
template <typename T>
void SeqList<T>::clear() {
	delete[] data;
	len = maxSize = 0;
}

/**
 * @brief 改变容量的大小
 *        如果新容量小于旧容量，或者分配新空间失败，返回false
 */ 
template <typename T>
bool SeqList<T>::reserve(int newCapacity) {
	
	if (newCapacity <= maxSize) 
		return false;
	
	maxSize = newCapacity;
	T* oldData = data;
	data = new T[maxSize];
	if (data == NULL) {
		data = oldData;       // 恢复旧数据，返回false
		return false;
	}
	
	// 拷贝旧数据
	for (int i = 0; i < len; ++i) {
		data[i] = oldData[i];
	}
			
	delete[] oldData;         // 清除原数据空间
	return true;
}

/**
 *  @brief 改变表长度，空间不够时扩容
 */
template <typename T>
bool SeqList<T>::resize(int newSize) {
	if (newSize > maxSize) {
		if (!reserve(newSize))
			return false;
	}
	len = newSize;
	return true;
}

/**
 * @brief 重载运算符<<，使得可以方便地输出整个线性表
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const SeqList<T>& x){
    out << "( ";
    x.output();
    out << ")";
    return out;
}

/**
 * @brief ==运算符重载，判断两个顺序表是否相等
 */
template <typename T>
bool operator==(const SeqList<T>& x, const SeqList<T>& y) {
	if (x.length() == y.length()) {
		for (int i = 0; i < x.length(); ++i) {
			if (x[i] != y[i])
				return false;
		}
		return true;     // 如果长度相等，而且每个元素又相同，则两顺序表相等
	}
	else {
		return false;
	}
}

/**
 * @brief !=运算符重载，判断两个顺序表是否不等，利用==实现
 */
template <typename T>
inline bool operator!=(const SeqList<T>& x, const SeqList<T>& y) {
	return !(x == y);
}

}  // namespace sky

#endif   /*  _SKY_SEQ_LIST_H  */
