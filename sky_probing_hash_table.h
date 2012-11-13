/** 
 *  @file   sky_probing_hash_table.h
 *  @brief  Implementation of Hash Table with Probing stategies
 *  @author Hairen Liao(廖海仁） <liaohairen@gmail.com>
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
 *  本库为作者本人学习数据结构与算法所写，模拟STL标准库，并力求得其精神，不拘其细节。 同时也希望本库对其他初学
 *  数据结构与算法者有所帮助，因此写了相当多的注释和说明。本库属于自由软件，您基本可以自由使用，但作者不为本库的
 *  正确性及其使用做任何担保，包括使用此库完成作业时被视为抄袭。 同时作者也非常乐于听到您的反馈和改进意见。
 *  
 */

/** 
 *  ProbingProbingHashTable
 *  Hash表 
 */

#ifndef _SKY_PROBING_HASH_TABLE_H
#define _SKY_PROBING_HASH_TABLE_H  1

#include <vector>
#include <list>
#include <string>

namespace sky {

template <typename T>
class ProbingHashTable {
public:
	explicit ProbingHashTable(int size = 101) : array(size) { makeEmpty(); }
	
	bool contains( const T& x) const;
	void makeEmpty();
	bool insert(const T& x);
	bool remove(const T& x);
	
	enum EntryType{ACTIVE, EMPTY, DELETED};

private:
	struct HashEntry {
		T element;
		EntryType info;
		
		HashEntry(const T& e=T(), EntryType i = EMPTY) : element(e), info(i) {}
	};
	
	std::vector<HashEntry> array;
	int currentSize;
	
	bool isActive(int currentPos) const { return array[currentPos].info == ACTIVE; }
	int findPos(const T& x) const;
	void rehash();
	int myhash(const T& x) const;
	

	
};

template <typename T> 
int ProbingHashTable<T>::myhash(const T& x) const {
    int hashVal = hash(x);
    
    hashVal %= array.size();
    if (hashVal < 0)
    	hashVal += array.size();
    
    return hashVal;
}

template <typename T> 
void ProbingHashTable<T>::makeEmpty() {
	for (int i = 0; i < array.size(); i++)	
		array[i].info = EMPTY;
}

template <typename T> 
bool ProbingHashTable<T>::contains(const T& x) const {
	return isActive( findPos(x) );
}

template <typename T> 
int ProbingHashTable<T>::findPos(const T& x) const {
	int offset = 1;
	int currentPos = myhash(x);
	
	while (array[currentPos].info != EMPTY &&
		   array[currentPos].element != x)
	{
		currentPos += offset;
		offset += 2;
		if (currentPos >= array.size())
			currentPos -= array.size();
	}
	
	return currentPos;
}

template <typename T> 
bool ProbingHashTable<T>::remove(const T& x) {
	int currentPos = findPos(x);
	if (!isActive(currentPos))
		return false;
	
	array[currentPos].info = DELETED;
	return true;
}

template <typename T> 
bool ProbingHashTable<T>::insert(const T& x) {
	int currentPos = findPos(x);
	if (isActive(currentPos))
		return false;
	
	array[currentPos] = HashEntry(x, ACTIVE);
	
	if (++currentSize > array.size() / 2)
		rehash();
	
	return true;
}

template <typename T>  
void ProbingHashTable<T>::rehash() {
	std::vector<HashEntry> oldArray = array;
	array.resize( 2 * array.size() + 1) ;  // nextPrime()
	for (int j = 0; j < array.size(); j++)
		array[j].info = EMPTY;
	
	currentSize = 0;
	for (int i = 0; i < array.size(); i++) {
		if (oldArray[i].info == ACTIVE)
			insert(oldArray[i].element);
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

} // namespace sky 

#endif
