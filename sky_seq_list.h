/** 
 *  @file   sky_seq_list.h 
 *  @brief  Implementation of Seqential Linear List     
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
 *  SeqList
 *  ˳������Ա��������Ĵ洢��ʾ˳���
 */

#ifndef _SKY_SEQ_LIST_H
#define _SKY_SEQ_LIST_H  1

#include <iostream>
#include "sky_list.h"

namespace sky {

/* �ܶ�̿����ʵ�ֶ�����һ����������ı�������ʼ����ʱ������(maxSize)��ֵ��������ʵ��ʹ�����Ա���ԭʼ������
 * ���������Ա��Ƿ���Ԫ�أ����������������˴�Ŀռ䡣 �������STL vector��ʵ�֣���ʼ����Ϊ0
 */
// const int DEFAULT_MAX_LIST_SIZE = 10;

template <typename T>
class SeqList: public sky::List<T> {
public:
	SeqList() : len(0), maxSize(0), data(NULL) {};       // Ĭ�Ϲ��캯��
	SeqList(int sz);                                     // ָ������
	SeqList(int sz, const T& x);                         // ��ʼ�����ȣ�ÿһԪ�ظ�ֵx
	SeqList(const SeqList<T>& x);                        // �������캯��
	SeqList<T>& operator=(const SeqList<T>& x);          // �����=����
	~SeqList() { delete[] data; }                        // ��������

	int  length() const { return len; }                  // ���ȣ�Ԫ�ظ�����
	int  capacity() const { return maxSize; }            // ��������Ŀǰ����Ŀռ��С�� 
	bool isEmpty() const { return len == 0; }            // ���Ƿ�Ϊ��
	bool isFull() const { return len == maxSize; }       // Ŀǰ����Ŀռ��Ƿ�װ��
	bool getData(int i, T& x) const;                     // ��ȡiλ�ã���i+1��Ԫ�أ���ֵ��ͨ��x����
	int  search(const T& x) const;	                     // �ڱ��в���x���ҵ�������λ�ã�δ�ҵ�����-1
	void output() const;                                 // �����
	
