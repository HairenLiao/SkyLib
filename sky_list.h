/** @file   sky_list.h 
 *  @brief  Inteface of all linear lists     
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

// ���Ա�ӿ�

#ifndef _SKY_LIST_H
#define _SKY_LIST_H  1

namespace sky {

/** List 
 *  �������в�ͬʵ�ֵ�List�Ľӿڣ���ȫ���ɴ��麯�����ɣ���һ�������࣬�൱��Java��interface)��
 *  ע����Ϊ�ӿڲ�Ҫ����ʵ�����κμٶ���ֻ����ͨ�õķ��������Զ��߿��ܷ�����������̿�������һЩ������
 *  ����Ժ�ʱʹ�����ã���ʱʹ��constҪʮ����ȷ���緽��int search(const T& x) const = 0 ��
 *  ��һ��const��ʾ�˷������ñ���Ĳ���x��ֵ��
 *  Tʹ�����ã�&��һ���Ľ�����Ч�ʣ�
 *  �ڶ���const��ʾ�˷������ı����״̬��
 *  virtual ... = 0 ��ʾ���崿�麯����
 */
template <typename T>
class List {
	//virtual int  capacity() 				const = 0;  // ����LinkedList������capacity,����capacity()���Ե������List�ж���
	//virtual bool isFull() 				const = 0;  // �ж����Ƿ���,��������˷���Ҳ�����ô�
	virtual int  length() 					const = 0;  // ���ȣ��൱��STL vector��size()
    virtual bool isEmpty() 		    		const = 0;  // �ж����Ƿ�Ϊ��
    virtual bool getData(int i, T& x) 		const = 0;  // ȡ��i�������ֵ��ͨ������x����
    virtual int  search(const T& x) 		const = 0;  // �ڱ��в��Ҹ���ֵx��δ�ҵ�����-1
    
    //virtual bool setPos(int i) 		      	  = 0;  // ����ڽӿ����д˺���������ʵ�ֹ����д���Ҫ��һ������current�ı����������������ʵ�֣����Բ���
    virtual bool setData(int i, const T& x)       = 0;  // �޸ĵ�i�������ֵΪx
    virtual bool insert(int i, const T& x) 	      = 0;  // �ڵ�i���������x
    virtual bool remove(int i, T& x) 	          = 0;  // ɾ����i�����ͨ��x����
    virtual bool erase(int i) 		              = 0;  // ɾ����i�����������ֵ����STL vector��erase����
    //virtual void sort() 		      	          = 0;  // �Ա�Ԫ�ؽ�����������
    virtual void clear()                          = 0;  // ��ձ�
};

} // namespace sky 

#endif /* _SKY_LIST_H */
