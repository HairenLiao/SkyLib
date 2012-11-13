/** 
 *  @file   sky_hash_table.h
 *  @brief  Implementation of Hash Table
 *  @author Hairen Liao(�κ��ʣ� <liaohairen@gmail.com>
 *  
 *  Copyright (c) 2012
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
 *  HashTable
 *  Hash�� 
 */

#ifndef _SKY_HASH_TABLE_H
#define _SKY_HASH_TABLE_H  1

#include <vector>
#include <list>
#include <string>

namespace sky {

template <typename T>
class HashTable {
	std::vector<std::list<T> > theLists;
	int currentSize;
	
	void rehash();
	int myhash(const T& x) const;
	
public:
	explicit HashTable(int size = 101) : theLists(size){}
	
	bool contains( const T& x) const;
	void makeEmpty();
	bool insert(const T& x);
	bool remove(const T& x);
};

template <typename T> 
int HashTable<T>::myhash(const T& x) const {
    int hashVal = hash(x);
    
    hashVal %= theLists.size();
    if (hashVal < 0)
    	hashVal += theLists.size();
    
    return hashVal;
}

template <typename T> 
void HashTable<T>::makeEmpty() {
	for (int i = 0; i < theLists.size(); i++)
		theLists[i].clear();
}

template <typename T> 
bool HashTable<T>::contains(const T& x) const {
	const std::list<T>& whichList = theLists[ myhash(x) ];
	return std::find(whichList.begin(), whichList.end(), x) != whichList.end();
}

template <typename T> 
bool HashTable<T>::remove(const T& x) {
	std::list<T>& whichList = theLists[ myhash(x) ];
	
	typedef typename std::list<T>::iterator iterator; 
	iterator itr = std::find(whichList.begin(), whichList.end(), x);
	
	if (itr == whichList.end())
		return false;
	
	whichList.erase(itr);
	--currentSize;
	return true;
}

template <typename T> 
bool HashTable<T>::insert(const T& x) {
	std::list<T>& whichList = theLists[ myhash(x) ];
	
	// x has already, return false without doing anything
	if (std::find(whichList.begin(), whichList.end(), x) != whichList.end())
		return false;
	
	whichList.push_front(x);
	
	if (++currentSize > theLists.size())
		rehash();
	
	return true;
}

template <typename T> 
void HashTable<T>::rehash() {
	std::vector<std::list<T> > oldLists = theLists;
	theLists.resize( 2 * theLists.size() + 1) ;  // nextPrime()
	for (int j = 0; j < theLists.size(); j++)
		theLists[j].clear();
	
	// Copy table over
	currentSize = 0;
	typedef typename std::list<T>::iterator iterator;
	for (int i = 0; i < oldLists.size(); i++) {
		iterator itr = oldLists[i].begin();
		while (itr != oldLists[i].end())
			insert(*itr++);
	}
}

int hash(const std::string& key) {
	int hashVal = 0;
		
	for (int i = 0; i < key.length(); i++)
		hashVal = 37 * hashVal + key[i];
		
	return hashVal;
}
	
int hash(int key) {
	return key;
}

class Employee {
	std::string name;
	double salary;
	int seniority;
public:
	Employee(std::string theName, double theSalary, int theSeniority) : name(theName), salary(theSalary), seniority(theSeniority) {}
	const std::string& getName() const { return name; }
	
	bool operator==(const Employee& rhs) const {
		return getName() == rhs.getName();
	}
	
	bool operator!=(const Employee& rhs) const {
		return !(*this == rhs);
	}
};

int hash(const Employee& item) {
    return hash(item.getName()); 	
}



} // namespace sky 

#endif
