/******************************************************************************
 Title : AVLTreeClass.h
 Author : Akanksha Verma
 Created on : March,1st 2013
 Description : Implements function for an AVL Tree, functions to calculate its IPL Length,recursive funtion counts
 Usage : for Verma_Main.cpp as per README.txt
 Build with : Makefile command "make all" use use excutable./prog1
 Modifications :
 ******************************************************************************/

#ifndef Assignment2_AVLTreeClass_h
#define Assignment2_AVLTreeClass_h

#include<iostream>
#include <string>
#include <list>
#include<math.h>


using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// *****************************PUBLIC OPERATIONS*****************************************************
// void insert( x )                   --> Insert x
// void insertword(x,num,linenumber>  --> Inserts word x line number num in list linenumber
// int remove( x )                    --> Remove x and returns the num of operations
// void UpdateValue(x,k)              --> Updates the associated value of k
// boolean isEmpty( )                 --> Return true if empty; else false
// void makeEmpty( )                  --> Remove all items
// void printTree( )                  --> Print tree in sorted order
// ********************************ERRORS**************************************************************


int highest=0;
int bucket;

template<typename Comparable, typename Value>
class AVLTreeClass {
public:
    AVLTreeClass( ) : root( NULL ) //default constructor
    { }
    
    AVLTreeClass( const AVLTreeClass & rhs ) : root( NULL ){ //constructor with Parameter
        *this = rhs;
    }
    
    ~AVLTreeClass( ){  //Destructor
        makeEmpty( );
    }
    
    /**
     * Insert X into tree
     */
    void insert( const Comparable & x ,const Value & k)
    {
        insert( x,k, root );
    }
    
    /**
     * Removes x from tree and returns the number of operation
     */
    int remove( const Comparable & x ){
        return remove(x,root);
    }
    
    /**
     *Calls function to update the associated value in a node
     */
    void UpdateValue( Comparable & x,Value & y){
        
        UpdatesValue(x, root, y);
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( ){
        makeEmpty( root );
    }
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const{
		return root == NULL;
    }
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
    
    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const{
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }
    
    /**
     *Prints result of Finding the Comparable with the Highest Value
     *Uses functions Find_Highest(Avlnode) and Find_bucket(int,avlnode)
     *Used For Hash Table
     **/
    void finds(){
        
        cout<<"Highest Number of Collisions = "<<find_Highest(root)<<endl;
        cout<<"Bucket Number with Highest Collisions = "<<find_bucket(find_Highest(root),root)<<endl;
        
    }
    
    
    
    /**
     * calls function that counts the number of nodes in a tree and returns the number
     */
    int countOfNodes(){
        return countNodes(root);
    }
    
    
private:
    
    struct AvlNode  //AvlTreenode structure
    {
        Comparable Key; //Key comparable data
        AvlNode   *left;
        AvlNode   *right;
        Value Associated; //the associated value
        int height;
		bool flag; //To check if a node is present in tree or not
        
        
        AvlNode( const Comparable & theElement, AvlNode *lt, AvlNode *rt,   //default initialization
                Value k, int h = 0, bool b = true )
        : Key( theElement ), left( lt ), right( rt ), Associated(k), height( h ), flag( b ) { }
    };
    
    AvlNode *root;
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x,const Value & k, AvlNode * & t ){
        
        if( t == NULL )
            t = new AvlNode( x, NULL ,NULL,k);
        
        
        if( x < t->Key )
        {
            insert( x,k, t->left );
            if( height( t->left ) - height( t->right ) == 2 ){
                if( x < t->left->Key )
                    rotateWithLeftChild( t );
                
                else
                    doubleWithLeftChild( t );
            }
        }
        else if( t->Key < x )
        {
            
            insert( x,k, t->right );
            if( height( t->right ) - height( t->left ) == 2 ){
                if( t->right->Key < x )
                    rotateWithRightChild( t );
                
                else
                    doubleWithRightChild( t );
            }
            else
                ;  // Duplicate; do nothing
            t->height = max( height( t->left ), height( t->right ) ) + 1;
        }
    }
    
    /*
     *Recursively Traverses the tree and Counts the nodes in a tree
     */
    int countNodes(AvlNode *&t){
        
        if (t==NULL)
            return(0);
        else
            return(1 + countNodes(t->left) + countNodes(t->right));
    }
    
    
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t ){
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }
    
    
    /**
     * Internal method to print a subtree and the associated value of each key
     * rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const{
        if( t != NULL )
        {
            printTree( t->left );
            if(t->flag)
                cout <<t->Key<<"          "<<t->Associated<< endl; //prints the key and the associated value
            
            printTree( t->right );
        }
    }
    
    
    /**
     * Find the Comarable to be removed in the tree and then using lazy deletion
     * set the node to be deleted with a false flag
     * returns the number of operations for deletion
     */
    int remove( const Comparable & x,AvlNode * & t){
        
		if(t == NULL)// if tree is empty
            return 0; //item not found
        else if (x < t->Key){
            remove(x,t->left);
        }
        else if( t->Key < x){
            remove(x,t->right);
        }
        else{
            t->flag= false; //sets the deleted flag to false
        }
        
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const{
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }
    
    
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const{
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }
    
    
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( AvlNode *t ) const {
		return t == NULL ? -1 : t->height;
    }
    
    
	
    /*
	 *Checks if left node is greated or right node
     */
    int max( int lhs, int rhs ) const {
        return lhs > rhs ? lhs : rhs;
    }
    
    /**
     *Takes in the Comparable,node and the new value to update associated value
     *finds the location of the comparable and then updates its associated value
     */
    void UpdatesValue( Comparable & x,AvlNode *&t,Value & y){
        
        if(t == NULL)// if tree is empty
            return; //item not found
        
        else if (x < t->Key){
            
            UpdatesValue(x,t->left,y);
        }
        else if( t->Key < x){
            
            UpdatesValue(x,t->right,y);
        }
        else
            t->Associated +=y;
    }
    
    
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->Key )
            return contains( x, t->left );
        else if( t->Key < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
    
    /**
     *Finds the node with the Highest Value
     *Returns value assigned to global variable Highest
     **/
    
    int find_Highest(AvlNode *& t){
        
        if( t != NULL )
        {
            find_Highest( t->left );
            if(t->Associated > highest){
                highest= t->Associated; //assignes Value to global variable highest
                bucket = t->Key;
            }
            find_Highest( t->right );
        }
        return highest;
    }
    
    /**
     *Find the comparable(Bucket) with highest Value(Collisions)
     *Used for the Hash Table, to keep track of their collision
     *returns the bucket number /comparable value
     **/
    unsigned int find_bucket(int number, AvlNode *& t){
        
        if(t != NULL){
            find_bucket(number,t->left);
            if(t->Associated > number){
                bucket = t->Key;
            }
            find_bucket(number,t->right);
        }
        
        return bucket;
    }
    
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }
    
    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }
    
    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }
    
    
    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif


