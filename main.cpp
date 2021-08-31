/* Standard includes */

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>


/* Project includes */

#include "BST.h"
//#include "LinkedList.h"

using namespace std;

//Test Insert

void testInsert() {
    BST bst;
    assert(bst.insert(25));   // Test insertion
    assert(bst.insert(14));  
    assert(bst.insert(6));   
    assert(bst.insert(-2));  // Test negative number insertion
	assert(bst.insert(-8));
	assert(bst.insert(12));
 
    assert(!bst.insert(14)); //Test duplicates insertion
    assert(!bst.insert(-2));

    cout << "Test Insert Passed\n";
} 

// Test Remove

void testRemove() {
    BST bst;

	//Insertion
	assert(bst.insert(25));   
    assert(bst.insert(14));  
    assert(bst.insert(6));   
    assert(bst.insert(-2));  
	assert(bst.insert(-8));
	assert(bst.insert(12));

	//Deletion

	assert(bst.remove(14));         // Test remove
	assert(!bst.remove(14));        // Try to remove same value again
    assert(bst.remove(-2));        // Test removing negative value
	assert(!bst.remove(10));         // Test removing non existing value
	assert(bst.insert(45));         //Insert new value 
	assert(bst.remove(45));         //Remove the newly inserted value
    

    cout << "Test Remove Passed\n";
}

//Test Contains

void testContains() {
    BST bst;

	//Insertion
	assert(bst.insert(25));   
    assert(bst.insert(14));  
    assert(bst.insert(6));   
    assert(bst.insert(-2));  
	assert(bst.insert(-8));
	assert(bst.insert(12));

	assert(bst.contains(25));   //Test contains
	assert(bst.contains(-2));   //Test contains on negative number
	assert(bst.insert(45));         //Insert new value 
	assert(bst.contains(45));   //Test contains on newly inserted value
	assert(!bst.contains(16));   //Test contains on non existing value

	assert(bst.remove(14));         // Remove a value
	assert(!bst.contains(14));   //Test contains on removed value

    
    cout << "Test Contains Passed";
}
int main()
{
	int option, data, k1,k2;
	bool b;
	BST bst;
	cout<<"\n**************THREADED BINARY SEARCH TREE********************\n\n";

	while(true){

	cout<<"\n-----------------------------------------------------------------\n"
		<<"Operations:\n"
		<<"-----------------------------------------------------------------\n"
		<<"1. Insert\n"
		<<"2. Search\n"
		<<"3. Delete\n"
		<<"4. Reverse Inorder Traversal\n"
		<<"5. Inorder Traversal\n"
		<<"6. Retrieve the elements in a range\n"
		<<"7. Retrieve Kth largest element\n"
		<<"8. Print Tree\n"
		<<"9. Run Test cases\n"
		<<"10. Exit\n"
		<<"-----------------------------------------------------------------\n";

	cout<<"Choose the operation to be performed:";
	cin >>option;

	switch(option)
	{
	case 1:
		cout<<"\n*********INSERT************\n"
			<<"Enter the element to be inserted:";
		cin>>data;
		b = bst.insert(data);
		
		if(b==true)
			cout<<"\nInsertion of element succesfull\n";
		else
			cout<<"\nElement already present in the tree, cant be reinserted!!!\n";
		break;
	case 2:
		cout<<"\n*********SEARCH************\n"
			<<"Enter the element to be searched:";
		cin>>data;
		b = bst.contains(data);
		if(b==true)
			cout<<"\nElement is found in the tree\n";
		else
			cout<<"\nElement is not present in the tree\n";
		break;
	case 3:
		cout<<"\n*********DELETE************\n"
			<<"Enter the element to be deleted:";
		cin>>data;
		b = bst.remove(data);
		if(b==true)
		cout<<"\nDeletion of element succesfull\n";
		else
			cout<<"\nElement is not present in the tree, cant be deleted!!!\n";
		break;
    
	case 4:
		cout<<"\n***********REVERSE INORDER TRAVERSAL*****************\n";
		bst.reverseInorder();
		break;
	case 5:
		cout<<"\n***********INORDER TRAVERSAL*****************\n";
		bst.inorder();
		break;
	case 6:
		cout<<"\n***********RANGE TRAVERSAL*****************\n";
		cout<<"\nEnter the range k1 and k2: ";
		cin >> k1;
		cin>>k2;
		bst.rangeTraversal(k1,k2);
		break;
	case 7: 
		cout<<"\nEnter the k value: ";
		cin >> data;
		bst.kthLargest(data);
		break;
	case 8:
		cout<<"\n***********PRINT TREE*****************\n";
		cout<<"File grapg.gv generated\n"
			<<"Type the following command in command prompt to generate png :\n"
			<<"dot.exe –Tpng graph.gv -o graph.png\n";
		bst.printTree();
		break;
	case 9:
		cout<<"\n***********TEST CASES*****************\n";
		testInsert();
		testRemove();
		testContains();
		break;
	case 10:
		goto end;
	}
	}
end:
	cout<<"***************************DONE***************************\n";
	return 0;
}

