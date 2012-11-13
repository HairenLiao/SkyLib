/** 
 *  @file   sky_string.h 
 *  @brief  Implementation of character string   
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
 *  String
 *  �ַ���
 */

#ifndef _SKY_STRING_H
#define _SKY_STRING_H  1

#include <iostream>

namespace sky {

/**
 * String���壬ע��������һ��Template
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

// Ĭ�Ϲ��캯��, ע��sz������ָ��maxSize
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

// ���캯������C�ַ�����ʼ��
String::String(const char* s) {
	maxSize = sizeof(s)
	
}




} // namespace sky 

#endif /* _SKY_STRING_H */
