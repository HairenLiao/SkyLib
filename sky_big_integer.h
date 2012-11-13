/** @file   sky_big_integer.h
 *  @brief  ʹ�� STL listʵ�ֵĲ��޴�С������
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

// ����������

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

	friend int AbsCompare(const BigInteger& x, const BigInteger& y); // �Ƚ����������ľ���ֵ�ĸ���
	friend BigInteger operator+(const BigInteger& x, const BigInteger& y);
	friend BigInteger operator-(const BigInteger& x, const BigInteger& y);
	friend BigInteger operator*(const BigInteger& x, const BigInteger& y);
	friend BigInteger operator^(const BigInteger& x, int n);
	friend std::ostream& operator <<(std::ostream& os, const BigInteger& x);

private:
	void removeLeadingZeros();
	std::list<int>* bitList;
	bool sign; // ��ʶ�������Ǹ��� true��ʾ-, false��ʾ+
};

// ɾ����ʼ��0
void BigInteger::removeLeadingZeros() {
	std::list<int>::iterator iter = bitList->begin();
	while (iter != bitList->end() && *iter == 0) {
		iter = bitList->erase(iter);
	}
}

// �Ƚ���������ľ���ֵ��С
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

	// ����ߵ������������������ֵ���
	return 0;
}

/**
 * @brief ͨ��std::string��ʼ��������
 *        ע����Ҫ����ʼ��0
 */
BigInteger::BigInteger(const std::string& s) {
	bitList = new std::list<int>;
	char c;
	sign = false;

	// ���s�ǿգ�ȡ��һ���ַ���Ϊ����λ
	if (s.size() > 0 && s[0] == '-')
		sign = true;

	for (std::string::size_type i = 0; i < s.size(); ++i) {
		c = s[i];
		if (c >= '0' && c <= '9')
			bitList->push_back(c - '0');
	}

	removeLeadingZeros();
}

// �������캯��
BigInteger::BigInteger(const BigInteger& x) {
	bitList = new std::list<int>;
	sign = x.sign;
	for (std::list<int>::const_iterator c_iter = x.bitList->begin(); c_iter
			!= x.bitList->end(); ++c_iter)
		bitList->push_back(*c_iter);
}

// =���������
BigInteger& BigInteger::operator=(const BigInteger& x) {
	if (this != &x) {
		sign = x.sign;
		for (std::list<int>::const_iterator c_iter = x.bitList->begin(); c_iter != x.bitList->end(); ++c_iter)
		bitList->push_back(*c_iter);
	}

	return *this;
}

// ��������
BigInteger::~BigInteger() {
	delete bitList;
}

// �������ֵ
void BigInteger::output() const {
	if (sign)
	std::cout << '-';
	if (bitList->empty())
	std::cout << "0";

	std::list<int>::const_iterator c_iter = bitList->begin();
	for (;c_iter != bitList->end(); ++c_iter)
	std::cout << *c_iter;
}

// ����ȡ��
BigInteger BigInteger::operator-() const {
	BigInteger bigInt;
	//bigInt.sign = -sign;  bool����Ӧ����!sign ������-sign!!!
	bigInt.sign = !sign;
	for (std::list<int>::const_iterator c_iter = bitList->begin(); c_iter != bitList->end(); ++c_iter)
	bigInt.bitList->push_back(*c_iter);
	return bigInt;
}

