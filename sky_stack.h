/** @file   sky_stack.h 
 *  @brief  Inteface of all stacks   
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

// 栈的接口

#ifndef _SKY_STACK_H
#define _SKY_STACK_H  1

namespace sky {

const int DEFAULT_MAX_STACK_SIZE = 100;

/** Stack 
 *  为SeqStack和LinkedStack等具体栈的实现使用
 */
template <typename T>
class Stack {
	virtual bool push(const T& x)   = 0;  
	virtual bool pop(T& x)          = 0;   
	virtual bool getTop(T& x) const = 0;   
    virtual bool isEmpty()    const = 0;                   // 判定栈是否为空
    virtual bool isFull()     const = 0;                   // 栈是否满，再push将会产生溢出
    virtual int  length()     const = 0;
    virtual void clear()            = 0;                   // 清空表
};

}  // namespace sky 

#endif /* _SKY_STACK_H */
