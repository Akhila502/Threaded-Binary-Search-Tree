// BST_214101050.cpp : Defines the entry point for the console application.
//


/* Standard includes */

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <fstream>

/* Project includes */

#include "BST.h"

using namespace std;

/*****************************************************************************/
/*                                                                           */
/* CONSTRUCTORS                                                              */
/*                                                                           */
/*****************************************************************************/

Node::Node() 
{
	data = 0;
	count = 0;
	left = this;
	right = this;
	lthread = false;
	rthread = false;
}

Node::Node(const int& newdata)  
{
	data = newdata;
	count = 0;
	left = nullptr;
	right = nullptr;
	lthread = false;
	rthread = false;
}

// Create a null instance of BST and allocate dummy node
BST::BST(){

    root = new Node();
    root->rthread = false;
    root->lthread = false;
    root->left = root;
    root->right = root;
}

// Copy constructor 
BST::BST(const BST& tree) {
    // call to copyTree method that copies the tree
    copyTree(tree.root->left);
} 

// Destructor for BST.
// Tree is empty and all nodes are deleted properly with no memory leaks.
BST::~BST() {
    clear(root);
} 

// Creates a new instance of tree and is identical copy
void BST::copyTree(Node* oldTreeRoot) {

    if (oldTreeRoot->data == root->data)
        return;
    insert(oldTreeRoot->data);

    if (oldTreeRoot->lthread)
        copyTree(oldTreeRoot->left);

    if (oldTreeRoot->rthread)
        copyTree(oldTreeRoot->right);
}

/*****************************************************************************/
/*                                                                           */
/* FUNCTIONS                                                                 */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
 /*                                                                           */
 /* function "insert"                                                         */
 /*                                                                           */
 /* bool insert(const int newData)                                            */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To add a new element of int value into the tree as a node.             */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Integer value to be inserted                                           */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*   TRUE for succesful insertion, otherwise FALSE                           */
 /*                                                                           */
 /*****************************************************************************/

bool BST::insert(const int newData) {
    Node* temp = new Node(newData);
    // check if the tree is empty
    if ((root->left == root) && (root->right == root)) {
        // At this point the tree is empty and only has dummy node
        // Reroute all pointers of root to temp
        temp->left = root->left;
        temp->right = root->right;
        // Insert temp into tree
        root->left = temp;
        root->lthread = true;
		return true;
    }
    // Tree is not empty so we will add it
    Node* ptr = root->left;

    while (true) {
        // check for duplicate value if already present in the tree
        if (newData == ptr->data) {
			//if duplicate is present, then do not add the new node and remove it 
            delete temp;
            temp = nullptr;
            return false;
        }

        // if value is larger than the current node data then insert or move to the right
        if (newData > ptr->data) 
		{
			
			ptr->count++;
            if (!ptr->rthread) 
			{
                temp->right = ptr->right;
                temp->rthread = ptr->rthread;
                temp->lthread = false;

                //Point to inorder successor 
                temp->left = ptr;
                ptr->rthread = true;
                ptr->right = temp;
				return true;
            }
			else 
			{
				ptr = ptr->right;
			}
        } 
        
        // if value is smaller than current node data then insert or move left
        if (newData < ptr->data) 
		{
            if (!ptr->lthread) 
			{
                // At this point we know that the left does not point to any inorder predecessor. 
                temp->left = ptr->left;
                temp->lthread = ptr->lthread;
                temp->rthread = false;

                //Point to inorder successor 
                temp->right = ptr;
                ptr->lthread = true;
                ptr->left = temp;
				return true;
            }
			else 
			{
				ptr = ptr->left;
			}

        } 
    } 
} 

 /*****************************************************************************/
 /*                                                                           */
 /* function "search"                                                         */
 /*                                                                           */
 /* Node* search(Node* ptr, const int target) const                           */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    Finds a target node in a tree.                                         */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    pointer to a node and target data                                      */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*    pointer to target node or NULL pointer                                 */
 /*                                                                           */
 /*****************************************************************************/
              
