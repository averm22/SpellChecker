
/******************************************************************************
 Title :
 Author :Akanksha Verma
 Created on : April 2, 2010
 Description : Draws stars of any size in a window, by dragging the mouse to
 define the bounding rectangle of the star
 Purpose : Reinforces drawing with the backing-pixmap method, in which the
 application maintains a separate, hidden pixmap that gets drawn
 to the drawable only in the expose-event handler. Introduces the
 rubberbanding technique.
 Usage : drawing_stars
 Press the left mouse button and drag to draw a 5-pointed star
 Build with : gcc -o drawing_demo_03 drawing_stars.c \
 `pkg-config --cflags --libs gtk+-2.0`
 Modifications :
 ******************************************************************************/
#ifndef __Assignment3__File__
#define __Assignment3__File__
#include <vector>
#include <iostream>
#include <string>
#include<cmath>
#include "AVLTreeClass.h"

using namespace std;

const int BUCKET_SIZE = 50287;
int nextPrime( int n );
int hashes( const string & key );


AVLTreeClass< unsigned int, int> CollisionKeeper; //structure to keep track of individual collsions for each bucket
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
        for( unsigned int i = 0; i < array.size( ); i++ )
            array[ i ].info = EMPTY;
    }
    
    bool insert( const HashedObj & x )
    {
        
        
        // Insert x as active
        unsigned int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;
        
        array[ currentPos ] = HashEntry( x, ACTIVE );
        
        // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 ){
            rehash( );
            
        }
        

        return true;
    }
    
    bool remove( const HashedObj & x ) //deletes an element
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;
        
        array[ currentPos ].info = DELETED;
        return true;
    }
    
    enum EntryType { ACTIVE, EMPTY, DELETED }; //records status of an object 
   
    
    
    int get_TotalCollisions(){ //gets total number of collisions
        return total;
    }
    
    void Print_Highest_Collisions(){ //prints the bucket number and the individual collisions
        
        CollisionKeeper.printTree();
    }
    
    void Print_Highest(){ //finds the highest collision for a bucket
        
        CollisionKeeper.finds();
    }
    
    
    void SetprobeType(int value){  //sets the vale of private data member probe as read off the command line
        probe = value;
    }
    
private:
    
    struct HashEntry     //object for each element entered
    {
        HashedObj element;
        EntryType info;
        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
        : element( e ), info( i ){ }
    };


//private data members
    vector<HashEntry> array;            //vector to store the objects
    unsigned int currentSize;   //track size of array / how many elements are present
    int probe;      //records if its a quadratic or double hashing probing
    
    bool isActive( int currentPos ) const
    { return array[ currentPos ].info == ACTIVE; }
    
    
    int findPos( const HashedObj & x ) const //finds the position to insert/locate element.
    {
        
        int offset = 1;
        unsigned int currentPos = myhash( x );
        int collision=0;
        // Assuming table is half-empty, and table length is prime,
        // this loop terminates
        while( array[ currentPos ].info != EMPTY &&
              array[ currentPos ].element != x )
        {
            
           
            if(!CollisionKeeper.contains(currentPos)) //avltree checks if a bucket is not on the list
                CollisionKeeper.insert(currentPos, collision); //inserts it if not
            else{
                
                CollisionKeeper.UpdateValue(currentPos, collision); //Updates collision value if present.
            }
            
            if(probe == 0){ //Quadratic probing
                offset += 1;
                currentPos += static_cast<int>(pow(offset, 2.00)); // Compute ith probe
            }
            else if(probe == 1){ //Double hashing
            offset = myhash2(x);
            currentPos += (offset*myhash2(x)%(BUCKET_SIZE-1)+1); // Compute ith probe
            }
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
            
           collision++;
           
            
        }
    
        total+=collision;
        
        return currentPos;
    }
    
    /**
     *Allows to add space incase of no space on table
     *copies and re-inserts the previous elements onto
     *the newly resized hash table
     **/
    
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
    
    
    /**
     *Hash Function mods the calculate hash value for the key
     * to accomodate in the Table of size T
     **/
    
    int myhash( const HashedObj & x ) const //Function 1 for Double Hashing
    {
        int hashVal = hashes(x);
        hashVal %= array.size( );
        if( hashVal < 0 )
            hashVal += array.size( );
        
        return hashVal;
    }
    
    /**
     * Used For Double Hashing
     * Second Hash Function
     */
    int myhash2(const HashedObj & x) const{ //second hash function for Double hashing
        
        int hashVal = hashes(x);
        hashVal = 157-(hashVal%157);
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
        hashVal = 35 * hashVal + key[ i ];
    
    return hashVal;
}




#endif