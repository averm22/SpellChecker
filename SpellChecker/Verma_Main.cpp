/******************************************************************************
 Title : Verma_Main.cpp
 Author : Akanksha Verma
 Created on : March,1st 2013
 Description :calls the main function which calls the avltree class header file
              implements a test function for two types of AVL trees
 Usage :  as per README.txt
 Build with : Makefile command "make all" use use excutable./prog1
 Modifications :
 ******************************************************************************/

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include "AVLTreeClass.h"

using namespace std;

//Function Declarations
void TestingAVLTree();
//Function test the implementation of an Integer type AVL tree
//test insert,remove,output in level order and Internal path length of tree

void TestingAVLTreesofWords();
//Function implements a tree with string as key inputs and lists of linenumbers as stored
//reads from file,parses strings,inserts and allows user to remove as per search


string DeletePunctuations(string & input);
//Function called by TestingAVLTreesofWords() to delete all the punctuations in the string
//returns string



int main(){

    int choice; //variable for user's choice
    cout<<"Two parts of the program are:\n"<<" Part 1:Avl Tree of Integers\n Part 2: AVL Tree of Words\nWhich one would you like to run (1/2):";
    cin>>choice;	//user input 
    if(choice == 1)
         TestingAVLTree(); //call TestingAVLTree if choice is 1
    else if(choice == 2)
        TestingAVLTreesofWords(); //call Function for part 2 of the program.

    return 0;//end of main
}



/**
 * asks user to input the number of item they want to input in the tree
 * user inputs the comparable along with the value separated by a space
 * tree printed in level order on every insertion
 * User asked to remove a word of their choice from the tree
 * List of comparables and their associated values outputted
 * user choose comparable to be updated and new updated value
 * updated list of comparables and their values outputted
 * Internal path length outputted
 */

void TestingAVLTree(){
    
    
    AVLTreeClass<int, int> mytree;  //AVL tree of time int
    
    int input,value,x,y,Input2,UpdateValue;
    
    cout<<"  \n Part 1 : Test Function for AVL Tree of Integers \n\n ";
    
    cout<<"How many items would you like to enter in the AVL Tree? :";
    cin>>x;
	cout<<"Enter Number and its associated value separated by a space "<<endl;
    int i=0;
    while (i<x) {
        cout<<" Insert item in tree >> ";
        cin>> input >> value;
        mytree.insert(input,value);  //every input inserted into tree
        mytree.PrintInlevelOrder();   //tree printed in order on ever insertion
        i++;
    }
    //Allows user to remove an item off the tree
    cout<<"Enter Comparable item you would like to remove: "; //user prompted for a comparable they want to delete
    cin>> y;
    
    mytree.remove(y); //comparable removed from tree
    
    mytree.PrintInlevelOrder(); //tree printed in level order again
    
    //Allow user to update an associated value for a comparable they select
    cout<<"Update Value:\n ";
    cout<<"Current Values for Comparables: \n"<<"Comparable Value"<<endl;
    mytree.printTree(); //prints the list of comparables and their values in sorted order for reference
    
    cout<<"Enter the Comparable for which you would like to update the value: ";
    cin>>Input2;
    
    cout<<"What would you like to update the value with: ";
    cin>>UpdateValue;
    
    mytree.UpdateValue(Input2, UpdateValue);  //function call to update the value of the comparable selected
    
    cout<<"Updated Values are: \n"<<"Comparable Value"<<endl;
    mytree.printTree();//new updated list of key comparables and their associated value printed
    
    mytree.ipl(1); //prints the Internal Path length of the user inputted tree.
}




/*
*reads file and parses each read line,into words and calls function to insert it into the tree
*linenumbers: list declaration to store the line numbers where the words occur
*Calls functions to compute the IPL, the avg single rotations and double rotations
*Allows user to search word and display the line numbers where it appears 
*Allows user to search word ,deletes it and outputs number of operations it takes to delete the word
*Deletes the words from words.txt , displays the new IPL after lazy deletion.
*/

void TestingAVLTreesofWords(){	

    fstream file;    
    int LineNumb=0,N=0;
    string line,word,SearchWord;
    AVLTreeClass< string,list<int> > words;
    list<int> linenumbers;

    file.open("DocumentHW2.txt");

    if(file.is_open())
        cout<<"File DocumentHW2.txt Open"<<endl;
    else
        cout<<"Not open"<<endl;

    while(!file.eof()){
        getline(file,line);
        LineNumb++;
		
        if(line.length() == 0)
            continue;
		
        int start=-1,length= line.length();
        bool isaWord =false;
		DeletePunctuations(line);
        for(int i=0;i<length;i++){
			
            islower(line[i]); //changes to lower case
			
            if(!(isalnum(line[i])|| isalpha(line[i]))){  //checks if its a letter or not

                if(isaWord){ 
                    string word = line.substr(start,i-start); //uses the substring function to parse the line
					N++;	//increments for each word inputted in the tree
                    words.insertword(word, LineNumb,linenumbers); // inserts the word in tree and the line number in the list
                }
                isaWord=false;
            }
            else{
                if(!isaWord) 
                    start = i;
            		isaWord=true; 
            	}
        	}
   		 }
	
	cout<<"Total Number of Words ="<<N<<endl;  //Outputs the calculated total number of words , variable N
    words.manipulations(); //function call which out puts parts A,B,C of the program
	
    words.ipl(2); //Calls function to calculate internal path length and outputs.
    file.close(); //closes the file.

//Allow User to Search a word and display the line numbers it appears in
    cout<<"D: Search word and Print the line numbers \n Enter Word to search for in the AVL tree: ";
    cin>>SearchWord;

    if(!words.SearchWord(SearchWord))
        cout<<"Word Not Found"<<endl;
    //

//Allow user to search a word and delete it from the tree
    cout<<"E: Allows Deletion of Specific Word\n Enter the Word you would like to remove from the tree: ";
    cin>>SearchWord;
    if(words.remove(SearchWord)==0) //checks if word is found in tree
        cout<<"Word not found in the tree!: No delete took place\n";
    else
        cout<<"The Number Of operation it took to delete\""<<SearchWord<<"\"="<< words.remove(SearchWord)<<endl;



//Deletion of words in the tree from words in the file WordsHw.txt
    file.open("wordsHW2.txt");
    LineNumb =0;
    int NumOfWordsDeleted=0;
    if(file.is_open())
        cout<<"\nFile wordsHW2.txt Open "<<endl;
    else
        cout<<"Not open"<<endl;

    while(!file.eof()){
        file>>word;
        LineNumb++;
        if(LineNumb%2 == 0){ //checks for everyother line
            words.remove(word); //removes every other word of the wordhw.txt from documents file
            NumOfWordsDeleted++;
        }
    }
    
    cout<<"F:Deleted words present in wordsHW2.txt from DocumentsHW2.txt\n"; //outputs the end 


    file.close();
	 words.ipl(1);

}

string DeletePunctuations(string & input){ //Deletes punctuations

	int length=input.length();
    for(int i=0;i<length;i++){
        if(ispunct(input[i]))
            input[i]=' ';
    }
    return input;
}

