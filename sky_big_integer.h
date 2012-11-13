/** @file   sky_big_integer.h
 *  @brief  使用 STL list实现的不限大小的整数
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

// 无限制整数

#ifndef _SKY_BIG_INTEGER_H
#define _SKY_BIG_INTEGER_H 1

#include <iostream>
#include <string>
#include <list>

namespace sky {

class BigInteger {
public:
	BigInteger() : sign(false) {
		bitList = new std::list<int>;
	}
	BigInteger(const std::string& s);
	BigInteger(const BigInteger& x);
	BigInteger& operator=(const BigInteger& x);
	~BigInteger();
	void output() const;
	BigInteger operator-() const;

	friend int AbsCompare(const BigInteger& x, const BigInteger& y); // 比较两个整数的绝对值哪个大
	friend BigInteger operator+(const BigInteger& x, const BigInteger& y);
	friend BigInteger operator-(const BigInteger& x, const BigInteger& y);
	friend BigInteger operator*(const BigInteger& x, const BigInteger& y);
	friend BigInteger operator^(const BigInteger& x, int n);
	friend std::ostream& operator <<(std::ostream& os, const BigInteger& x);

private:
	void removeLeadingZeros();
	std::list<int>* bitList;
	bool sign; // 表识正数还是负数 true表示-, false表示+
};

// 删除开始的0
void BigInteger::removeLeadingZeros() {
	std::list<int>::iterator iter = bitList->begin();
	while (iter != bitList->end() && *iter == 0) {
		iter = bitList->erase(iter);
	}
}

// 比较这个整数的绝对值大小
int AbsCompare(const BigInteger& x, const BigInteger& y) {
	if (x.bitList->size() > y.bitList->size()) {
		return 1;
	} else if (x.bitList->size() < y.bitList->size()) {
		return -1;
	} else {
		std::list<int>::const_iterator px = x.bitList->begin();
		std::list<int>::const_iterator py = y.bitList->begin();
		while (px != x.bitList->end()) {
			if (*px > *py)
				return 1;
			else if (*px < *py)
				return -1;
			++px;
			++py;
		}
	}

	// 如果走到这里，表明两整数绝对值相等
	return 0;
}

/**
 * @brief 通过std::string初始化大整数
 *        注意需要处理开始的0
 */
BigInteger::BigInteger(const std::string& s) {
	bitList = new std::list<int>;
	char c;
	sign = false;

	// 如果s非空，取第一个字符作为符号位
	if (s.size() > 0 && s[0] == '-')
		sign = true;

	for (std::string::size_type i = 0; i < s.size(); ++i) {
		c = s[i];
		if (c >= '0' && c <= '9')
			bitList->push_back(c - '0');
	}

	removeLeadingZeros();
}

// 拷贝构造函数
BigInteger::BigInteger(const BigInteger& x) {
	bitList = new std::list<int>;
	sign = x.sign;
	for (std::list<int>::const_iterator c_iter = x.bitList->begin(); c_iter
			!= x.bitList->end(); ++c_iter)
		bitList->push_back(*c_iter);
}

// =运算符重载
BigInteger& BigInteger::operator=(const BigInteger& x) {
	if (this != &x) {
		sign = x.sign;
		for (std::list<int>::const_iterator c_iter = x.bitList->begin(); c_iter != x.bitList->end(); ++c_iter)
		bitList->push_back(*c_iter);
	}

	return *this;
}

// 析构函数
BigInteger::~BigInteger() {
	delete bitList;
}

// 输出整数值
void BigInteger::output() const {
	if (sign)
	std::cout << '-';
	if (bitList->empty())
	std::cout << "0";

	std::list<int>::const_iterator c_iter = bitList->begin();
	for (;c_iter != bitList->end(); ++c_iter)
	std::cout << *c_iter;
}

// 符号取反
BigInteger BigInteger::operator-() const {
	BigInteger bigInt;
	//bigInt.sign = -sign;  bool变量应该用!sign 而不是-sign!!!
	bigInt.sign = !sign;
	for (std::list<int>::const_iterator c_iter = bitList->begin(); c_iter != bitList->end(); ++c_iter)
	bigInt.bitList->push_back(*c_iter);
	return bigInt;
}

// 两整数加法
BigInteger operator+ (const BigInteger& x, const BigInteger& y) {
	// 如果x、y符号不同, 用减法代替加法
	if (x.sign != y.sign) {
		//std::cout << "Point2" << std::endl;
		return x - (-y);
	}

	//std::cout << "Point3" << std::endl;
	BigInteger bigInt;
	bigInt.sign = x.sign;

	std::list<int>::reverse_iterator px = x.bitList->rbegin();
	std::list<int>::reverse_iterator py = y.bitList->rbegin();

	int a, b, r; //  a = 10*b + r
	b = 0; //  b是附加位
	while (px != x.bitList->rend() && py != y.bitList->rend()) {
		//std::cout << *px << " " << *py << " " << std::endl;
		a = *px + *py + b; // 两个位数相加再加上上一次加法的剩余位
		b = a / 10;
		r = a % 10;
		bigInt.bitList->push_front(r); // 余位插入链表	
		++px;
		++py;
	}

	/* 至此，两个整数至少一个已经加完 */
	// 处理整数px的可能剩余项
	while (px != x.bitList->rend()) {
		a = *px + b; // 两个位数相加再加上上一次加法的剩余位
		b = a / 10;
		r = a % 10;
		bigInt.bitList->push_front(r); // 余位插入链表	
		++px;
	}

	// 处理整数py的可能剩余项
	while (py != y.bitList->rend()) {
		a = *py + b; // 两个位数相加再加上上一次加法的剩余位
		b = a / 10;
		r = a % 10;
		bigInt.bitList->push_front(r); // 余位插入链表	
		++py;
	}

	// 如果可能的进位存在，也需要插入链表
	if (b > 0)
	bigInt.bitList->push_front(b);

	return bigInt;
}