Node* BST::search(Node* ptr, const int target) const {

	//If target data is found, return the pointer object
	while(ptr != root)
	{
		if(target == ptr->data)
			return ptr;
		else if(target < ptr->data)
			//checking if the left pointer is point to a predecessor
			if(ptr->lthread)
				ptr = ptr->left;
			else break;
		else if(target > ptr->data)
			//checking if the right pointer is pointing to the successor
			if(ptr->rthread)
				ptr = ptr->right;
			else break;
	}
    //when target data is not found, return the null pointer
    return nullptr;
}

/*****************************************************************************/
 /*                                                                           */
 /* function "contains"                                                       */
 /*                                                                           */
 /* bool contains(const int anEntry) const                                    */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    Return a boolean indicating if a target Entry is present               */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Node pointer                                                           */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*   TRUE if target found otherwise FALSE                                    */
 /*                                                                           */
 /*****************************************************************************/

bool BST::contains(const int data) const {
    //Return true if search returns a ptr and false if returns nullptr
    return (search(root->left, data) != nullptr) ? true : false;
}

/*****************************************************************************/
 /*                                                                           */
 /* function "remove"                                                         */
 /*                                                                           */
 /* bool remove(const int data)                                               */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To remove node with provided data value.                               */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Integer value to be deleted                                            */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*   TRUE for succesful deletion, otherwise FALSE                            */
 /*                                                                           */
 /*****************************************************************************/

bool BST::remove(const int data) {
    // Set parent to dummy node and our pointer to the real root
    Node* parent = root, *ptr = root->left;
    bool found = false;

    // Traverse tree until the target node is found and remember parent
    while (ptr != nullptr) {
        if (data == ptr->data) {
            found = true;   //We found the node
			if(ptr->count > 0)
				ptr->count --;
            break;
        }
        // assign parent before moving to the next node
        parent = ptr;

        // if data is less than current move left otherwise move right
        if (data < ptr->data){
            // check to see if at a leaf
            if (ptr->lthread == true) {
                ptr = ptr->left;
            }
            else break;
        }
        else {
            // check to see if at a leaf
            if (ptr->rthread == true) {
                ptr = ptr->right;
            }
            else break;
        } 
    } 
    // if not found then end method here and return false
    if (!found) 
		return false;
    
    // At this point we have the target node and we have its parent as well

    // Now we have to remove and link the new nodes depending on their children

    // If ptr has two children, then both threads will be true and we would need to
    // reroute the pointers for both children
    if (ptr->rthread && ptr->lthread) {
        deleteTwoChild(ptr);
    }
    //If ptr only has one child
    else if ((ptr->rthread && !(ptr->lthread))||(!(ptr->rthread) && (ptr->lthread))) {
        deleteOneChild(ptr, parent);
    }
 
    // If ptr has no children (is a leaf)
    else {
        deleteNoChild(ptr, parent);
    }
    // node removal is complete return true
	return true;
}
/*****************************************************************************/
 /*                                                                           */
 /* function "deleteNoChild"                                                  */
 /*                                                                           */
 /* void deleteNoChild(Node* ptr, Node* parent)                               */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To reroute parent pointers if target has no children.                  */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    pointer to the node and its parent                                     */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*    None.                                                                  */
 /*                                                                           */
 /*****************************************************************************/
void BST::deleteNoChild(Node* ptr, Node* parent) {
    // checks whether the target is the left or right child of the parent
    if (ptr == parent->left) {
        //Now the left thread of parent is a thread
        parent->lthread = false;
        parent->left = ptr->left;
    }
    else {
        //Now the right thread of parent is a thread
        parent->rthread = false;
        parent->right = ptr->right;
    } 
    delete ptr; //clear the pointer
    ptr = nullptr;
} 

/*****************************************************************************/
 /*                                                                           */
 /* function "deleteOneChild"                                                 */
 /*                                                                           */
 /* void deleteOneChild(Node* ptr, Node* parent)                              */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To reroute parent pointers if target has a child node.                 */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    pointer to the node and its parent                                     */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*    None.                                                                  */
 /*                                                                           */
 /*****************************************************************************/

