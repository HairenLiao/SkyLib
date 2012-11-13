/** @file   sky_seq_deque.h 
 *  @brief  Array-based Deque Implentation 
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
 *  ���ݽṹ���㷨���������������д���൱���ע�ͺ�˵���������������������������������ʹ�ã������߲�Ϊ�����
 *  ��ȷ�Լ���ʹ�����κε���������ʹ�ô˿������ҵʱ����Ϊ��Ϯ�� ͬʱ����Ҳ�ǳ������������ַ����͸Ľ������
 *  
 */

// ˫�˶���,��������ʵ��

#ifndef _SKY_SEQ_DEQUE_H
#define _SKY_SEQ_DEQUE_H 1
#include "sky_deque.h"

namespace sky {

/** SeqDeque
 *  ˳��˫�˶���
 *  �ر�Ӧע��pushFront(), popRear(), getRear()��������Щ�ǵ��˶���û�е�
 */
template <typename T>
class SeqDeque : public sky::Deque<T> {
public:
	SeqDeque(int sz = DEFAULT_MAX_DEQUE_SIZE) : front(0), rear(0), len(0) {
		maxSize = (sz <= 0) ? DEFAULT_MAX_DEQUE_SIZE : sz;
		elem = new T[maxSize];
	}
	SeqDeque(const SeqDeque& x);
	SeqDeque& operator=(const SeqDeque& x);
	~SeqDeque() { delete[] elem; }
	
	bool isEmpty() const { return len == 0; }             
	bool isFull()  const { return len == maxSize; }
	int  length() const { return len;  }
	bool pushFront(const T& x);    
	bool pushRear(const T& x);
	bool popFront(T& x);
	bool popRear(T& x);                             
	bool getFront(T& x) const;                          
	bool getRear(T& x) const;             
    void clear() { front = rear = len = 0; }
    void output() const;
    template <typename TT>
    friend std::ostream& operator<< (std::ostream& os, const SeqDeque<TT>& x);
private:
	T*  elem;
	int front, rear;      
	int len;  
	int maxSize;
};


/**
 * @brief �������캯��
 */
template <typename T>
SeqDeque<T>::SeqDeque(const SeqDeque<T>& x) {
	len = x.len;
	maxSize = x.maxSize;
	front = x.front;
	rear = x.rear;
	elem = new T[maxSize];
	
	int i = front;
	// ����len��Ԫ��
	for (int num = 0; num < len; num++) {
		elem[i] = x.elem[i];
		i = (i + 1) % maxSize;	
	}
}

/**
 * @brief =���������
 */
template <typename T>
SeqDeque<T>& SeqDeque<T>::operator =(const SeqDeque<T>& x) {
	if (this != &x) {
		delete[] elem;
		len = x.len;
		maxSize = x.maxSize;
		front = x.front;
		rear = x.rear;
		elem = new T[maxSize];
			
		int i = front;
		// ����len��Ԫ��
		for (int num = 0; num < len; num++) {
			elem[i] = x.elem[i];
			i = (i + 1) % maxSize;	
		}
	}
	
	return *this;
}

/**
 * @brief ��˫�˶��е�ͷ����,��������������false���������Ԫ�أ�����true
 * 
 */
template <typename T>
bool SeqDeque<T>::pushFront(const T& x) {
	if (isFull())
		return false;
	front = (front + maxSize - 1) % maxSize;        // �൱��ѭ��front--
	elem[front] = x;                                // front�����Ƕ�ͷ��һ������Ԫ�أ����������Լ�����룬��Ϊrear���ܸı�
	len++;
	return true;
}

/**
 * @brief ��˫�˶��е�β����,�����벻�ɹ�������false�����򷵻�true
 * 
 */
template <typename T>
bool SeqDeque<T>::pushRear(const T& x) {
	if (isFull())
		return false;
	elem[rear] = x;                     // rear�Ƕ��е�һ���ɲ���Ŀ�λ
	rear = (rear + 1) % maxSize;        // �൱��ѭ��rear++
	len++;
	return true;
}

/**
 * @brief Ԫ�س�����ͷ��������пգ�����false, ���򷵻�true
 */
template <typename T>
bool SeqDeque<T>::popFront(T& x) {
	if (isEmpty())
		return false;
	x = elem[front];
	front = (front + 1) % maxSize;
	len--;
	return true;	
}

/**
 * @brief Ԫ�س�����β��������пգ�����false, ���򷵻�true
 */
template <typename T>
bool SeqDeque<T>::popRear(T& x) {
	if (isEmpty())
		return false;	
	rear = (rear + maxSize - 1) % maxSize;           // loop rear--
	x = elem[rear];
	len--;
	return true;	
}

/**
 * @brief ��ȡͷԪ��,ֻ��Ԫ�ظ�������
 */
template <typename T>
bool SeqDeque<T>::getFront(T& x) const {
	if (isEmpty())
		return false;
	x = elem[front];
	return true;
}

/**
 * @brief ��ȡβԪ��,ֻ��Ԫ�ظ�������
 */
template <typename T>
bool SeqDeque<T>::getRear(T& x) const {
	if (isEmpty())
		return false;
	// ���зǿգ���ȡͷԪ��
	//x = elem[rear];  rear�ǿ�λ�� , --rear���Ƕ�βԪ�ص�ַ��
	x = elem[(rear + maxSize - 1) % maxSize];
	return true;
}

/**
 * @brief ��ӡ����Ԫ��
 */
template <typename T>
void SeqDeque<T>::output() const {
	std::cout << "[front--> ";
	
	int i = front;
	for (int num = 0; num < len; num++) {
		std::cout << elem[i] << " ";
		i = (i + 1) % maxSize;	
	}
	
	std::cout << "<--rear]" << std::endl;
}

/**
 * @brief �����<<����
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const SeqDeque<T>& x) {
	os << "[front--> ";
	
	int i = x.front;
	for (int num = 0; num < x.len; num++) {
		std::cout << x.elem[i] << " ";
		i = (i + 1) % x.maxSize;	
	}
			
	os << "<--rear]";	
}

}  // namespace sky 

#endif /* _SKY_SEQ_DEQUE_H */
