Assignment 3 :
Akanksha Verma (averm@hunter.cuny.edu)

--Implemented programs
	To my knowledge, All parts of the assignment were completed and functional
	 as per the given specifications
	 
	Descriptions of all programs:
	Part 1:
		Creates a hash table using a bad hash function 
		Outputs the Total number of Collision, the Bucket number with Highest collision and its collision
		Source file: Verma_Main_1.cpp , uses Hash_1.h for implementation of Hash Table and AVLTreeClass.h header for keeping track of collisions and bucket numbers
	 Part 2:
		Creates a hash table using my own Good hash function 
		Outputs the Total number of Collision, the Bucket number with Highest collision and its collision	
		part a.) Uses Quadratic probing to create Hash table
		part b.) Uses Double Hashing to create table
		
		 Source file: Verma_Main_2.cpp , uses Hash_2.h for implementation of Hash Table and AVLTreeClass.h header for keeping track of collisions and bucket numbers
	Part 3:
		Creates a Hash Table with words from the text file 
		Part (a) : Reads words from doc file, and then checks for it in the hash table to determine if its misspelled .Outputs list of Misspelled word in doc file
		Part (b) : Manipulates each misspelled word by adding alphabet(s),switching character positions,deleting letter and then outputs possible corrections for each.

		Source file: Verma_Main_3.cpp , uses Hash_3.h for implementation of Hash Table and AVLTreeClass.h header for keeping track of collisions and bucket numbers
		
	Part 4:
		Creates a Hash Table with words from the text file also inputs prefixes of the word with a list of actual word against each prefix, a flag to indicate if prefix is a 		real word or not.
		Reads Misspelled words from document file, and prints list of possible correction if Misspelled word is a prefix (has a false flag)

		Source file: Verma_Main_1.cpp , uses Hash_1.h for implementation of Hash Table and AVLTreeClass.h header for keeping track of collisions and bucket numbers
	
		source file :Verma_Main_4.cpp uses Hash_3.h for implementation of Hash Table and AVLTreeClass.h header for keeping track of collisions and bucket numbers
		
	
	 Error message generated if command line does not have the correct number of argument and program exits 
        Error messages incase file does not open, no exceptional error handling necessarily implemented.

--Not any known bugs

--To compile just type

         make all

--To run the First program type
     
	 ./Hash1Test (name of text file )

--To run the Second Program type

	./Hash2Test wordsHW2.txt 0 [For Quadratic Probing]
	./Hash2Test wordsHW2.txt 1 [For Double Hashing] 

--To run Third Program type
	
	./spellcheck infile.txt wordsHW2.txt 0 [For part a]
	./spellcheck infile.txt wordsHW2.txt 1 [For Part b]

--To run the Fourth Program Type
	./spellcheck2 infile.txt wordsHW2.txt 


--To remove object files type

         make clean
