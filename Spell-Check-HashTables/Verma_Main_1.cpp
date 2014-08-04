/******************************************************************************
 Title :Verma_Main_1.cpp
 Author : Akanksha Verma
 Created on : March 25th, 2013
 Description : 
 Usage : Spell Checker Part 1: Bad Hash Function
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include "Hash_1.h"

using namespace std;

int main(int argc, char*argv[]){
    if (argc != 2) {
        cout<<"Usage: "<<argv[0]<<" Filename"<<endl;
    }
    
    ifstream Dictionaryfile;
    string Word;
    HashTable<string> Dictionary; //Hashtable declaration
    
    Dictionaryfile.open(argv[1]);  //opens file as read from command line
  
    //checks if file is open
    if(Dictionaryfile.good()){
        cout<<"\nFile opened"<<endl;//output if open
        cout<<"\n------------------- Part 1 -------------------------\n";
    }
    else{
        cout<<"Not open: Re-compile program"<<endl;//output if not open
        return 0;
    }
    
    while(!Dictionaryfile.eof()){ //loops till the file is not empty
        Dictionaryfile>>Word;    //reads words from the file
       Dictionary.insert(Word); //Inserts word into the Hash Table
       
    }
    
//prints the total collision, Highest collion for 1 bucket and its bucket number
    cout<<"Total number of Collisions for the BAD hash function = "<<Dictionary.get_TotalCollisions()<<endl;
    Dictionary.Print_Highest();//prints the bucket number and its collision
    cout<<endl;
    return 0;
    
}
