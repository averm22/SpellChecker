/******************************************************************************
 Title :Verma_Main_3.cpp
 Author : Akanksha Verma
 Created on : March 25th, 2013
 Description :Spellchecker ,inputs words from a dictionary of limited words into to
              a Hash table, Reads another file of misspelled words and then in :
              part(a) : outputs the list of misspelled words as read
              part(b): outputs possible correction by various string manipulations
                       for each misspelled word
            
 Usage : Part 3 (a,b) 
        for assignment 3 Implements use of Hash Tables for spellcheckers
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include "Hash_3.h"

using namespace std;

/**
 *Function to calculate factorial of input n recursively
 *Used to calculate bound for transposition error combinations
 **/
int factorial(int n){

        if (n == 0)
        {
            return 1;
        }
        else
        {
            return n * factorial(n - 1);
        }

}
/**
 *Function to convert strings to lower case
 **/
string ConvertToLower(string Input){
    for(int i=0;Input[i] != '\0';i++){
        Input[i]=tolower(Input[i]);
    }
    return Input;
}

int main(int argc, char *argv[]){ //comman line variables
    
    if(argc != 4) {//Checks if the user has entered the correct number of arguments
        cout<<"Usage: "<<argv[0]<<" filename"<<endl;
        cout<<"Enter Correct number of arguments to run the program:Program Exits"<<endl;
        return 0; //exits program if arguments are not correct
    }
    else{
        
        ifstream Dictionaryfile; 
        string Word,check,temp,temp2,temp3,temp4,temp5,temp6,temp7;
        HashTable<string> Dictionary; //Hash table object
    
        Dictionaryfile.open(argv[2]); //Opens file taken in as 3rd argument
        
        if(Dictionaryfile.good()) //if file is open
            cout<<"File wordsHW2.txt opened"<<endl;
        else
            cout<<"Not open"<<endl; //if file is not open
       
        
    //Reads words from the file in the 3rd comman line argument
    //Inserts words in the Hash Tables
        while(!Dictionaryfile.eof()){ //loops till file is not at the end
            Dictionaryfile>>Word; //reads into string
            Dictionary.insert(Word); //inputs string to hasg table
        }
        
        cout<<"Words from "<<argv[2]<<" inserted into hash table"<<endl;
        Dictionaryfile.close();
    
  //-------------Part A and B-------------------------------------//
        
    Dictionaryfile.open(argv[1]);  //opens file taken in as the 2nd argument:Document with misspelled words in command line

  //Checks if file is open or not
    if(Dictionaryfile.good())  
        cout<<"File infile.txt opened"<<endl;//outputs if file is open
    else
        cout<<"Not open"<<endl; //Outputs if file did not open

        
    int option = atoi(argv[3]); //converts commandline input string to integer type
        
  //Part A of the question for outputting the incorrect words 
    if(option == 0){  
    
        cout<<"The words spelled incorrectly are:"<<endl;
        while(true){
        Dictionaryfile>>check;
            if(Dictionaryfile.eof())
                break;
        if(!Dictionary.contains(check))
            cout<<"-"<<check<<endl;
        }
        
    }
        
  //Part B of the question for Outputting potential corrections
   else if(option == 1){ 
            while(true){ //checks if there are anymore words to be read
                Dictionaryfile>>check;
                if(Dictionaryfile.eof())
                    break;
                
                check = ConvertToLower(check);
                if(!Dictionary.contains(check)){ //checks if mispelled word is in the dictionary
                    cout<<"\n\n Mispelled Word: \""<<check<<"\""<<endl; //outputs mispelled word
                    cout<<"----- Potential Fix for "<<check<<" ------"<<endl;
                  
                    
    /*--------------------Solving Mispelling By Adding 1 or more characters From the Alphabets ----------------------*/
     //Adds alphabets at front once and twice to same string,adds at the back of string.1 alphabet added at each loop
     //Checks each new string on hash table, outputs if not present on hashtable
                    
            int num = 0;  // intialize number for range of alphabets
            temp = check;//initalizes temp with main string
            while(num <26){ //Adds Alphabets a-z , 1 at every loop to predict potential corrections
                        
            char letter = static_cast<char>( 'a' + num ); // Convert to letter case
            static_cast<string>(&letter);  //formats type char to string
            temp+=letter; //adds an alphabet at the end
            temp2=letter+check;  //adds an alphabet in the front
            temp4=temp+letter;  //adds an alphabet at the back
                
            //checks if the transformed string is correct
            //outputs as potential correction
            if(Dictionary.contains(temp))
                cout<<"-"<<temp<<endl;
                        
            if(Dictionary.contains(temp2))
                cout<<"-"<<temp2<<endl;
                        
            if(Dictionary.contains(temp4))
                cout<<"-"<<temp4<<endl;
                        
            num++; //increments num for the loop
            temp = check; //re-intializes temp to original string for other manipulations
            temp2= check;
        }  
           
                   
                    
     /*--------------------Solving Mispelling By switch characters: Transposition Error corrections ----------------------*/               
    //Transposition Error: Swaps letters in words , till n! where n is the length of string.
    // Uses swap function to switch the letter, checks each word in the hash table
                   
            int i=0; // initilize counter variable
            int length = check.length(); // initializes with length of string
            int bound = factorial(length); //predicts the max number of possible combination for trasnposition error
            temp5 = check; //re-intializes temp to original string for other manipulations

            while(i<bound){  //Tranposition error: Swaps position of alphabets in string
                int j=i+1; //increments next char counter
                
                if(j<length){ //loops till next char is within the string length
                    
                    swap(temp5[i], temp5[j]); //Transposition error swapping
                    i++;
                    
                    if(Dictionary.contains(temp5))  //checks if the new string is in the hash table
                        cout<<"-"<<temp5<<endl;
                }
                else
                    break;
                }
                    
                    
              
                    
  /*--------------------Solving Mispelling By Deleting aphabets after 3 characters in string ----------*/               
    //Deletes characters using string.resize()
                    
                        int k=2;    //initializes it to keep the string at minimum 3 letters for base case
                        temp6=check;    //orginal string initialized to temp
                    
                        while(k<length){    //runs till k increments to the length of string
                            temp6.resize(k);    //resize shifts string size depending on k
                            
                            if(Dictionary.contains(temp6))      //checks if new resized string is in the hash table
                                cout<<"-"<<temp6<<endl;     //outputs the string as potential correction if true
                
                            k++;    //increments count for loop
                            temp6=check;    //re-initializes temp to original string
                   
                        }
               
                 }

           
            }
       
        }
    
         Dictionaryfile.close();
    }
    
   
    return 0;
    
}