void BST::deleteOneChild(Node* ptr, Node* parent) {
    Node* child;
    // check whether pointer has right or left child
    if (ptr->lthread) {
        child = ptr->left;
    }
    else {
        child = ptr->right;
    } 
	// Assign parents left or right pointer accordingly.
    if (ptr == parent->left) {
        parent->left = child;
    }
    else parent->right = child;

    // find successor and predecessor of the pointer node
    Node* successor = inorderSuccessor(ptr);
    Node* predecessor = inorderPredecessor(ptr);

    if (ptr->lthread) {
        predecessor->right = successor;
    }
    else if (ptr->rthread) successor->left = predecessor;
    
    delete ptr; // clean up ptr
    ptr = nullptr;
} 

/*****************************************************************************/
 /*                                                                           */
 /* function "deleteTwoChild"                                                 */
 /*                                                                           */
 /* void deleteTwoChild(Node* ptr, Node* parent)                              */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To delete the node with two children                                   */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    pointer to the node and its parent                                     */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*    None.                                                                  */
 /*                                                                           */
 /*****************************************************************************/
void BST::deleteTwoChild(Node* ptr) {
    // find the successor nodes for pointer and the parent
    Node* successor = ptr->right;
    Node* parentSuccessor = ptr;
    // traverse to the leftmost of the successor
    while (successor->lthread) {
        parentSuccessor = successor;
        successor = successor->left;
    } 
    ptr->data = successor->data;

    // checks if successor is a leaf
    if ((!successor->lthread) && !(successor->rthread)) deleteNoChild(successor, parentSuccessor);

    else deleteOneChild(successor, parentSuccessor);

} 

/*****************************************************************************/
 /*                                                                           */
 /* function "inorderSuccessor"                                               */
 /*                                                                           */
 /* Node* inorderSuccessor(Node* ptr)                                         */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    Looks for the next successor of the target node.                       */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    pointer to the node                                                    */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*    Successor is found and returned.                                       */
 /*                                                                           */
 /*****************************************************************************/

Node* BST::inorderSuccessor(Node* ptr) {
    //If there is a thread to the right, then return the next threaded node
    if (!ptr->rthread) {
        return ptr->right;
    }
    //If no thread then inorder successor is the leftmost node of the node to right
    ptr = ptr->right;
    while (ptr->lthread) {
        ptr = ptr->left;
    }
    return ptr;
}

/*****************************************************************************/
 /*                                                                           */
 /* function "inorderPredecessor"                                             */
 /*                                                                           */
 /* Node* inorderPredecessor(Node* ptr)                                       */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    Looks for the predecessor the the target node.                         */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Node pointer                                                           */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*    Predecessor is found and returned.                                     */
 /*                                                                           */
 /*****************************************************************************/

Node* BST::inorderPredecessor(Node* ptr) {
	//If there is a thread to the left, then return the next threaded node
    if (!ptr->lthread) {
        return ptr->left;
    }
	//If no thread then inorder predecessor is the rightmost node of the node to left
    ptr = ptr->left;
    while (ptr->rthread) {
        ptr = ptr->right;
    }
    return ptr;
}

/*****************************************************************************/
 /*                                                                           */
 /* function "inorder"                                                        */
 /*                                                                           */
 /* Node* inorder(Node* ptr)                                                  */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    inorder traversal of tree                                              */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Node pointer                                                           */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*    None.                                                                  */
 /*                                                                           */
 /*****************************************************************************/

LinkedList* BST::inorder() 
 {
	LinkedList *list = new LinkedList();
	//if tree is empty
     if (root->left == root)
	 {	cout<<"Tree is empty\n";
        return list;
	 }
    // Reach Leftmost node
    Node *ptr = root->left;
    while (ptr -> lthread)
        ptr = ptr -> left;
    // One by one print successors
    while (ptr != root)
    {
		list->add(ptr->data);
        ptr = inorderSuccessor(ptr);
    }
    list->printLL();
	return list;
}

/*****************************************************************************/
 /*                                                                           */
 /* function "reverseInorder"                                                 */
 /*                                                                           */
 /* Node* reverseInorder(Node* ptr)                                           */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    inorder traversal of tree in the reverse order from max to min         */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Nonw.                                                                  */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*    List                                                                   */
 /*                                                                           */
 /*****************************************************************************/

