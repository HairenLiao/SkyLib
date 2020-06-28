/** 
 *  @file   sky_polynomial.h 
 *  @brief  Implementation of Polynomial     
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
 *  Polynomial
 *  多项式
 */

#ifndef _SKY_POLYNOMIAL_H
#define _SKY_POLYNOMIAL_H  1

#include <iostream>
#include <cmath>

namespace sky {

/**
 * PolynomialTerm
 * @brief 多项式的项，包括系数、指数及下一项的指针
 * C 系数的类型，可以是float、double等，C的类型若不指定，为float类型
 * N 指数的类型，可以是int、long、unsigned int、unsigned long等类型
 * 
 */
template <typename N, typename C = float>
struct PolynomialTerm {
	C coef;            // 系数
	N  n;              // 指数
	PolynomialTerm<N, C>* nextTerm;  // 下一项指针
	PolynomialTerm(const C& c = 0, const N& e = 0, PolynomialTerm* termNext = NULL) : coef(c), n(e), nextTerm(termNext) {}	
};

template <typename N, typename C = float>
class Polynomial {
	// 整个多项式的度可以存储在头结点的指数项中
    // T deg;     // Degree of the polynomial
    PolynomialTerm<N, C>* listHead;
public:
    Polynomial() { listHead = new PolynomialTerm<N, C>; }
    ~Polynomial();
    Polynomial(const Polynomial<N, C>& p);
    
    void clear();
    Polynomial<N, C>& operator=(const Polynomial<N, C>& p);   
    
    N maxDegree() const;  // { return listHead->n; } 用listHead->n存储多项式的度虽可行，但维护成本太高
    bool isEmpty() const { return listHead->nextTerm == NULL; }
    void output() const; 
    
