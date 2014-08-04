#ifndef __Assignment3__File__
#define __Assignment3__File__
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include "AVLTreeClass.h"

using namespace std;

const int BUCKET_SIZE = 50287;
int nextPrime( int n );
int hashes( const string & key );
int Badhashfunction(string word);

AVLTreeClass<unsigned int, int> CollisionKeeper; //structure to keep track of individual collsions for each bucket
int total=0; //Variable to keep track of Total Collision

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashes( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable( int size = 50287 ) : array( nextPrime( size ) )  //initializes the new object
    { makeEmpty( ); }
    
    bool contains( const HashedObj & x ) const //bool function to check if object is on Hashtable
    {   
        return isActive( findPos( x ) );
    }
    
    void makeEmpty( ) //Deletes all data on the tables
    {
        currentSize = 0;
        for( unsigned int i = 0; i < array.size( ); i++ )
            array[ i ].info = EMPTY;
    }
    
	//returns the flag for object
    bool insert( const HashedObj & x )
    {
        
        
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;
        
        array[ currentPos ] = HashEntry( x, ACTIVE );
        
        // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 ){
            rehash( );
            
        }
        

        return true;
    }
    
	//Deletes an object
    bool remove( const HashedObj & x)
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;
        
        array[ currentPos ].info = DELETED;
        return true;
    }
    
    enum EntryType { ACTIVE, EMPTY, DELETED };
   
    
      //Return total number of collisions
    int get_TotalCollisions(){
        return total;
    }

    //prints the Highest number of Collision and its bucket
    void Print_Highest_Collisions(){
        
        CollisionKeeper.printTree();
    }
    
   //Searches for the highest collision number for a bucket 
    void Print_Highest(){
        
        CollisionKeeper.finds();
    }
   
    
    
private:
    
    struct HashEntry
    {
        HashedObj element;
        EntryType info;
        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
        : element( e ), info( i ){ }
    };


    
    vector<HashEntry> array;
    unsigned int currentSize;
    
    
    bool isActive( int currentPos ) const
    { return array[ currentPos ].info == ACTIVE; }
    
    int findPos( const HashedObj & x ) const
    {
        
        double offset = 1;
        unsigned currentPos = myhash( x );
        int collision=0;
        // Assuming table is half-empty, and table length is prime,
        // this loop terminates
       
        if(!CollisionKeeper.contains(currentPos))       // Inserts for position with 0 collision
            CollisionKeeper.insert(currentPos, collision);
        
        while( array[ currentPos ].info != EMPTY &&
              array[ currentPos ].element != x )
        {
            
            if(!CollisionKeeper.contains(currentPos)) //avltree checks if a bucket is not on the list
                CollisionKeeper.insert(currentPos, collision); //inserts it if not
            else
                CollisionKeeper.UpdateValue(currentPos, collision); //Updates collision value if present.
            
           
            currentPos += pow(offset, 2.00); // Compute ith probe
            offset += 1;
            
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
            
        collision++;
    }

        total+=collision;
       // cout<<currentPos<<"  "<<collision<<endl;
        return currentPos;
    }


    
    void rehash( )
    {
        vector<HashEntry> oldArray = array;
        
        // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( unsigned int j = 0; j < array.size( ); j++ )
            array[ j ].info = EMPTY;
        
        // Copy table over
        currentSize = 0;
        for( unsigned int i = 0; i < oldArray.size( ); i++ )
            if( oldArray[ i ].info == ACTIVE )
                insert( oldArray[ i ].element ); 
    }
    
    
    int myhash( const HashedObj & x ) const
    {
        
        int hashVal = hashes(x); 
        hashVal %= array.size( );
        if( hashVal < 0 )
            hashVal += array.size( );
        
        return hashVal;
}
};

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;
    
    if( n == 1 || n % 2 == 0 )
        return false;
    
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;
    
    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime( int n )
{
    if( n <= 0 )
        n = 3;
    
    if( n % 2 == 0 )
        n++;
    
    for( ; !isPrime( n ); n += 2 )
        ;
    
    return n;
}

/**
 * A hash routine for string objects.
 */
int hashes( const string & key )
{
    int hashVal = 0;
    
    for( unsigned int i = 0; i < key.length( ); i++ )
        hashVal = 25 * hashVal + key[ i ];
    
    return hashVal;
}



#endif
