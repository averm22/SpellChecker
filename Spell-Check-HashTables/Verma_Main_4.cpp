/******************************************************************************
 Title :Verma_Main_4.cpp
 Author : Akanksha Verma
 Created on : March 25th, 2013
 Usage : Spell Checker Part 4
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include "Hash_4.h"
using namespace std;

string ConvertToLower(string Input){
    for(int i=0;Input[i] != '\0';i++){
        Input[i]=tolower(Input[i]);
    }
    return Input;
}

int main(int argc, const char * argv[])
{

    if( argc != 3){ //checks if the number of arguments are atleast 3
        cout<<"Usage: "<<argv[0]<<" filename"<<endl;
        cout<<"Enter Corrent number of Arguments: Program Exits"<<endl;
        return 0; //outputs error me
    }

    ifstream DictionaryFile;
    DictionaryFile.open(argv[2]); //opens file in the second argument on command line
    
    HashTable<string>Dictionary; //declaring hashobject
    string Word,temp6;
    
    if(DictionaryFile.good()) //checks if file is open
        cout<<"File wordsHW2.txt opened"<<endl; 
    else
        cout<<"Not open"<<endl;
    
    
    
    while(!DictionaryFile.eof()){ //Checks if file still has strings to be read
        DictionaryFile>>Word;
        Word=ConvertToLower(Word); //converts word read to lower
        int length = Word.length(); //initializes to the length of the string
        if (!Dictionary.contains(Word)) {  //checks if the hash table contains the word
            Dictionary.insert(Word,true); //calls function insert word with true flag if true
        }
        else{
            Dictionary.ChangeFlag(Word, true); //calls function change the flag to true if the word already exists
        }
        
        int k=length-1; 
        temp6=Word;

        while(k>2){
            temp6 = Word.substr(0,k); //Keeps making substrings of the real word for the prefixes
            if(!Dictionary.contains(temp6)){ //checks if prefix is present in the hash table
                Dictionary.insertRealWord(temp6, false,Word); //if prefix is not present, it is inserted in the table 
															  //with a false flag
            }
            else
                Dictionary.InsertAnotherRealWord(temp6, Word); //if prefix is present, the word itself is inserted as 
																//a real word for the prefix
            
            k--;

        }
    }
    
    
    DictionaryFile.close(); //closes file

    DictionaryFile.open(argv[1]); //opens file 

//checks if the file is open or not
    if(DictionaryFile.good())
        cout<<"File infile.txt opened\n"<<endl; //output if open
    else
        cout<<"Not open"<<endl; //output if not open
    
    int i =0;
    while(true){
        DictionaryFile>>Word;
        if(DictionaryFile.eof())   //checks if file has ended
            break;
        Word = ConvertToLower(Word); //converts word to lower case
        if(!Dictionary.GetFlag(Word) && Dictionary.contains(Word)){ //Checks if the word is a prefix and is present in 
																	//the hash table
        cout<<i+1<<".Misspelled Word: \""<<Word<<"\""<<endl;
        cout<<"Possible Completions"<<endl;
        cout<<"---------------------"<<endl;
        Dictionary.PrintPotentialWords(Word); //outputs the list of possible correction from corresponding list
        cout<<endl<<endl;
            i++; //increment counter
        }
     
     
    }
    
	DictionaryFile.close();
    return 0; //end of program
    }

