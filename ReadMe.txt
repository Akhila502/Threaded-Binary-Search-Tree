

/////////////////////////////////////////////////////////////////////////////

Threaded Binary Search Tree:
---------------------------------
For fully threaded binary tree, each node has five fields. Three fields like normal binary tree node, another two fields to store boolean value to denote whether link of that side is actual link or thread.
lthread	left	data	right	rthread
•	Data – stores the integer node value
•	Left and right pointers – to store the next pointers 
•	lthread and rthread – Boolean value to represent whether left and right pointers point to a thread or a child.
-	If lthread is true => left points a child
else if lthread is false => left points to a thread or predecessor
-	If rthread is true => right points to a child
else if rthread is false => right points to a thread or successor


/////////////////////////////////////////////////////////////////////////////

Operations Performed
------------------------------

1) Insert
2) Delete
3) Search
4) Inorder Predecessor
5) Inorder Successor
6) Inorder
7) Reverse Inorder
8) Split 
9) Range Traversal
10) Kth largest
11) Print Tree

/////////////////////////////////////////////////////////////////////////////

Instructions to run the file
-----------------------------
* open the [Assignment_yes_no.sln] file in Visual Studio 10+.
* Run the Assignment_yes_no.cpp ( F5 ).

Instruction to run graphviz
--------------------------------
For svg file:
dot.exe –Tsvg graph.gv -o grapg.svg

For png file:
dot.exe –Tpng graph.gv -o graph.png

////////////////////////////////////////////////////////////////////////////////