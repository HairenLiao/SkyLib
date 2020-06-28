/** 
 *  @file   sky_polynomial.h 
 *  @brief  Implementation of Polynomial     
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
 *  Polynomial
 *  ����ʽ
 */

#ifndef _SKY_POLYNOMIAL_H
#define _SKY_POLYNOMIAL_H  1

#include <iostream>
#include <cmath>

namespace sky {

/**
 * PolynomialTerm
 * @brief ����ʽ�������ϵ����ָ������һ���ָ��
 * C ϵ�������ͣ�������float��double�ȣ�C����������ָ����Ϊfloat����
 * N ָ�������ͣ�������int��long��unsigned int��unsigned long������
 * 
 */
template <typename N, typename C = float>
struct PolynomialTerm {
	C coef;            // ϵ��
	N  n;              // ָ��
	PolynomialTerm<N, C>* nextTerm;  // ��һ��ָ��
	PolynomialTerm(const C& c = 0, const N& e = 0, PolynomialTerm* termNext = NULL) : coef(c), n(e), nextTerm(termNext) {}	
};

template <typename N, typename C = float>
class Polynomial {
	// ��������ʽ�Ķȿ��Դ洢��ͷ����ָ������
    // T deg;     // Degree of the polynomial
    PolynomialTerm<N, C>* listHead;
public:
    Polynomial() { listHead = new PolynomialTerm<N, C>; }
    ~Polynomial();
    Polynomial(const Polynomial<N, C>& p);
    
    void clear();
    Polynomial<N, C>& operator=(const Polynomial<N, C>& p);   
    
    N maxDegree() const;  // { return listHead->n; } ��listHead->n�洢����ʽ�Ķ�����У���ά���ɱ�̫��
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
 * @brief ����������ɾ�����ж���ʽ��
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
 * @brief �������캯��
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
 * @brief ����������㣨������ͷ��㣩
 * 
 */
template <typename N, typename C>
void Polynomial<N, C>::clear() {
	PolynomialTerm<N, C>* ptrTerm = listHead->nextTerm;
	while (ptrTerm) { 
		listHead->nextTerm = ptrTerm->nextTerm;
		delete ptrTerm;	
		// ptrTermָ��ͷ������һ�ڵ�
		ptrTerm = listHead->nextTerm;	
	}	
	
	/* ѭ��������ֻʣ��ͷ��� */
}

/**
 * @brief �����ʽ�Ķ� Theta(N)
 * 
 */
template <typename N, typename C>
N Polynomial<N, C>::maxDegree() const {
		
	PolynomialTerm<N, C>* ptrTerm = listHead;
	while (ptrTerm->nextTerm)  // ѭ�������β
		ptrTerm = ptrTerm->nextTerm;
	
	N deg = ptrTerm->n;
	return deg;
}

/**
 * @brief =���������
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
 * @brief �ԣ�ϵ��, ָ�����Ե���ʽ�������ʽ
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
 * @brief ����������ر�����ʽ���ã���˿���������
 *        �������ָ������ָͬ���ϵ�����
 * 
 */
template <typename N, typename C>
Polynomial<N, C>& Polynomial<N, C>::insertTerm(C c, N e) {
	// ���������ָ�����ڶ���ʽ��template <typename N, typename C = float>�������ý���
	// if (e > listHead->n)
	//	listHead->n = e;
	
	PolynomialTerm<N, C>* ptrTerm = listHead;
	
	while (ptrTerm->nextTerm && ptrTerm->nextTerm->n < e)
		ptrTerm = ptrTerm->nextTerm;
	
	/* ���ˣ�ptrTerm->nextTermҪôΪNULL, Ҫôָ��Ҫ����Ľ���ǰһ�ڵ�
	    �����½ڵ㲢����
	 */
	PolynomialTerm<N, C>* tmpTerm;
	C newCoef = c;
	
	// ���nextTerm������ָ�������ֵ��ͬ��ϵ�����
	if (ptrTerm->nextTerm && ptrTerm->nextTerm->n == e) {
		newCoef += ptrTerm->nextTerm->coef;
	
	    // �����ϵ��ֵ���㣬������һ���ϵ��ֵ
	    if (std::fabs(newCoef) > 1e-6) {
	    	ptrTerm->nextTerm->coef = newCoef;
	    }
	    else {  // ����ɾ����һ�ڵ�
	    	tmpTerm = ptrTerm->nextTerm;
	    	ptrTerm->nextTerm = tmpTerm->nextTerm;
	    	delete tmpTerm;
	    }
	}
	else {  //��������½ڵ�
		tmpTerm = new PolynomialTerm<N, C>(c, e, ptrTerm->nextTerm);
		ptrTerm->nextTerm = tmpTerm;	
	}	
	
	return *this;
}

/**
 * @brief ��ĳһֵx�Ķ���ʽֵp(x), ����cmath��pow����ʵ�ֳ˷�����
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
 * @brief ����ĳָ��i�Ķ�Ӧ���ϵ��
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
	
	// ���δ�ҵ�������0
	return 0;	
}

/**
 * @brief +p �൱�ڶ�ԭ����ʽ��һ����������
 * 
 */
template <typename N, typename C>
Polynomial<N, C> Polynomial<N, C>::operator +() const {
	Polynomial<N, C> p;
	p = *this;
	return p;	
}

/**
 * @brief ����ʽ��ÿһ���
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
 * @brief ����ʽ�ӷ�
 * 
 */
template <typename N, typename C>
Polynomial<N, C> operator+(const Polynomial<N, C>& p1, const Polynomial<N, C>& p2) {
	Polynomial<N, C> p;
	
	// �˾���©������������������������Ͷ���ʽ�Ľײ������ߵ������
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
			
			// ���ϵ���Ͳ�Ϊ0������ϵ�����֮�����
			if (std::fabs(c) > 1e-6) {
				ptrTerm->nextTerm = new PolynomialTerm<N, C>(c, ptrTerm1->n);		
				ptrTerm = ptrTerm->nextTerm;
			}	
			
			// ����p�Ƿ�������룬p1��p2��ָ�붼��Ҫ��ǰ�ƶ��������������ѭ��
			ptrTerm1 = ptrTerm1->nextTerm;
			ptrTerm2 = ptrTerm2->nextTerm;
			// ptrTerm = ptrTerm->nextTerm;��䲻��д�������Ϊ��ʱδ�����κ���
		}	
	}
	
