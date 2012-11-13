/** 
 *  @file   sky_indirect_list.h 
 *  @brief  Implementation of Indirect Linear List     
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
 *  IndirectList
 *  ��ӱ�
 */

#ifndef _SKY_INDIRECT_LIST_H
#define _SKY_INDIRECT_LIST_H  1

#include <iostream>

namespace sky {

const int DEFAULT_MAX_INDIRECT_LIST_SIZE = 10;

template <typename T>
class IndirectList{
    T **table;
    int len;
    int maxSize;
    int current;
public:
    IndirectList(int maxListSize = DEFAULT_MAX_INDIRECT_LIST_SIZE);
    ~IndirectList();
    bool atEnd() const   { return  current == len ; }
    bool setPos(int pos);
    bool getData(T&) const; 
    bool setData(const T&);
    bool insert(const T&);
    bool insertRear(const T&);
    bool remove(T&);
    void clear();
    int  search(const T&) const;              //Search an item from start to the end
    void setStart() { current = 0;   }
    void setEnd()   { current = len; }
    void prev() { 
    	if (current != 0 ) 
    	    current--;
    }
    
    // current cannot be greater  than length
    void next() { 
    	if (current < len) 
    	    current++; 
    } 
    void output() const;
};

template <typename T>
IndirectList<T>::IndirectList(int maxListSize){
    maxSize = maxListSize;
    table = new T *[maxSize];   // table is pointer to an array of T pointers
    len = 0;
    current = 0;
}
    
template <typename T>
IndirectList<T>::~IndirectList() {
    for (int i = 0; i < len; i++)
	   delete table[i];        //delete real data
    delete[] table;             //delete table
}

// clear(). Clear all data.Reset list;
template <typename T>
void IndirectList<T>::clear() {
    for (int i = 0; i < len; i++)
	delete table[i];        //delete real data
    len = current = 0;                      //table need not be deleted.
}

// setPos(int). Same with that of SeqList
template <typename T>
bool IndirectList<T>::setPos(int pos) {
    if (pos >= 0 && pos <= len) {   
       current = pos;              
       return true;              
    }
    
    return false;
}      

// �õ�currentλ�õ�ֵ
template <typename T>
bool IndirectList<T>::getData(T& x) const {
     if (current == len) 
         return false;                    // At end of list,no data to get.
     x = *(table[current]);            // Else...
     return true;
}

// ����currentλ�õ�ֵ
template <typename T>
bool IndirectList<T>::setData(const T& x) {
     if (current == len) 
         return false;                    // At end of list,no data to get.
     *(table[current]) = x;               // Else...
     return true;
}

// ����ֵ����ǰλ��
template <typename T>
bool IndirectList<T>::insert(const T& x) {
    if (len == maxSize) {
    	maxSize = 2*len;
	    T** newTable=new T *[maxSize];
	    if (!newTable)                          // If allocation fails, return false
	        return false;                 
	    
	    for(int i = 0; i < len; i++)            // Copy indices of old array to those of new one
	        newTable[i] = table[i];
	    
	    delete[] table;  
	    table = newTable;  
    }
 
    for (int i = len; i > current; i--)               // Shift indices rightward
	    table[i] = table[i-1];
    
    table[current] = new T;
    *table[current] = x;
    len++;
    return true;
}

// ����ֵ�����Ա�ĩβ
template <typename T>
bool IndirectList<T>::insertRear(const T& x) {
    if (len == maxSize) {
    	maxSize = 2*len;
	    T** newTable=new T *[maxSize];
	    if (!newTable)                          // If allocation fails, return false
	        return false;                 
	    
	    for(int i = 0; i < len; i++)            // Copy indices of old array to those of new one
	        newTable[i] = table[i];
	    
	    delete[] table;  
	    table = newTable;  
    }
 
   
    table[len] = new T;
    *table[len] = x;
    len++;
    return true;
}

// ɾ����ǰλ�õ�ֵ
template <typename T>
bool IndirectList<T>::remove(T& x){
    if (current == len) 
	    return false;           
    
    x = *table[current];                     // Copy removed item
    delete table[current];

    for (int i = current; i < len-1; i++)    // Shift data leftward
	   table[i] = table[i+1];

    len--;                                    // Decrease length
    return true;
}

// ����ĳֵ��λ��
template <typename T>
int IndirectList<T>::search(const T& x) const {
      int i;
      for (i = 0; i < len; i++) {
	      if ( *(table[i]) == x) 
	          return i;
      }

      return -1;
}

// �����Ԫ��
template <class T>
void IndirectList<T>::output() const{
    int i = 0;
    
    std::cout<<"( ";
    
    while (i < current) 
    	std::cout << *table[i++] << " ";
    
    std::cout<<"| ";
    
    while (i < len) 
    	std::cout << *table[i++] << " ";
    
    std::cout <<")" << std::endl;
}

}  // namespace sky

#endif   /*  _SKY_INDIRECT_LIST_H  */
