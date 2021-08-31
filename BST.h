
#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>

#include "LinkedList.h"

using namespace std;


/*****************************************************************************/
/*                                                                           */
/* PROTOTYPES                                                                */
/*                                                                           */
/*****************************************************************************/

// only BinarySearchTree class can create Node objects
class Node {
  
	friend class BST;

private:

    // data in the Node
	int data;

    // child nodes
  	Node* left, *right;

	// left and right threads
	//if lthread is set to false, then there is a thread in the left direction
	//if rthread is set to false, then there is a thread in the right direction
	// if either is true, then there is a node in that direction
	bool lthread, rthread;

	int count; //couns the number of nodes present in its right subtree


public:
  // constructors

  //Default no arg constructor of Node.
  Node();

  // Constructor with data in argument.
  Node(const int& data);

}; 


class BST {

private:

  // pointer to the root of the BST
  Node* root;

   
public:
  // constructor and destructors

  // Creates BST object with dummy node
  BST();

  //copy constructor
  BST(const BST &tree);

  // Destructor for BST
  virtual ~BST();


  //BST Methods

  
  // Creates a new instance of tree and is identical copy
  void copyTree( Node* oldTreeRoot);

  // To traverse and delete all nodes in tree.
  void clear(Node* root);

  //Finds a target node in a tree.
  Node* search(Node* treePtr, const int target) const;

  //To reroute parent pointers if target has no children.
  void deleteNoChild(Node* ptr, Node* parent);

  //To reroute parent pointers if target has a child node.
  void deleteOneChild(Node* ptr, Node* parent);

  // To delete a node with two children nodes, link them to the parent, and thread them accordingly.
  void deleteTwoChild(Node* ptr);

  // Looks for the next successor of the target node.
  Node* inorderSuccessor(Node* ptr);

  // Looks for the predecessor the the target node.
  Node* inorderPredecessor(Node* ptr);

  
  // Conducts inorder traversal of tree and stores all node datas in order. 
  LinkedList* inorder();

  // Inorder traversal of tree in the reverse order from max to min 
  LinkedList* reverseInorder();
  
 //Return all the elements in the specified range
  LinkedList rangeTraversal(int k1, int k2);

  //To split the BST into 2 BSTs T1 and T2 where keys(T1)<=k and keys(T2)>k
  void split(int k);

  void setChild(Node *node, bool toLeft, Node *child);

  Node* splitTree(Node *root, int k);

  vector<Node*> splitBST_Iterative(int k);

  vector<Node*> splitBST_Recursive(Node* root, int k);

  //Interface methods

  // To add a new element of int value into the tree as a node.
  bool insert(const int newData);

  // To remove the node with provided data value.
  bool remove(const int data);

  // Return a boolean indicating if a target Entry is present
  bool contains(const int anEntry) const;
  

  //Returns the kth largest element in the tree
  void kthLargest(int k);

  vector<Node*> splitBST(int k);

  void write(Node *root, ofstream &myfile);

  void printTree();
};
#endif