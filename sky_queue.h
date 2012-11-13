/** @file   sky_queue.h 
 *  @brief  Inteface of all queues   
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

// ���еĽӿ�

#ifndef _SKY_QUEUE_H
#define _SKY_QUEUE_H  1

namespace sky {

const int DEFAULT_MAX_QUEUE_SIZE = 100;

/** Queue 
 *  ΪSeqQueue��LinkedQueue�Ⱦ���ջ��ʵ��ʹ��
 */
template <typename T>
class Queue {
	virtual bool enQueue(const T& x) = 0;                   // �����
	virtual bool deQueue(T& x)       = 0;                   // ������
	virtual bool getFront(T& x) const = 0;                   // ��ȡ����ͷ��ֵ
    virtual bool isEmpty()  const    = 0;                   // �ж������Ƿ�Ϊ��
    virtual bool isFull()   const    = 0;                   // �����Ƿ�������enqueue����������
    virtual int  length()   const    = 0;
    virtual void clear()             = 0;                   // ��ն���
};

}  // namespace sky 

#endif /* _SKY_QUEUE_H */
