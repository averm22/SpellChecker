/******************************************************************************
 Title :Verma_Main_2.cpp
 Author : Akanksha Verma
 Created on : March 25th, 2013
 Description :
 Usage : Part 2 (a and b) for Assignment 3

 ******************************************************************************/

#include <iostream>
#include <fstream>
#include<string>
#include <stdlib.h> 
#include "Hash_2.h"

using namespace std;

int main(int argc , char *argv[]){
    
    if(argc != 3) {//argc should be 3
        cout<<"Usage: "<<argv[0]<<" filename"<<endl;
        cout<<"Enter Correct number of arguments to run the program:Program Exits"<<endl;
        return 0; //exits if the commanline arguments were not what was needed
    }
    ifstream Dictionaryfile;
    string Word;
    HashTable<string> Dictionary; //Hashtable object
    
    Dictionaryfile.open(argv[1]); //opens file as specified in the commanline
  
//checks if the file is open
    if(Dictionaryfile.good())
        cout<<"\nFile opened"<<endl; //Indicates file is open
    else{
        cout<<"Not open: Re-compile program"<<endl; //indicates file is not open
        return 0; //exits if file is not open
    }
    int ProbeType = atoi(argv[2]);//converts commandline arugument from string to int
    
    while(!Dictionaryfile.eof()){ //loops till file is not empty
        Dictionaryfile>>Word; //reads words
        Dictionary.SetprobeType(ProbeType); //sets the probe type's argument
        Dictionary.insert(Word); //Inserts word
    }
     
	cout<<"Hash Function Used:  hashVal = (35 * hashVal + key[ i ] )%Bucket_Size"<<endl;
    if(ProbeType == 0){  //For part a : Quadratic Probing
        cout<<"\n---------------------Part 2 : a --------------------------------------\n";
    //prints Total number of collision , bucket with highest collision and its collision
        cout<<"Total number of Collisions using Quadratic Probing = "<<Dictionary.get_TotalCollisions()<<endl; 
        Dictionary.Print_Highest(); 
    }
    
    else if(ProbeType == 1){    //For part b: Double Hashing
        cout<<"\n---------------------Part 2 : b --------------------------------------\n";
    //prints Total number of collision , bucket with highest collision and its collision
        cout<<"Total number of Collisions using Double Hash = "<<Dictionary.get_TotalCollisions()<<endl;
        Dictionary.Print_Highest();
    }
    
    cout<<endl;
    
    return 0;
}