LinkedList* BST::reverseInorder() {
	
	 LinkedList *list = new LinkedList();
	//if tree is empty
     if (root->left == root)
	 {	cout<<"Tree is empty\n";
        return list;
	 }
    // Reach rightmost node
    Node *ptr = root->left;
    while (ptr -> rthread)
        ptr = ptr -> right;
    // One by one print predecessors
    while (ptr != root)
    {
		list->add(ptr->data);
        ptr = inorderPredecessor(ptr);
    }
    list->printLL();
	return list;
}

/*****************************************************************************/
 /*                                                                           */
 /* function "clear"                                                          */
 /*                                                                           */
 /* void clear(Node* root)                                                    */
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To traverse and delete all nodes in tree.                              */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Node pointer                                                           */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*   None.                                                                   */
 /*                                                                           */
 /*****************************************************************************/

void BST::clear(Node* ptr) {
    // checks if nodes for leaf nodes, if not, recursively traverse and delete
    if (ptr->lthread) {
            clear(ptr->left);
        }
    if (ptr->rthread) {
            clear(ptr->right);
    }
    // clean the current node
    delete ptr;
    ptr = nullptr;
} 

/*****************************************************************************/
 /*                                                                           */
 /* function "rangeTraversal"                                                 */
 /*                                                                           */
 /* LinkedList rangeTraversal(int k1, int k2)                                 */          
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To retrieve all the elements in the specified range                    */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Range k1 to k2                                                         */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*   List.                                                                   */
 /*                                                                           */
 /*****************************************************************************/

 
LinkedList BST::rangeTraversal(int k1, int k2) {
	
	LinkedList list;
	// check if the tree is empty
    if ((root->left == root) && (root->right == root)) {
		return list;
	}
	Node *ptr = root->left;
	while (true) {
        if (k1 == ptr->data) {
			break;
        }

        // if value is larger than the current node data then move to the right
        if (k1 > ptr->data) 
		{
            if (!ptr->rthread) 
			{
                break;
            }
			else 
			{
				ptr = ptr->right;
			}
        } 
        
        // if value is smaller than current node data then move left
        if (k1 < ptr->data) 
		{
            if (!ptr->lthread) 
			{
                break;
            }
			else 
			{
				ptr = ptr->left;
			}

        } 
    } 
	//now as we got the starting point of range, continue to look at the data values and add them till range exceeds
	while(ptr->data <= k2)
	{
		list.add(ptr->data);
		ptr = inorderSuccessor(ptr);
	}
	list.printLL();
	return list;

}
/*****************************************************************************/
 /*                                                                           */
 /* function "kthLargest"                                                     */
 /*                                                                           */
 /* void kthLargest(int k)                                                    */          
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To retrieve the kth largest element in the BST                         */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Value K                                                                */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*   Kth largest element                                                     */
 /*                                                                           */
 /*****************************************************************************/

void BST::kthLargest(int k) {

	//check if the tree is empty
	if ((root->left == root) && (root->right == root)) 
	{
        cout<< "Tree is empty\n";
		return;
	}
	Node* ptr=root->left;
	while(ptr!=root && (ptr->rthread == true || ptr->lthread == true))
	{
			//if the count of right subtree incremented by one is same as k then we return it as the kth largest
			if(ptr->count + 1 == k)
			{
				cout<<k<<"th largest element in tree: "<<ptr->data<<"\n";
				return;
			}
			//if the count of the right subtree is less than k then we move to it's left 
			else if(k > ptr->count+1){
			// Decrease the k value by the number of elements in the right subtree i.e count + 1 for that node
				k = k - (ptr->count+1);
				ptr = ptr->left;
			}
			//Move to the right of the pointer
			else
				ptr = ptr->right;
		}

		//if we reach leaf node then check if the value is reached
		if(ptr!=root && (ptr->rthread == false) && (ptr->lthread == false)){
			if(ptr->count+1==k)
			{
				cout<<"Kth largest element in tree: "<<ptr->data<<"\n";
				return;
			}
		}
		//At this point, all the nodes are traversed 
		cout << "Invalid value of K\n";
}

