Assignment 2 :
Akanksha Verma (averm@hunter.cuny.edu)

--Implemented programs
	To my knowledege, All parts of the assignment were completed and functional
	 as per the given main function 
	Structure of Main:
		- Main provides you with a 2 option Menu to run Part 1 and Part 2 of the Assignments.On Prompt:
			- Type 1 to run Part 1: AVL Tree of integers
			- Type 2 to run Part 2: AVL Tree of Words from the txt files
	 Part1:(Test Function
		- First ask user to enter the number of elements they want to enter in the tree
		- On every insert prompt: enter 1 comparable and the associated value  numbers separated by a space **
		- Output of the input with its boolean flag is generated on each input
		- After all inputs are done: 
				-User is prompted for a number that is to be deleted from the tree
				-Enter the number to delete from tree, the new tree is displayed with the null node
		-Update Value Function:
				-User is shown a table with the comparable and its associated value they entered.
				-Enter the comparable value for which they want to update the associated value
				-Enter the new update value
				-New table of the comparable and its updated associated value is displayed
		-The computed Internal Path length is displayed.
	Part 2:
		-After insertion and manipulation,User is asked if they would like to find a word (*suggested word search = "is"*)
	       - User is asked if they wish to remove a word from the tree (suggested word to remove "the"/"yet")
	       - Internal Path length after deletion may not be correctly implemented
		
		
	
	source file :Verma_Main.cpp and uses AVLTreeClass.h header file for the Tree implementation
	
	error messages incase file does not open, no exceptional error handling necessarily implemented.

--Not any known bugs

--To compile just type

         make all

--To run the first program type
     
	 ./prog1

--To remove object files type

         make clean