	// ����������ʽp1��������
	while (ptrTerm1) {
		ptrTerm->nextTerm = new PolynomialTerm<N, C>(ptrTerm1->coef, ptrTerm1->n);
		ptrTerm1 = ptrTerm1->nextTerm;
		ptrTerm = ptrTerm->nextTerm;	
	}
	
	// ����������ʽp2��������
	while (ptrTerm2) {
		ptrTerm->nextTerm = new PolynomialTerm<N, C>(ptrTerm2->coef, ptrTerm2->n);
		ptrTerm1 = ptrTerm2->nextTerm;
		ptrTerm = ptrTerm->nextTerm;	
	}
	
	return p;
}

/**
 * @brief ����ʽ����,�����ʽ�ӷ����ƴ��룬ֻ�ǲ���p2��ʱ�ü���
 * 
 */
template <typename N, typename C>
Polynomial<N, C> operator -(const Polynomial<N, C>& p1, const Polynomial<N, C>& p2) {
	Polynomial<N, C> p;
	
	// �˾���©������������������������Ͷ���ʽ�Ľײ������ߵ������
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
			
			// ���ϵ���Ͳ�Ϊ0������ϵ�����֮�����
			if (std::fabs(c) > 1e-6) {
				ptrTerm->nextTerm = new PolynomialTerm<N, C>(c, ptrTerm1->n);		
				ptrTerm = ptrTerm->nextTerm;
			}	
			
			// ����p�Ƿ�������룬p1��p2��ָ�붼��Ҫ��ǰ�ƶ��������������ѭ��
			ptrTerm1 = ptrTerm1->nextTerm;
			ptrTerm2 = ptrTerm2->nextTerm;
			// ptrTerm = ptrTerm->nextTerm;��䲻��д�������Ϊ��ʱδ�����κ���
		}	
	}
	
	// ����������ʽp1��������
	while (ptrTerm1) {
		ptrTerm->nextTerm = new PolynomialTerm<N, C>(ptrTerm1->coef, ptrTerm1->n);
		ptrTerm1 = ptrTerm1->nextTerm;
		ptrTerm = ptrTerm->nextTerm;	
	}
	
	// ����������ʽp2��������
	while (ptrTerm2) {
		ptrTerm->nextTerm = new PolynomialTerm<N, C>(-ptrTerm2->coef, ptrTerm2->n);
		ptrTerm1 = ptrTerm2->nextTerm;
		ptrTerm = ptrTerm->nextTerm;	
	}
	
	return p;
}