    Polynomial<N, C>& insertTerm(C c, N e);
    C operator()(C x);                  // value of p(x)                  
    C coefficient(N i);                 // return coefficient of x^i
    Polynomial<N, C> operator +() const;
    Polynomial<N, C> operator -() const;
    Polynomial<N, C> operator ^(const N& n) { return PowPolynomial(*this, n); }
    
    
    template <typename NN, typename CC>
    friend Polynomial<NN, CC> operator +(const Polynomial<NN, CC>& p1, const Polynomial<NN, CC>& p2);
    template <typename NN, typename CC>
    friend Polynomial<NN, CC> operator -(const Polynomial<NN, CC>& p1, const Polynomial<NN, CC>& p2);
    template <typename NN, typename CC>
    friend Polynomial<NN, CC> operator *(const Polynomial<NN, CC>& p1, const Polynomial<NN, CC>& p2);
    template <typename NN, typename CC>
    friend Polynomial<NN, CC> MultiplyPolynomial(const Polynomial<NN, CC>& p1, const Polynomial<NN, CC>& p2);
    template <typename NN, typename CC>
    friend Polynomial<NN, CC> PowPolynomial(const Polynomial<NN, CC>& p1, const NN& n);     
    template <typename NN, typename CC>
    friend std::ostream& operator <<(std::ostream& os, const Polynomial<NN, CC>& p);   
};

/**
 * @brief 析构函数：删除所有多项式项
 * 
 */
template <typename N, typename C>
Polynomial<N, C>::~Polynomial() {
	PolynomialTerm<N, C>* ptrTerm;
	while (listHead) {
		ptrTerm = listHead; 
		listHead = listHead->nextTerm;
		delete ptrTerm;
	}	
}

/**
 * @brief 拷贝构造函数
 * 
 */
template <typename N, typename C>
Polynomial<N, C>::Polynomial(const Polynomial<N, C>& p) {
	listHead = new PolynomialTerm<N,C>(p.listHead->coef, p.listHead->n);
	
	PolynomialTerm<N, C>* ptrTerm1 = listHead;
	PolynomialTerm<N, C>* ptrTerm2 = p.listHead->nextTerm;
	
	while (ptrTerm2) {
		ptrTerm1->nextTerm = new PolynomialTerm<N, C>(ptrTerm2->coef, ptrTerm2->n);
		ptrTerm2 = ptrTerm2->nextTerm;
		ptrTerm1 = ptrTerm1->nextTerm;
	}
}

/**
 * @brief 清空所有项结点（不包括头结点）
 * 
 */
template <typename N, typename C>
void Polynomial<N, C>::clear() {
	PolynomialTerm<N, C>* ptrTerm = listHead->nextTerm;
	while (ptrTerm) { 
		listHead->nextTerm = ptrTerm->nextTerm;
		delete ptrTerm;	
		// ptrTerm指向头结点的下一节点
		ptrTerm = listHead->nextTerm;	
	}	
	
	/* 循环结束，只剩下头结点 */
}

/**
 * @brief 求多项式的度 Theta(N)
 * 
 */
template <typename N, typename C>
N Polynomial<N, C>::maxDegree() const {
		
	PolynomialTerm<N, C>* ptrTerm = listHead;
	while (ptrTerm->nextTerm)  // 循环到表结尾
		ptrTerm = ptrTerm->nextTerm;
	
	N deg = ptrTerm->n;
	return deg;
}

/**
 * @brief =运算符重载
 * 
 */
template <typename N, typename C>
Polynomial<N, C>& Polynomial<N, C>::operator=(const Polynomial<N, C>& p) {
	if (this != &p) {
		clear();
		
		PolynomialTerm<N, C>* ptrTerm1 = listHead;
		PolynomialTerm<N, C>* ptrTerm2 = p.listHead->nextTerm;
			
		while (ptrTerm2) {
			ptrTerm1->nextTerm = new PolynomialTerm<N, C>(ptrTerm2->coef, ptrTerm2->n);
			ptrTerm2 = ptrTerm2->nextTerm;
			ptrTerm1 = ptrTerm1->nextTerm;
		}	
	}
	
	return *this;
}

/**
 * @brief 以（系数, 指数）对的形式输出多项式
 * 
 */
template <typename N, typename C>
void Polynomial<N, C>::output() const {
	std::cout << "(";
	PolynomialTerm<N, C>* ptrTerm = listHead->nextTerm;
	
	while (ptrTerm) {
		std::cout << "(" << ptrTerm->coef << ", " << ptrTerm->n << ")";
		if (ptrTerm->nextTerm)
			std::cout << ", ";
		ptrTerm = ptrTerm->nextTerm;
	}
	
	std::cout << ")";
}

/**
 * @brief 插入新项，返回本多项式引用，因此可连续插入
 *        若插入的指数有相同指数项，系数相加
 * 
 */
template <typename N, typename C>
Polynomial<N, C>& Polynomial<N, C>::insertTerm(C c, N e) {
	// 如果插入项指数大于多项式阶template <typename N, typename C = float>数，重置阶数
	// if (e > listHead->n)
	//	listHead->n = e;
	
	PolynomialTerm<N, C>* ptrTerm = listHead;
	
	while (ptrTerm->nextTerm && ptrTerm->nextTerm->n < e)
		ptrTerm = ptrTerm->nextTerm;
	
	/* 到此，ptrTerm->nextTerm要么为NULL, 要么指向要插入的结点的前一节点
	    生成新节点并插入
	 */
	PolynomialTerm<N, C>* tmpTerm;
	C newCoef = c;
	
	// 如果nextTerm存在且指数与插入值相同，系数相加
	if (ptrTerm->nextTerm && ptrTerm->nextTerm->n == e) {
		newCoef += ptrTerm->nextTerm->coef;
	
	    // 如果新系数值非零，更新下一项的系数值
	    if (std::fabs(newCoef) > 1e-6) {
	    	ptrTerm->nextTerm->coef = newCoef;
	    }
	    else {  // 否则，删除下一节点
	    	tmpTerm = ptrTerm->nextTerm;
	    	ptrTerm->nextTerm = tmpTerm->nextTerm;
	    	delete tmpTerm;
	    }
	}
	else {  //否则插入新节点
		tmpTerm = new PolynomialTerm<N, C>(c, e, ptrTerm->nextTerm);
		ptrTerm->nextTerm = tmpTerm;	
	}	
	
	return *this;
}

/**
 * @brief 求某一值x的多项式值p(x), 借用cmath的pow函数实现乘方运算
 * 
 */
template <typename N, typename C>
C Polynomial<N, C>::operator()(C x) {
	C f = 0;
	
	PolynomialTerm<N, C>* ptrTerm = listHead->nextTerm;
	while (ptrTerm) {
		f += (ptrTerm->coef + std::pow(x, ptrTerm->n));
		ptrTerm = ptrTerm->nextTerm;
	}
	
	return f;
}

/**
 * @brief 返回某指数i的对应项的系数
 * 
 */
template <typename N, typename C>
C Polynomial<N, C>::coefficient(N i) {
	PolynomialTerm<N, C>* ptrTerm = listHead->nextTerm;
	
	while (ptrTerm && ptrTerm->n <= i) {
		if (ptrTerm->n == i)
			return ptrTerm->coef;
		ptrTerm = ptrTerm->nextTerm;
	}
	
	// 如果未找到，返回0
	return 0;	
}

/**
 * @brief +p 相当于对原多项式做一个拷贝返回
 * 
 */
template <typename N, typename C>
Polynomial<N, C> Polynomial<N, C>::operator +() const {
	Polynomial<N, C> p;
	p = *this;
	return p;	
}

/**
 * @brief 多项式的每一项反向
 * 
 */
template <typename N, typename C>
Polynomial<N, C> Polynomial<N, C>::operator -() const {
	Polynomial<N, C> p;		
	PolynomialTerm<N, C>* ptrTerm1 = p.listHead;
	PolynomialTerm<N, C>* ptrTerm2 = listHead->nextTerm;
				
	while (ptrTerm2) {
		ptrTerm1->nextTerm = new PolynomialTerm<N, C>(-(ptrTerm2->coef), ptrTerm2->n);
		ptrTerm2 = ptrTerm2->nextTerm;
		ptrTerm1 = ptrTerm1->nextTerm;
	}		
	
	return p;
}

/**
 * @brief 多项式加法
 * 
 */
template <typename N, typename C>
Polynomial<N, C> operator+(const Polynomial<N, C>& p1, const Polynomial<N, C>& p2) {
	Polynomial<N, C> p;
	
	// 此句有漏洞，若两表的最高项互相抵消，则和多项式的阶不是两者的最大者
	// p.listHead->n = (p1.listHead->n) > (p2.listHead->n) ? p1.listHead->n : p2.listHead->n;
	
	PolynomialTerm<N, C>* ptrTerm = p.listHead;
	PolynomialTerm<N, C>* ptrTerm1 = p1.listHead->nextTerm;
	PolynomialTerm<N, C>* ptrTerm2 = p2.listHead->nextTerm;
	
	while (ptrTerm1 && ptrTerm2) {
		if (ptrTerm1->n < ptrTerm2->n) {
			ptrTerm->nextTerm = new PolynomialTerm<N, C>(ptrTerm1->coef, ptrTerm1->n);
			ptrTerm1 = ptrTerm1->nextTerm;
			ptrTerm = ptrTerm->nextTerm;
		}
		else if (ptrTerm1->n > ptrTerm2->n) {
			ptrTerm->nextTerm = new PolynomialTerm<N, C>(ptrTerm2->coef, ptrTerm2->n);
			ptrTerm2 = ptrTerm2->nextTerm;
			ptrTerm = ptrTerm->nextTerm;
		}
		else { // Term1 n = Term n
			C c = ptrTerm1->coef + ptrTerm2->coef;
			
			// 如果系数和不为0，插入系数相加之后的项
			if (std::fabs(c) > 1e-6) {
				ptrTerm->nextTerm = new PolynomialTerm<N, C>(c, ptrTerm1->n);		
				ptrTerm = ptrTerm->nextTerm;
			}	
			
			// 不管p是否加入新想，p1与p2的指针都需要向前移动，否则会陷入死循环
			ptrTerm1 = ptrTerm1->nextTerm;
			ptrTerm2 = ptrTerm2->nextTerm;
			// ptrTerm = ptrTerm->nextTerm;语句不能写在这里，因为此时未插入任何项
		}	
	}
	
	// 补充插入多项式p1的所有项
	while (ptrTerm1) {
		ptrTerm->nextTerm = new PolynomialTerm<N, C>(ptrTerm1->coef, ptrTerm1->n);
		ptrTerm1 = ptrTerm1->nextTerm;
		ptrTerm = ptrTerm->nextTerm;	
	}
	
	// 补充插入多项式p2的所有项
	while (ptrTerm2) {
		ptrTerm->nextTerm = new PolynomialTerm<N, C>(ptrTerm2->coef, ptrTerm2->n);
		ptrTerm1 = ptrTerm2->nextTerm;
		ptrTerm = ptrTerm->nextTerm;	
	}
	
	return p;
}

/**
 * @brief 多项式减法,与多项式加法类似代码，只是插入p2项时用减号
 * 
 */
template <typename N, typename C>
Polynomial<N, C> operator -(const Polynomial<N, C>& p1, const Polynomial<N, C>& p2) {
	Polynomial<N, C> p;
	
	// 此句有漏洞，若两表的最高项互相抵消，则和多项式的阶不是两者的最大者
	// p.listHead->n = (p1.listHead->n) > (p2.listHead->n) ? p1.listHead->n : p2.listHead->n;
	
	PolynomialTerm<N, C>* ptrTerm = p.listHead;
	PolynomialTerm<N, C>* ptrTerm1 = p1.listHead->nextTerm;
	PolynomialTerm<N, C>* ptrTerm2 = p2.listHead->nextTerm;
	
	while (ptrTerm1 && ptrTerm2) {
		if (ptrTerm1->n < ptrTerm2->n) {
			ptrTerm->nextTerm = new PolynomialTerm<N, C>(ptrTerm1->coef, ptrTerm1->n);
			ptrTerm1 = ptrTerm1->nextTerm;
			ptrTerm = ptrTerm->nextTerm;
		}
		else if (ptrTerm1->n > ptrTerm2->n) {
			ptrTerm->nextTerm = new PolynomialTerm<N, C>(-ptrTerm2->coef, ptrTerm2->n);
			ptrTerm2 = ptrTerm2->nextTerm;
			ptrTerm = ptrTerm->nextTerm;
		}
		else { // Term1 n = Term n
			C c = ptrTerm1->coef - ptrTerm2->coef;
			
			// 如果系数和不为0，插入系数相加之后的项
			if (std::fabs(c) > 1e-6) {
				ptrTerm->nextTerm = new PolynomialTerm<N, C>(c, ptrTerm1->n);		
				ptrTerm = ptrTerm->nextTerm;
			}	
			
			// 不管p是否加入新想，p1与p2的指针都需要向前移动，否则会陷入死循环
			ptrTerm1 = ptrTerm1->nextTerm;
			ptrTerm2 = ptrTerm2->nextTerm;
			// ptrTerm = ptrTerm->nextTerm;语句不能写在这里，因为此时未插入任何项
		}	
	}
	
	// 补充插入多项式p1的所有项
	while (ptrTerm1) {
		ptrTerm->nextTerm = new PolynomialTerm<N, C>(ptrTerm1->coef, ptrTerm1->n);
		ptrTerm1 = ptrTerm1->nextTerm;
		ptrTerm = ptrTerm->nextTerm;	
	}
	
	// 补充插入多项式p2的所有项
	while (ptrTerm2) {
		ptrTerm->nextTerm = new PolynomialTerm<N, C>(-ptrTerm2->coef, ptrTerm2->n);
		ptrTerm1 = ptrTerm2->nextTerm;
		ptrTerm = ptrTerm->nextTerm;	
	}
	
	return p;
}

/**
 * @brief 多项式乘法，借用insertTerm方法能处理重复指数项的特点
 * 
 */
template <typename N, typename C>
Polynomial<N, C> operator *(const Polynomial<N, C>& p1, const Polynomial<N, C>& p2) {
	Polynomial<N, C> p;
	
	PolynomialTerm<N, C>* ptrTerm1 = p1.listHead->nextTerm;
	PolynomialTerm<N, C>* ptrTerm2 = p2.listHead->nextTerm;
	
	while (ptrTerm1) {
		ptrTerm2 = p2.listHead->nextTerm; // 每次循环需重置ptrTerm2指针到p2表头
		
		while (ptrTerm2) {
			p.insertTerm(ptrTerm1->coef * ptrTerm2->coef, ptrTerm1->n + ptrTerm2->n);
			ptrTerm2 = ptrTerm2->nextTerm;	
		}
		
		ptrTerm1 = ptrTerm1->nextTerm;
	}
	
	return p;
}

/**
 * @brief 多项式乘法的另一形式实现，用临时数组存放结果，效率更高
 * 
 */
template <typename N, typename C>
Polynomial<N, C> MultiplyPolynomial(const Polynomial<N, C>& p1, const Polynomial<N, C>& p2) {
	Polynomial<N, C> p;
	
	// 如果p1或p2空，直接返回空多项式
	if (p1.isEmpty() || p2.isEmpty()) 
	    return p;
	
	N maxDeg = p1.maxDegree() + p2.maxDegree();
	
	C *tmpResult= new C[maxDeg+1];   // 临时暂存结果数组
	
	for (N i = 0; i <= maxDeg; i++)   // 数组元素置0
		tmpResult[i] = 0;
	
	PolynomialTerm<N, C>* ptrTerm1 = p1.listHead->nextTerm;
	PolynomialTerm<N, C>* ptrTerm2 = p2.listHead->nextTerm;
	
	while (ptrTerm1) {
		ptrTerm2 = p2.listHead->nextTerm; // 每次循环需重置ptrTerm2指针到p2表头
		
		while (ptrTerm2) {
			// 将结果暂存入数组
			tmpResult[ptrTerm1->n + ptrTerm2->n] += (ptrTerm1->coef * ptrTerm2->coef);
			ptrTerm2 = ptrTerm2->nextTerm;	
		}
		
		ptrTerm1 = ptrTerm1->nextTerm;
	}
	
	// 结果存入多项式p
	PolynomialTerm<N, C>* ptrTerm = p.listHead;
	for (N i = 0; i <= maxDeg; i++) {
		if (std::fabs(tmpResult[i]) > 1e-6) { // 如果数组元素非0，插入结果多项式
			ptrTerm->nextTerm = new PolynomialTerm<N, C>(tmpResult[i], i);
			ptrTerm = ptrTerm->nextTerm;	
		}
	}
	
	delete[] tmpResult;  // 删除临时数组
	return p;
}

/**
 * @brief 乘方
 * 
 */
template <typename N, typename C>
Polynomial<N, C> PowPolynomial(const Polynomial<N, C>& p1, const N& n) {
	Polynomial<N, C> p;
	if (n == 1) 
		p = p1;
	else if (n == 2) 
		p = MultiplyPolynomial<N, C>(p1, p1);
	else if (n > 2) 
		p = MultiplyPolynomial<N, C>(p1, PowPolynomial<N, C>(p1, n-1));
	
	return p;
}


/**
 * @brief 输出<<重载
 * 
 */
template <typename N, typename C>
std::ostream& operator <<(std::ostream& os, const Polynomial<N, C>& p) {
	    os << "(";
		PolynomialTerm<N, C>* ptrTerm = p.listHead->nextTerm;
		
		while (ptrTerm) {
			os << "(" << ptrTerm->coef << ", " << ptrTerm->n << ")";
			if (ptrTerm->nextTerm)
				os << ", ";
			ptrTerm = ptrTerm->nextTerm;
		}
		
		os << ")"; 
}
    
}  // namespace sky

#endif   /*  _SKY_POLYNOMIAL_H   */
