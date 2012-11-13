/** @file   sky_avl_tree.h 
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

#ifndef _SKY_AVL_TREE_H
#define _SKY_AVL_TREE_H  1

#include <iostream>

namespace sky {

template <typename T>
class AvlTree
{
    struct AvlNode {
        T element;
        AvlNode *left;
        AvlNode *right;
        int height;
        AvlNode (const T& elem, AvlNode *lt, AvlNode *rt, int h=0) : element(elem), left(lt), right(rt), height(h) {}
    };

    AvlNode *root;
    void insert(const T& x, AvlNode* &t);
    void remove(const T& x, AvlNode* &t) const;
    AvlNode* findMin(AvlNode *t) const {
        if (t == NULL)
            return NULL;
        if (t->left == NULL)
            return t;
        return finMin(t->left);
    }

    AvlNode* findMax(AvlNode *t) const {
        if (t == NULL)
            return NULL;
        if (t->right == NULL)
            return t;
        return findMax(t->right);
    }

    bool contains(const T& x, AvlNode *t) const;
    void makeEmpty(AvlNode* &t) {
        if (t != NULL ) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }
    void printTree(AvlNode *t, int level) const;
    AvlNode* clone(AvlNode *t) const {
    	if (t == NULL)
    		return NULL;
    	AvlNode* newNode = new AvlNode(t->element, clone(t->left), clone(t->right));
    	return newNode;
    }
    
    int count(AvlNode* t) const {
    	if (t == NULL)
    		return 0;
    	return 1 + count(t->left) + count(t->right);
    }
    
    int height(AvlNode* t) const {
    	return t==NULL ? -1 : t->height;
    }
    
    int max(int a, int b) const {
    	return a > b ? a : b;
    }
    
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode* &k2) {
        AvlNode *k1 =k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height(k2->left), height(k2->right)) + 1;
        k1->height = max( height(k1->left), k2->height) + 1;
        k2 = k1;
    }
    
    /**
     * Rotate binary tree node with right child 
     * For AVL tree, this is a single rotation for case 4
     * Update heights, then set new root
     */
    void rotateWithRightChild(AvlNode* &k1) {
    	AvlNode *k2 = k1->right;
    	k1->right = k2->left;
    	k2->left = k1;
    	k1->height = max( height(k1->left), height(k1->right)) + 1;
    	k2->height = max( height(k2->right), k1->height) + 1;
    	k1 = k2;
    }
    
    /**
     * Double rotate binary tree node: first left child
     * with its right child; then node k3 with new left child
     * For AVL trees, this is a double rotation for case 2.
     * Update height, then set new root
     */
    void doubleWithLeftChild( AvlNode* &k3) {
    	rotateWithRightChild(k3->left);
    	rotateWithLeftChild(k3);
    }
    
    /**
     * Double rotate binary tree node: first right child
     * with its left child; then node k3 with new right child
     * For AVL trees, this is a double rotation for case 3.
     * Update height, then set new root
     */
     void doubleWithRightChild( AvlNode* &k1) {
         rotateWithLeftChild(k1->right);
         rotateWithRightChild(k1);
     }
  
public:
    AvlTree() : root(NULL){ }
    AvlTree(const AvlTree& rhs) {
    	root = clone(rhs.root);
    }
    ~AvlTree() {
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
    const AvlTree& operator=(const AvlTree& rhs) {
    	if (this != &rhs){
    	    makeEmpty();
    	    root = clone(rhs.root);
    	}
    	return *this;
    }
};

template <typename T>
bool AvlTree<T>::contains(const T& x, AvlNode *t) const {
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
AvlNode* AvlTree<T>::findMin(AvlNode *t) const {
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return finMin(t->left);
}
*/

template <typename T>
void AvlTree<T>::insert(const T& x, AvlNode* &t) {
    if (t == NULL)
        t = new AvlNode(x, NULL, NULL);
    else if ( x < t->element ) {
        insert(x, t->left);
        if (height(t->left) - height(t->right) == 2)
        	if (x < t->left->element)
        		rotateWithLeftChild(t);
        	else
        		doubleWithLeftChild(t);
    }
    else if ( x > t->element ) {
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2)
        	if ( x > t->right->element)
        		rotateWithRightChild(t);
        	else
        		doubleWithRightChild(t);
    }
    else
        ;  // Duplicate, do nothing
    t->height = max( height(t->left), height(t->right)) + 1;
}

// Remove element from a tree node
template <typename T>
void AvlTree<T>::remove(const T& x, AvlNode* &t) const {
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
		AvlNode* oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
}

// Print binary tree
template <typename T>
void AvlTree<T>::printTree(AvlNode* t, int level) const {
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
