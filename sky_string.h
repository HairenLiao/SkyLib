/** 
 *  @file   sky_string.h 
 *  @brief  Implementation of character string   
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
 *  String
 *  字符串
 */

#ifndef _SKY_STRING_H
#define _SKY_STRING_H  1

#include <iostream>

namespace sky {

/**
 * String定义，注意它不是一个Template
 */
class String {
public:
	String(int sz = 0);
	String(const char* s);
	String(const String& s);
	String& operator=(const String& s);
	~String() {
		delete[] str;
	}

	int length() const {
		return len;
	}
	int size() const {
		return len;
	}
	int capacity() const {
		return maxSize;
	}
	int find(const String& s) const;
	String& subString(int pos, int n);
	int compare(const String& s);
	String& concat(const String& s);
	String& insert(const String& s, int pos);
	String& erase(int pos, int n);
	String& replace(const String& s, int pos, int n);

	char& operator[](int i);
	String& operator()(int pos, int n);
	String& operator+=(const String& s);
	bool operator==(const String& s);
	bool operator!();
	bool operator!=(const String& s);

private:
	char* str;
	int len;
	int maxSize;
};

// 默认构造函数, 注意sz是用来指定maxSize
String::String(int sz) {
	maxSize = (sz >= 0) ? sz : 0;
	str = new char[maxSize + 1];
	if (str == NULL) {
		std::cerr << "Allocation Error" << std::endl;
		exit(1);
	}
	len = 0;
	str[0] = '\0';
}

// 构造函数，以C字符串初始化
String::String(const char* s) {
	maxSize = sizeof(s)
	
}




} // namespace sky 

#endif /* _SKY_STRING_H */