// 两整数减法
BigInteger operator- (const BigInteger& x, const BigInteger& y) {
	// 如果两整数符号不同，用加法代替减法
	BigInteger bigInt;
	if (x.sign != y.sign) {
		// std::cout << "Point1" << std::endl;
		return (x + (-y));
	}

	// 此时两数符号相同

	std::list<int>* biggerNum;
	std::list<int>* smallerNum;

	if (AbsCompare(x, y) >= 0) {
		if (x.sign == true)
		bigInt.sign = true;
		biggerNum = x.bitList;
		smallerNum = y.bitList;
	}
	else {
		if (y.sign == false)
		bigInt.sign = true;
		biggerNum = y.bitList;
		smallerNum = x.bitList;
	}

	// px为绝对值大数的迭代器，py为绝对值小数的迭代器
	std::list<int>::reverse_iterator px = biggerNum->rbegin();
	std::list<int>::reverse_iterator py = smallerNum->rbegin();

	// 假定Abs(x) > Abs(y)
	int a, b, r; //  a = 10*b + r
	b = 0; //  b是附加位
	while (px != biggerNum->rend() && py != smallerNum->rend()) {
		if ((*px + b) >= *py) {
			r = (*px + b) - *py;
			bigInt.bitList->push_front(r); // 余位插入链表
			b = 0;
		}
		else {
			r = (*px + b) - *py + 10;
			b = -1;
			bigInt.bitList->push_front(r); // 余位插入链表
		}

		++px;
		++py;
	}

	/* 至此，两个整数至少一个已经加完 */
	// 处理整数px的可能剩余项
	while (px != biggerNum->rend()) {
		a = *px + b; // 两个位数相加再加上上一次加法的剩余位
		b = a / 10;
		r = a % 10;
		bigInt.bitList->push_front(r); // 余位插入链表	
		++px;
	}

	bigInt.removeLeadingZeros();
	return bigInt;
}

// 整数乘法
BigInteger operator* (const BigInteger& x, const BigInteger& y) {
	// 如果两整数符号不同，用加法代替减法
	BigInteger bigInt;
	if (x.sign != y.sign)
	bigInt.sign = true;

	if (x.bitList->empty() || y.bitList->empty())
	return bigInt;

	std::list<int>::size_type maxSize = x.bitList->size() + y.bitList->size();

	// 建立暂存数组并每位清0
	int *tmpResult = new int[maxSize+1];
	for (std::list<int>::size_type k = 0; k <= maxSize; ++k)
	tmpResult[k] = 0;

	std::list<int>::size_type i, j; // x, y的位阶数
	int t; // 存储两位数的乘积

	i = 0;
	for (std::list<int>::reverse_iterator px = x.bitList->rbegin(); px != x.bitList->rend(); ++px) {
		j = 0;
		for (std::list<int>::reverse_iterator py = y.bitList->rbegin(); py != y.bitList->rend(); ++py) {
			t = (*px) * (*py);
			tmpResult[i+j] += t;
			j++;
		}
		i++;
	}

	/* 至此，所有的数都乘完，并且都保存在临时数组tmpResult中，但是有一个问题；每位数可能大于9，所以需要整理。
	 * 这是大整数乘法相对于多项式乘法不同之处。
	 */
	t = 0; // 从这里开始t用来存储进位数 
	int s; // 存储某一位与进位数之和
	for (std::list<int>::size_type k = 0; k <= maxSize; ++k) {
		s = tmpResult[k] + t;
		tmpResult[k] = s % 10;
		t = s / 10;
		bigInt.bitList->push_front(tmpResult[k]);
	}

	delete tmpResult;
	bigInt.removeLeadingZeros();
	return bigInt;
}

// 乘方运算 n为正整数，否则返回0
BigInteger operator^(const BigInteger& x, int n) {
	BigInteger bigInt;
	if (n == 1)
	bigInt = x;
	else if (n >= 2)
	bigInt = x * (x^(n-1));

	return bigInt;
}

/**
 * @brief 输出重定向运算符<<重载
 * 
 */
std::ostream& operator <<(std::ostream& os, const BigInteger& x) {
	if (x.sign)
	os << '-';
	if (x.bitList->empty())
	os << "0";
	std::list<int>::const_iterator c_iter = x.bitList->begin();
	for (;c_iter != x.bitList->end(); ++c_iter)
	os << *c_iter;
	return os;
}

} // namespace sky 

#endif /* _SKY_BIG_INTEGER_H */