	bool setData(int i, const T& x);                     // ����iλ��Ԫ�ص�ֵΪx
	bool insert(int i, const T& x);                      // ��iλ�ò���һ��ֵx
	bool insertRear(const T& x);                         // ��ĩβ���룬�൱��STL vector��push_back()
	bool remove(int i, T& x);                            // ɾ��һ��Ԫ�أ�ɾ����Ԫ��ͨ��x����
	bool erase(int i);	                                 // ɾ��iλ��Ԫ�أ�������Ԫ��ֵ
	void clear();                                        // ��ձ�
	bool reserve(int newCapacity);                       // Ԥ�������������STL vector��reserve()����
	bool resize(int newSize);                            // �ı����
	T& operator[](int i);                                // ��ȡiλ��Ԫ������
	const T& operator[](int i) const;                    // ���������ȡiλ��Ԫ������
	
private:
	T* data;                                             // �������ݴ�ŵ�ַ
	int maxSize;                                         // ����������������Ϊcapacity,����������capacity��������ʹ��maxSize
	int len;                                             // ����
	bool expandCapacity();                               // ���ݣ�ͨ����len����maxSize��������Ҫ�����µ�Ԫ��ʹʹ��
};

/*
 *  @brief ��չ����
 */
template <typename T>
bool SeqList<T>::expandCapacity() {
	int oldLen = len;
	maxSize = (oldLen != 0) ? 2 * oldLen : 1;            // STL vector��ʹ�õ����ݷ�ʽ
	T* newData = new T[maxSize];
	if (newData == NULL)
		return false;
	// ����������
	for (int i = 0; i < len; ++i) {
		newData[i] = data[i];
	}
	
	delete[] data;                                      //  ���ԭ���ݿռ�
	data = newData;
	return true;
}

/**
 * @brief ���캯��
 * @param sz �ռ��С
 */
template <typename T>
SeqList<T>::SeqList(int sz) : len(0), maxSize(0), data(NULL) {
	if (sz > 0) {
		len = maxSize = sz;
	    data = new T[maxSize];
	}
}

/**
 * @brief ���캯��
 * @param sz �ռ䡢������С
 * @param x ���Կռ�Ԫ�س�ʼ��Ϊ��ֵ
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
 * @brief �������캯��
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
 * @brief =���������
 */
template <typename T>
SeqList<T>& SeqList<T>::operator=(const SeqList<T>& x) {
	if (this != &x) {
		delete[] data;                               // ���ԭ���ݣ�����Ҫ��������ܲ����ڴ�й¶
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
 *  @brief �õ���i��Ԫ�أ��ǵ��Ǵ�0��ʼ����
 *  @param i Ԫ��λ�ã���0��ʼ����
 *  @param x ��i���ڵ��ֵ
 *  @return ���i������Ҫ�󣬷���false, ��ȷȡ�ط���true
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
 * @brief �ڱ��в���x,�ҵ�������λ�ã����򷵻�-1
 * @param x �����ҵ�Ԫ��ֵ
 * @return �ҵ�������λ�ã����򷵻�-1
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
 * @brief ������������������<<��ʹ�ÿ��Է��������������Ա�
 */
template <typename T>
void SeqList<T>::output() const {
    for (int i = 0; i < len; ++i) {
    	std::cout << data[i] << " ";
    }
}

/**
 * @brief �����[]����
 */
template <typename T>
inline T& SeqList<T>::operator[](int i) {
	return data[i];
}

/**
 * @brief �����[]���أ�const����
 */
template <typename T>
inline const T& SeqList<T>::operator[](int i) const {
	return data[i];
}

/**
 * @brief ���õ�i���ڵ��ֵ
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
 * @brief ����Ԫ��
 * ע��˷�����Ҫ���ռ��Ƿ��㹻������Ԫ��
 */

template <typename T>
bool SeqList<T>::insert(int i, const T& x) {
    // ���i����0~(len-1)��Χ�ڣ���������������false,��ʾδ����ɹ�
    // ע������Ļ�������i>=len,������i>len����Ϊ��Ҫ��len�����룬����ʹ��insertRear()����
    if (i < 0 || i >= len) 
    	return false;
    // �������㣬��Ҫ���롣�ȼ���Ƿ��������Ѿ���������Ҫ�����ռ䣬���ҿ�����Ԫ��
    if (isFull()) {
    	//  �������δ�ɹ�������false
    	if (!expandCapacity()) 
    		return false;
    }
    // ������iλ�ú�Ԫ�����Ų��һ��λ�ã�Ϊ�˲�ʹ��������Ԫ�أ���len-1λ�ÿ�ʼ�����
    for (int j = len-1; j >= i; j--) {
	    data[j+1] = data[j];
    }
    data[i] = x;
	return true;
}

/**
 * @brief �����Ա�ĩβ����Ԫ�� 
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
 * @brief ɾ����i��Ԫ�أ�ͨ��x����
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
 * @brief ֱ��ɾ����i��Ԫ�أ�������ֵ
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
 * @brief ��ձ�
 */
template <typename T>
void SeqList<T>::clear() {
	delete[] data;
	len = maxSize = 0;
}

/**
 * @brief �ı������Ĵ�С
 *        ���������С�ھ����������߷����¿ռ�ʧ�ܣ�����false
 */ 
template <typename T>
bool SeqList<T>::reserve(int newCapacity) {
	
	if (newCapacity <= maxSize) 
		return false;
	
	maxSize = newCapacity;
	T* oldData = data;
	data = new T[maxSize];
	if (data == NULL) {
		data = oldData;       // �ָ������ݣ�����false
		return false;
	}
	
	// ����������
	for (int i = 0; i < len; ++i) {
		data[i] = oldData[i];
	}
			
	delete[] oldData;         // ���ԭ���ݿռ�
	return true;
}

/**
 *  @brief �ı���ȣ��ռ䲻��ʱ����
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
 * @brief ���������<<��ʹ�ÿ��Է��������������Ա�
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const SeqList<T>& x){
    out << "( ";
    x.output();
    out << ")";
    return out;
}

/**
 * @brief ==��������أ��ж�����˳����Ƿ����
 */
template <typename T>
bool operator==(const SeqList<T>& x, const SeqList<T>& y) {
	if (x.length() == y.length()) {
		for (int i = 0; i < x.length(); ++i) {
			if (x[i] != y[i])
				return false;
		}
		return true;     // ���������ȣ�����ÿ��Ԫ������ͬ������˳������
	}
	else {
		return false;
	}
}

/**
 * @brief !=��������أ��ж�����˳����Ƿ񲻵ȣ�����==ʵ��
 */
template <typename T>
inline bool operator!=(const SeqList<T>& x, const SeqList<T>& y) {
	return !(x == y);
}

}  // namespace sky

#endif   /*  _SKY_SEQ_LIST_H  */
