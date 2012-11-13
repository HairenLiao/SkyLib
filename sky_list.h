/** @file   sky_list.h 
 *  @brief  Inteface of all linear lists     
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

// 线性表接口

#ifndef _SKY_LIST_H
#define _SKY_LIST_H  1

namespace sky {

/** List 
 *  定义所有不同实现的List的接口（它全部由纯虚函数构成，是一个纯虚类，相当于Java的interface)。
 *  注意作为接口不要对其实现做任何假定，只定义通用的方法，所以读者可能发觉这里比许多教科书少了一些方法。
 *  另外对何时使用引用，何时使用const要十分明确。如方法int search(const T& x) const = 0 ：
 *  第一个const表示此方法不该表传入的参数x的值；
 *  T使用引用（&）一般会改进传参效率；
 *  第二个const表示此方法不改变类的状态；
 *  virtual ... = 0 表示定义纯虚函数。
 */
template <typename T>
class List {
	//virtual int  capacity() 				const = 0;  // 对于LinkedList不存在capacity,所以capacity()可以到具体的List中定义
	//virtual bool isFull() 				const = 0;  // 判定表是否满,对于链表此方法也无甚用处
	virtual int  length() 					const = 0;  // 表长度，相当于STL vector的size()
    virtual bool isEmpty() 		    		const = 0;  // 判定表是否为空
    virtual bool getData(int i, T& x) 		const = 0;  // 取第i个表项的值，通过引用x返回
    virtual int  search(const T& x) 		const = 0;  // 在表中查找给定值x，未找到返回-1
    
    //virtual bool setPos(int i) 		      	  = 0;  // 如果在接口中有此函数，则在实现过程中大致要有一个类似current的变量，如果则限制了实现，所以不加
    virtual bool setData(int i, const T& x)       = 0;  // 修改第i个表项的值为x
    virtual bool insert(int i, const T& x) 	      = 0;  // 在第i个表项插入x
    virtual bool remove(int i, T& x) 	          = 0;  // 删除第i个表项，通过x返回
    virtual bool erase(int i) 		              = 0;  // 删除第i个表项，不返回值，仿STL vector的erase函数
    //virtual void sort() 		      	          = 0;  // 对表元素进行升序排序
    virtual void clear()                          = 0;  // 清空表
};

} // namespace sky 

#endif /* _SKY_LIST_H */
