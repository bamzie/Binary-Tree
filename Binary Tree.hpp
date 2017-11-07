//
//  Binary Tree.hpp
//  Binary Tree
//
//  Created by Brian Morales on 7/14/16.
//  Copyright © 2016 Brian Morales. All rights reserved.
//

#ifndef Binary_Tree_hpp
#define Binary_Tree_hpp
#include <stdio.h>
#include <iostream>
using namespace std;

template <class T>
class BinaryTree
{
private:
    
    struct TreeNode
    {
        int value;
        TreeNode *right;
        TreeNode *left;
    };
    
    TreeNode *root;
    
    void insert( TreeNode *&, TreeNode *&);
    void destroySubTree( TreeNode *);
    void deleteNode (T, TreeNode *&);
    void makeDeletion( TreeNode *&);
    void displayInOrder(TreeNode *) const;
    void displayPreOrder(TreeNode *) const;
    void displayPostOrder(TreeNode *) const;
    
public:
    // Constructor
    BinaryTree()
    { root = NULL;}
    
    // Destructor
    ~BinaryTree()
    { destroySubTree(root);}
    
    // Binary Options/ Mutators
    void insertNode( T );
    bool searchNode( T );
    void remove(T);
    
    void displayInOrder() const
    { displayInOrder(root);}
    
    void displayPreOrder() const
    {  displayPreOrder(root);}
    
    void displayPostOrder() const
    { displayPostOrder(root);}
};

/***************************************************************************
*Insert accepts a TreeNode pointer and a pointer to a node.                *
*The Function inserts the node into the tree pointed by the TreeNode pointer.
*This Function is called recursivley.                                      *
****************************************************************************/
template <class T>
void BinaryTree<T>:: insert(TreeNode *&nodePtr, TreeNode *&newNode)
{
    if (nodePtr == NULL)
        nodePtr = newNode;                      // Insert node
    else if (newNode->value < nodePtr->value)
        insert(nodePtr->left, newNode);         //Search the left branch
    else
        insert(nodePtr->right, newNode);        //Search the right branch
}

/****************************************************************************
*insertNode creates a new node to hold num as its value, and passes         *
*it to the insert function.                                                 *
*****************************************************************************/
template <class T>
void BinaryTree<T>::insertNode(T item)
{
    TreeNode *newNode;                          // Pointer to a new node.
    
    //Create a new node and store itemin it.
    newNode = new TreeNode;
    newNode->value = item;
    newNode->left = newNode->right = NULL;
    
    // Insert the node.
    insert(root, newNode);
}

/*****************************************************************************
*destroySubTree is called by the destructor. It deletes all nodes in the tree.
******************************************************************************/
template<class T>
void BinaryTree<T>::destroySubTree(TreeNode *nodePtr)
{
    if (nodePtr)
    {
        if (nodePtr->left)
            destroySubTree(nodePtr->left);
        if (nodePtr->rigt)
            destroySubTree(nodePtr->right);
        delete nodePtr;
    }
}

/*****************************************************************************
*seachNode determine if a value is present in the tree. If so, the function  *
*returns true. Otherwise, it returns false.                                  *
******************************************************************************/
template<class T>
bool BinaryTree<T>::searchNode(T item)
{
    TreeNode *nodePtr = root;
    
    while(nodePtr)
    {
        if (nodePtr->value == item)
            return true;
        else if(item < nodePtr->value)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
    
    return false;
}

/****************************************************************************
*remove calls deleteNode to delete the node whose value member is the same as
* item.                                                                     *
*****************************************************************************/
template<class T>
void BinaryTree<T>::remove(T item)
{
    deleteNode(item, root);
}

/***************************************************************************
*deleteNode deletes the node whose value member is the same as num.        *
****************************************************************************/
template<class T>
void BinaryTree<T>::deleteNode(T item, TreeNode *&nodePtr)
{
    if (item < nodePtr->value)
        deleteNode(item, nodePtr->left);
    else if (item > nodePtr->value)
        deleteNode(item, nodePtr->right);
    else
        makeDeletion(nodePtr);
}

/***************************************************************************
*makedeletion takes a reference to a pointer to the node that is to be     *
*deleted. The node is removed and the branches of the tree below the node  *
*are reatched.                                                             *
****************************************************************************/
template <class T>
void BinaryTree<T>::makeDeletion(TreeNode *&nodePtr)
{
    // Define the temporary pointer to use in reattaching
    // the left subtree.
    TreeNode *tempNodePtr;
    
    if(nodePtr == NULL)
        cout << "Cannot delete empty node. \n";
    else if (nodePtr->right == NULL)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->left;                // Reattach the left child
        delete tempNodePtr;
    }
    else if(nodePtr->left == NULL)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;               // Reattach the right child
        delete tempNodePtr;
    }
    // If the node has two children.
    else
    {
        // Move one node to the right.
        tempNodePtr = nodePtr->right;
        
        //Go to the end left node.
        while(tempNodePtr->left)
            tempNodePtr = tempNodePtr->left;
        
        //Reattach the left subtree
        tempNodePtr->left = nodePtr->left;
        tempNodePtr = nodePtr;
        
        //Reattach the right subtree.
        nodePtr = nodePtr->rigt;
        delete tempNodePtr;
    }
    
}

/**************************************************************************
*The displayInOrder member function displays the values in the subtree    *
*pointed to by nodePtr, via inorder traversal.                            *
***************************************************************************/
template<class T>
void BinaryTree<T>::displayInOrder(TreeNode *nodePtr) const
{
    if(nodePtr)
    {
        displayInOrder(nodePtr->left);
        cout << nodePtr->value << endl;
        displayInOrder(nodePtr->right);
    }
}

/*************************************************************************
*The displayPreOrder memebr function displays the values in the subtree  *
*pointed to by nodePtr, via preorder traversal.                          *
**************************************************************************/
template<class T>
void BinaryTree<T>::displayPreOrder(TreeNode *nodePtr) const
{
    if (nodePtr)
    {
        cout << nodePtr->value << endl;
        displayPreOrder(nodePtr->left);
        displayPostOrder(nodePtr->right);
    }
}

/************************************************************************
*The displayPostOrder member function displays the values in the subtree*
*pointed to by nodePtr, via PostOrder traversal.                        *
*************************************************************************/
template<class T>
void BinaryTree<T>::displayPostOrder(TreeNode *nodePtr) const
{
    if (nodePtr)
    {
        displayPostOrder(nodePtr->left);
        displayPostOrder(nodePtr->right);
        cout << nodePtr->value << endl;
    }
}
#endif /* Binary_Tree_hpp */
