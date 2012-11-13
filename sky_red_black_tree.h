/** @file   sky_red_black_tree.h 
 *  @brief  Implematation of Red Black Tree     
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

#ifndef _SKY_RED_BLACK_TREE_H
#define _SKY_RED_BLACK_TREE_H  1

#include <iostream>

namespace sky {

template <typename T>
class RedBlackTree
{
    struct RedBlackNode {
        T element;
        RedBlackNode *left;
        RedBlackNode *right;
        int color;
        RedBlackNode (const T& elem = T(), RedBlackNode *lt = NULL,
        		      RedBlackNode *rt = NULL, int c = BLACK) 
        : element(elem), left(lt), right(rt), color(c) {}
    };

    RedBlackNode *header;
    RedBlackNode *nullNode;
    
    // Used in insert routine and its helpers (logically static)
    RedBlackNode *current;
    RedBlackNode *parent;
    RedBlackNode *grand;
    RedBlackNode *great;
    
    // Usual recursive stuff
    void reclaimMemory( RedBlackNode *t );
    void printTree( RedBlackNode* t) const;
    
    RedBlackNode* clone(RedBlackNode *t) const {
        if (t == NULL)
        	return NULL;
        RedBlackNode* newNode = new RedBlackNode(t->element, clone(t->left), clone(t->right));
        return newNode;
   }
    
    // Red-black tree manipulations
    
    /**
     * Internal routine that is called during an insertion if a node has two red children.
     * Performs flip and rotations. item is item being inserted.
     */
    void handleReorient( const T& item) {
    	current->color = RED;
    	current->left->color = BLACK;
    	current->right->color = BLACK;
    	
    	if (parent->color == RED) {
    		grand->color = RED;
    		if (item < grand->element != item < parent->element)
    			parent = rotate(item, grand);
    		current = rotate(item, great);
    		current->color = BLACK;
    	}
    	header->right->color = BLACK;
    }
    
    /**
     * Internal routine that performs a single or double rotation.
     * Because the result is attached to the parent, there are four cases
     * Called by handleReorient.
     * item is item in handleReorient
     * theParent is the parent of the root of the rotated subtree.
     * Return the root of the rotated subtree.
     * 
     */
    RedBlackNode* rotate(const T& item, RedBlackNode* theParent) {
    	if (item < theParent->element) {
    		item < theParent->left->element ?
    			rotateWithLeftChild( theParent->left) :
    			rotateWithRightChild( theParent->left);
    		return theParent->left;
    	}
    	else {
    		item < theParent->right->element ?
    		    rotateWithLeftChild( theParent->right) :
    		    rotateWithRightChild( theParent->right);
    		return theParent->right;
    	}
    }
    
    void rotateWithLeftChild(RedBlackNode* &k2);
    void rotateWithRightChild(RedBlackNode* &k1);
      
public:
    explicit RedBlackTree(const T& negInf) {
    	nullNode = newBlackNode;
    	nullNode->left = nullNode->right = nullNode;
    	header = new RedBlackNode( negInf );
    	header->left = header->right = nullNode;
    }
    RedBlackTree(const RedBlackTree& rhs);
    ~RedBlackTree();

    const T& findMin() const;
    const T& findMax() const;
    bool contains(const T& x) const;
    bool isEmpty() const;
    void printTree() const;
    void makeEmpty(); 
    void insert(const T& x);
    void remove(const T& x);  
    enum {RED, BLACK};
    const RedBlackTree& operator=( const RedBlackTree& rhs); 
};

template <typename T>
bool RedBlackTree<T>::contains(const T& x, RedBlackNode *t) const {
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
RedBlackNode* RedBlackTree<T>::findMin(RedBlackNode *t) const {
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return finMin(t->left);
}
*/

template <typename T>
void RedBlackTree<T>::insert(const T& x) {
	current = parent = grand = header;
	nullNode->element = x;
	
	while (current->element != x) {
		great = grand;
		grand = parent;
		parent = current;
		current = x < current->element ? current->left : current->right;
		
		if (current->left->color == RED && current->right->color == RED)
			handleReorient(x);
	}
	
	if (current != nullNode)
		return;
	
	current = new RedBlackNode(x, nullNode, nullNode);
	
	if (x < parent->element)
		parent->left = current;
	else
		parent->right = current;
	handleReorient(x);
    
}

// Remove element from a tree node
template <typename T>
void RedBlackTree<T>::remove(const T& x, RedBlackNode* &t) const {
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
		RedBlackNode* oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
}

// Print binary tree
template <typename T>
void RedBlackTree<T>::printTree(RedBlackNode* t, int level) const {
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
