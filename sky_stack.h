/** @file   sky_stack.h 
 *  @brief  Inteface of all stacks   
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

// ջ�Ľӿ�

#ifndef _SKY_STACK_H
#define _SKY_STACK_H  1

namespace sky {

const int DEFAULT_MAX_STACK_SIZE = 100;

/** Stack 
 *  ΪSeqStack��LinkedStack�Ⱦ���ջ��ʵ��ʹ��
 */
template <typename T>
class Stack {
	virtual bool push(const T& x)   = 0;  
	virtual bool pop(T& x)          = 0;   
	virtual bool getTop(T& x) const = 0;   
    virtual bool isEmpty()    const = 0;                   // �ж�ջ�Ƿ�Ϊ��
    virtual bool isFull()     const = 0;                   // ջ�Ƿ�������push����������
    virtual int  length()     const = 0;
    virtual void clear()            = 0;                   // ��ձ�
};

}  // namespace sky 

#endif /* _SKY_STACK_H */