// �������ӷ�
BigInteger operator+ (const BigInteger& x, const BigInteger& y) {
	// ���x��y���Ų�ͬ, �ü�������ӷ�
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
	b = 0; //  b�Ǹ���λ
	while (px != x.bitList->rend() && py != y.bitList->rend()) {
		//std::cout << *px << " " << *py << " " << std::endl;
		a = *px + *py + b; // ����λ������ټ�����һ�μӷ���ʣ��λ
		b = a / 10;
		r = a % 10;
		bigInt.bitList->push_front(r); // ��λ��������	
		++px;
		++py;
	}

	/* ���ˣ�������������һ���Ѿ����� */
	// ��������px�Ŀ���ʣ����
	while (px != x.bitList->rend()) {
		a = *px + b; // ����λ������ټ�����һ�μӷ���ʣ��λ
		b = a / 10;
		r = a % 10;
		bigInt.bitList->push_front(r); // ��λ��������	
		++px;
	}

	// ��������py�Ŀ���ʣ����
	while (py != y.bitList->rend()) {
		a = *py + b; // ����λ������ټ�����һ�μӷ���ʣ��λ
		b = a / 10;
		r = a % 10;
		bigInt.bitList->push_front(r); // ��λ��������	
		++py;
	}

	// ������ܵĽ�λ���ڣ�Ҳ��Ҫ��������
	if (b > 0)
	bigInt.bitList->push_front(b);

	return bigInt;
}

// ����������
BigInteger operator- (const BigInteger& x, const BigInteger& y) {
	// ������������Ų�ͬ���üӷ��������
	BigInteger bigInt;
	if (x.sign != y.sign) {
		// std::cout << "Point1" << std::endl;
		return (x + (-y));
	}

	// ��ʱ����������ͬ

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

	// pxΪ����ֵ�����ĵ�������pyΪ����ֵС���ĵ�����
	std::list<int>::reverse_iterator px = biggerNum->rbegin();
	std::list<int>::reverse_iterator py = smallerNum->rbegin();

	// �ٶ�Abs(x) > Abs(y)
	int a, b, r; //  a = 10*b + r
	b = 0; //  b�Ǹ���λ
	while (px != biggerNum->rend() && py != smallerNum->rend()) {
		if ((*px + b) >= *py) {
			r = (*px + b) - *py;
			bigInt.bitList->push_front(r); // ��λ��������
			b = 0;
		}
		else {
			r = (*px + b) - *py + 10;
			b = -1;
			bigInt.bitList->push_front(r); // ��λ��������
		}

		++px;
		++py;
	}

	/* ���ˣ�������������һ���Ѿ����� */
	// ��������px�Ŀ���ʣ����
	while (px != biggerNum->rend()) {
		a = *px + b; // ����λ������ټ�����һ�μӷ���ʣ��λ
		b = a / 10;
		r = a % 10;
		bigInt.bitList->push_front(r); // ��λ��������	
		++px;
	}

	bigInt.removeLeadingZeros();
	return bigInt;
}

// �����˷�
BigInteger operator* (const BigInteger& x, const BigInteger& y) {
	// ������������Ų�ͬ���üӷ��������
	BigInteger bigInt;
	if (x.sign != y.sign)
	bigInt.sign = true;

	if (x.bitList->empty() || y.bitList->empty())
	return bigInt;

	std::list<int>::size_type maxSize = x.bitList->size() + y.bitList->size();

	// �����ݴ����鲢ÿλ��0
	int *tmpResult = new int[maxSize+1];
	for (std::list<int>::size_type k = 0; k <= maxSize; ++k)
	tmpResult[k] = 0;

	std::list<int>::size_type i, j; // x, y��λ����
	int t; // �洢��λ���ĳ˻�

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

	/* ���ˣ����е��������꣬���Ҷ���������ʱ����tmpResult�У�������һ�����⣻ÿλ�����ܴ���9��������Ҫ����
	 * ���Ǵ������˷�����ڶ���ʽ�˷���֮ͬ����
	 */
	t = 0; // �����￪ʼt�����洢��λ�� 
	int s; // �洢ĳһλ���λ��֮��
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

// �˷����� nΪ�����������򷵻�0
BigInteger operator^(const BigInteger& x, int n) {
	BigInteger bigInt;
	if (n == 1)
	bigInt = x;
	else if (n >= 2)
	bigInt = x * (x^(n-1));

	return bigInt;
}

/**
 * @brief ����ض��������<<����
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
