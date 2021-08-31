#include <iostream>
using namespace std;

//Linked List Node Class
class LLNode
 {
	 
     friend class LinkedList;
	 friend class BST;
 private:
	 int data;
	 LLNode *next;
	 public:
  // constructors

  //Default no arg constructor of Node.
  LLNode()
  {
	  data = 0;
	  next = nullptr;
  }


  // Constructor with data in argument.
  LLNode(const int& newdata)
  {
	  data = newdata;
	  next = nullptr;
  }

 };


class LinkedList
{
	friend class BST;
private:
    LLNode *head;
     //Default Constructor
	LinkedList()
	{
		head = nullptr;
	}
	//Parameterized Constructor
	LinkedList(const int &x){
		head = new LLNode(x);
	}
	/*
	~LinkedList()
	{
		head = nullptr;
		delete(head);
	}
	*/
public:
	//inserting a new element into the linked list
	void add(int newdata)
	{
		LLNode *temp = new LLNode(newdata);
		if(head==nullptr)
		{
			head = temp;
			return;
		}
		else
		{
			LLNode *t = head;
			while(t->next!=nullptr)
			{
				t=t->next;
			}
			t->next = temp;
		}

	}
	//to display the elements in the linked list
	void printLL()
	{
		LLNode *temp = head;
		while(temp!=nullptr)
		{
			cout<<temp->data<<"\t";
			temp= temp->next;
		}
	}
};