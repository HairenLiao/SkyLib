/** @file   sky_binary_search_tree.h 
 *  @brief  Inteface of all linear lists     
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

#ifndef _SKY_BINARY_SEARCH_TREE_H
#define _SKY_BINARY_SEARCH_TREE_H  1

#include <iostream>

namespace sky {

template <typename T>
class BinarySearchTree
{
    struct BinaryNode {
        T element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode (const T& elem, BinaryNode *lt, BinaryNode *rt) : element(elem), left(lt), right(rt) {}
    };

    BinaryNode *root;
    void insert(const T& x, BinaryNode* &t) const;
    void remove(const T& x, BinaryNode* &t) const;
    BinaryNode* findMin(BinaryNode *t) const {
        if (t == NULL)
            return NULL;
        if (t->left == NULL)
            return t;
        return finMin(t->left);
    }

    BinaryNode* findMax(BinaryNode *t) const {
        if (t == NULL)
            return NULL;
        if (t->right == NULL)
            return t;
        return findMax(t->right);
    }

    bool contains(const T& x, BinaryNode *t) const;
    void makeEmpty(BinaryNode* &t) {
        if (t != NULL ) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }
    void printTree(BinaryNode *t, int level) const;
    BinaryNode* clone(BinaryNode *t) const {
    	if (t == NULL)
    		return NULL;
    	BinaryNode* newNode = new BinaryNode(t->element, clone(t->left), clone(t->right));
    	return newNode;
    }
    
    int count(BinaryNode* t) const {
    	if (t == NULL)
    		return 0;
    	return 1 + count(t->left) + count(t->right);
    }
public:
    BinarySearchTree() : root(NULL){ }
    BinarySearchTree(const BinarySearchTree& rhs) {
    	root = clone(rhs.root);
    }
    ~BinarySearchTree() {
        makeEmpty(root);
    }

    const T& findMin() const { return findMin(root); }
    const T& findMax() const { return findMax(root); }
    bool contains(const T& x) const { return contains(x, root); }
    bool isEmpty() const { return root == NULL ;}
    void printTree() const { printTree(root, 0); }
    void makeEmpty() { makeEmpty(root); }
    void insert(const T& x) { insert(x, root); }
    void remove(const T& x) { remove(x, root); }
    int length() const {
    	return count(root);
    }
    const BinarySearchTree& operator=(const BinarySearchTree& rhs) {
    	if (this != &rhs){
    	    makeEmpty();
    	    root = clone(rhs.root);
    	}
    	return *this;
    }
};

template <typename T>
bool BinarySearchTree<T>::contains(const T& x, BinaryNode *t) const {
     if (t == NULL)
         return false;
     else if (x < t->element)
         return contains(x, t->left);
     else if (x > t->element)
         return contains(x, t->right);
     else
         return true;
}

/*
template <typename T> 
BinaryNode* BinarySearchTree<T>::findMin(BinaryNode *t) const {
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return finMin(t->left);
}
*/

template <typename T>
void BinarySearchTree<T>::insert(const T& x, BinaryNode* &t) const {
    if (t == NULL)
        t = new BinaryNode(x, NULL, NULL);
    else if ( x < t->element )
        insert(x, t->left);
    else if ( x > t->element )
        insert(x, t->right);
    else
        ;  // Duplicate, do nothing
}

// Remove element from a tree node
template <typename T>
void BinarySearchTree<T>::remove(const T& x, BinaryNode* &t) const {
	if (t == NULL)
		return;
	
	if (x < t->element)
		remove(x, t->left);
	else if (x > t->element)
		remove(x, t->right);
	else if (t->left != NULL && t->right != NULL) {
		// Recursively replace the data of this node with the smallest data of the right substree
		// and recursively delete that node (wich is now empty
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else {
		BinaryNode* oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
}

// Print binary tree
template <typename T>
void BinarySearchTree<T>::printTree(BinaryNode* t, int level) const {
	if (t != NULL) {
		printTree(t->left, level+1);
		for (int i = 0; i <= level; i++)
			std::cout << " ";
		std::cout << t->element << std::endl;
		printTree(t->right, level+1);
	}
}


}

#endif
