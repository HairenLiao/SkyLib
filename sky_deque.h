/** @file   sky_deque.h 
 *  @brief  Inteface of all deques 
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

// ˫�˶��еĽӿ�

#ifndef _SKY_DEQUE_H
#define _SKY_DEQUE_H  1

namespace sky {

const int DEFAULT_MAX_DEQUE_SIZE = 100;

/** Deque 
 *  ΪSeqDeque��LinkedDeque�Ⱦ���˫�˶��е�ʵ��ʹ��
 */
template <typename T>
class Deque {
	virtual bool pushFront(const T& x) = 0;    
	virtual bool pushRear(const T& x)  = 0; 
	virtual bool popFront(T& x)        = 0;  
	virtual bool popRear(T& x)         = 0;
	virtual void clear()               = 0;
	
	virtual bool getFront(T& x) const  = 0;                   
	virtual bool getRear(T& x)  const  = 0;
    virtual bool isEmpty()      const  = 0;                   
    virtual bool isFull()       const  = 0;                   
    virtual int  length()       const  = 0;              
};

}  // namespace sky 

#endif /* _SKY_DEQUE_H */