/*****************************************************************************/
 /*                                                                           */
 /* function "splitBST"                                                       */
 /*                                                                           */
 /* vector<Node*> splitBST(int k)                                             */          
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To split the BST into 2 BSTs T1 and T2 where keys(T1)<=k and keys(T2)>k */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    Value K                                                                */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*   Roots of two BSTs                                                       */
 /*                                                                           */
 /*****************************************************************************/
vector<Node*> BST::splitBST(int k) {
    Node *ptr = root->left;
    vector<Node*> ans(2, new Node(0));
 

    while (ptr!=root && (ptr->lthread == true || ptr->rthread == true)){
    	// if the value of a current node is smaller or equal to the given value,
    	// then add the left subtree to the first tree 
 		if(ptr->data <= k){
            ans[0]->right = new Node(ptr->data);
            ans[0] = ans[0]->right;
			if(ptr->lthread == true)
            	ans[0]->left  = ptr->left;
			if(ptr->rthread == true)
            	ptr = ptr->right;
			else break;
        }
 		//else add right subtree to second tree and move to left child of the node
        else{
            ans[1]->left = new Node(ptr->data);
            ans[1] = ans[1]->left;
			if(ptr->rthread == true)
            	ans[1]->right = ptr->right;
			if(ptr->lthread == true)
            	ptr  = ptr->left;
			else break;
        }
    }
    //Check for the leaf nodes
	if(ptr!=root && ptr->lthread == false && ptr->rthread == false){
		 if(ptr->data <= k){
            ans[0]->right = new Node(ptr->data);
        }
 
        else{
            ans[1]->left = new Node(ptr->data);
        }
	}

    ans[0] = ans[0]->right; // root of the first tree
    ans[1]= ans[1]->left; // root of the second tree

	return ans;
}



/*****************************************************************************/
 /*                                                                           */
 /* function "printTree"                                                      */
 /*                                                                           */
 /* void printTree()                                                          */          
 /*                                                                           */
 /* Purpose:                                                                  */
 /*                                                                           */
 /*    To print the Threaded BST                                              */
 /*                                                                           */
 /* Parameters:                                                               */
 /*                                                                           */
 /*    None                                                                   */
 /*                                                                           */
 /* Returns:                                                                  */
 /*                                                                           */
 /*   graph.vz file                                                           */
 /*                                                                           */
 /*****************************************************************************/
void BST::printTree(){
  
    ofstream fout;
    fout.open ("graph.gv");
    fout << "digraph {\n";
    Node *ptr = root->left;
    write(ptr, fout);
	fout << "}\n";
    fout.close();

    
}

//writes tree data recursely into the file
void BST::write(Node *ptr, ofstream &fout) {

	//if the pointer is at the dummy node, simply return
	if(ptr == root) {
		return;
	}
	//if the pointer is at the leftmost node of BST, make left pointer to null
	if(ptr->left == root){
		fout << "nullleft" << ptr->data << "[shape=point];" << "\n";
		fout << ptr->data << " -> " << "nullleft" << ptr->data << ";" << "\n";
	}
	
	//if the pointer is at the rightmost node of BST, make right pointer to null
	if(ptr->right == root){
		fout << "nullright" << ptr->data << "[shape=point];" << "\n";
		fout << ptr->data << " -> " << "nullright" << ptr->data << ";" << "\n";
	}
	//for all the intermediate child nodes
    if(ptr->left!=root && ptr->lthread == true) {
        fout << ptr->data << " -> " << ptr->left->data << ";\n";
    }
	if(ptr->left!=root && ptr->lthread == false) {
        fout << ptr->data << " -> " << ptr->left->data<< "[color=blue];\n";
    }
    if(ptr->right!=root && ptr->rthread == true) {
        fout << ptr->data << " -> " << ptr->right->data << ";\n";
    }
	if(ptr->right!=root && ptr->rthread == false) {
        fout << ptr->data << " -> " << ptr->right->data << "[color=red];\n";
    }
 
	if(ptr->left!=root && ptr->lthread == true)
    	write(ptr->left, fout);
	if(ptr->right!=root && ptr->rthread == true)
    	write(ptr->right, fout);
}