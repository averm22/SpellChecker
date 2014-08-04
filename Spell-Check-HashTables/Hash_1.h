#ifndef __Assignment3__File__
#define __Assignment3__File__
#include <vector>
#include <iostream>
#include <string>
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
    explicit HashTable( int size = 50287 ) : array( nextPrime( size ) )
    { makeEmpty( ); }
    
    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }
    
    void makeEmpty( )
    {
        currentSize = 0;
        for(unsigned int i = 0; i < array.size( ); i++ )
            array[ i ].info = EMPTY;
    }
    
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
    
    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;
        
        array[ currentPos ].info = DELETED;
        return true;
    }
    
    enum EntryType { ACTIVE, EMPTY, DELETED };
   
    
    //returns total collision
    int get_TotalCollisions(){
        return total;
    }
    
	//prints the highest collision 
    void Print_Highest_Collisions(){
        
        CollisionKeeper.printTree();
    }

    //Finds the higest collision
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
        
        int offset = 1;
        unsigned int currentPos = myhash( x );
        int collision=0;
        // Assuming table is half-empty, and table length is prime,
        // this loop terminates
       
        while( array[ currentPos ].info != EMPTY &&
              array[ currentPos ].element != x )
        {
            if(!CollisionKeeper.contains(currentPos))
                CollisionKeeper.insert(currentPos, collision);
            else{
                
                CollisionKeeper.UpdateValue(currentPos, collision);
            }
           
            
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
            
           collision++;
        }
        
        
        total+=collision;//increments total collision
    
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
    
    //myhash function hashes the input using bad hash function
	//returns hashvalue for insertion
    int myhash( const HashedObj & x ) const
    {
       int hashVal = Badhashfunction(x);
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

/* returns index based on string's character code values */
int Badhashfunction(string word)
{
    int sum = 0;
    int len = word.length();
    for (int k=0; k<len; k++)
        sum += (int)word[k];
    
    return sum % BUCKET_SIZE; /* Table Size - number of Buckets */
}


#endif