/**
 * @brief ����ʽ�˷�������insertTerm�����ܴ����ظ�ָ������ص�
 * 
 */
template <typename N, typename C>
Polynomial<N, C> operator *(const Polynomial<N, C>& p1, const Polynomial<N, C>& p2) {
	Polynomial<N, C> p;
	
	PolynomialTerm<N, C>* ptrTerm1 = p1.listHead->nextTerm;
	PolynomialTerm<N, C>* ptrTerm2 = p2.listHead->nextTerm;
	
	while (ptrTerm1) {
		ptrTerm2 = p2.listHead->nextTerm; // ÿ��ѭ��������ptrTerm2ָ�뵽p2��ͷ
		
		while (ptrTerm2) {
			p.insertTerm(ptrTerm1->coef * ptrTerm2->coef, ptrTerm1->n + ptrTerm2->n);
			ptrTerm2 = ptrTerm2->nextTerm;	
		}
		
		ptrTerm1 = ptrTerm1->nextTerm;
	}
	
	return p;
}

/**
 * @brief ����ʽ�˷�����һ��ʽʵ�֣�����ʱ�����Ž����Ч�ʸ���
 * 
 */
template <typename N, typename C>
Polynomial<N, C> MultiplyPolynomial(const Polynomial<N, C>& p1, const Polynomial<N, C>& p2) {
	Polynomial<N, C> p;
	
	// ���p1��p2�գ�ֱ�ӷ��ؿն���ʽ
	if (p1.isEmpty() || p2.isEmpty()) 
	    return p;
	
	N maxDeg = p1.maxDegree() + p2.maxDegree();
	
	C *tmpResult= new C[maxDeg+1];   // ��ʱ�ݴ�������
	
	for (N i = 0; i <= maxDeg; i++)   // ����Ԫ����0
		tmpResult[i] = 0;
	
	PolynomialTerm<N, C>* ptrTerm1 = p1.listHead->nextTerm;
	PolynomialTerm<N, C>* ptrTerm2 = p2.listHead->nextTerm;
	
	while (ptrTerm1) {
		ptrTerm2 = p2.listHead->nextTerm; // ÿ��ѭ��������ptrTerm2ָ�뵽p2��ͷ
		
		while (ptrTerm2) {
			// ������ݴ�������
			tmpResult[ptrTerm1->n + ptrTerm2->n] += (ptrTerm1->coef * ptrTerm2->coef);
			ptrTerm2 = ptrTerm2->nextTerm;	
		}
		
		ptrTerm1 = ptrTerm1->nextTerm;
	}
	
	// ����������ʽp
	PolynomialTerm<N, C>* ptrTerm = p.listHead;
	for (N i = 0; i <= maxDeg; i++) {
		if (std::fabs(tmpResult[i]) > 1e-6) { // �������Ԫ�ط�0������������ʽ
			ptrTerm->nextTerm = new PolynomialTerm<N, C>(tmpResult[i], i);
			ptrTerm = ptrTerm->nextTerm;	
		}
	}
	
	delete[] tmpResult;  // ɾ����ʱ����
	return p;
}

/**
 * @brief �˷�
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
 * @brief ���<<����
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
