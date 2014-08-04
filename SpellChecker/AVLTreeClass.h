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
// bool SearchWords( x )              --> Return true if x is present
// void printTree( )                  --> Print tree in sorted order
// void printinLevelOrder()           --> Prints the tree in Level Order
// void ipl(i)                        --> Computes and outputs the Internal Path Lengths
// int CountOfNodes()                 --> Computes and returns the # of nodes
// void manipulaton()                 --> computes and outputs various manipulation of avl tree
// ********************************ERRORS**************************************************************

int  CountOfRecursiveInserts=0,NumberOfSingleRotations=0,NumberOfDoubleRotations=0,numberofops=0;

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
     * Inserts x into the avl tree, with its line number inputted in the associated list
     */
    void insertword(const Comparable & x , int & num ,const Value & linenumber){

        insertswords( x,num,root,linenumber);
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
    bool SearchWord( Comparable & x){
        
        return SearchWord(x, root);
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
     *Print the tree in level order , all nodes in each level
     */
    void PrintInlevelOrder() const{
        if(isEmpty())
            cout<<"Empty Tree"<<endl;
        else
            PrintLevel();
    }

    /*
     *Calls function which calculate the Internal Path lengths depending on the type of output desired.
     */
    void ipl(int i){
        int value = 0;
        int result=InternalPathLength(root, value);
        if(i==1){
            cout<<"The Internal Path Length is= "<<result<<endl;
        }
        else if(i == 2){
            double nodes = countNodes(root);
            cout<<"C: The Internal Path Length is= "<<result<<endl;
            cout<<"   Divided by Number of Nodes= "<<result/nodes<<endl;
        }
		else if(i==3){  
		cout<<"G:IPL by excluding deleted (False flag) nodes = "<<InternalPathLengthwithFlags(root,value)<<endl;
	}
       
    }
    
    /**
     * calls function that counts the number of nodes in a tree and returns the number
     */
    int countOfNodes(){
        return countNodes(root);
    }

    /**
     *Public Function when called obtains values from all manipulations of the avl tree
     *Outputs the results to the user
     */
    void manipulations(){

       double Nodes= countOfNodes();
       float AvgSingleRotations = NumberOfSingleRotations/Nodes;  //calculate avg single rotations
       float AvgDoubleRotations = NumberOfDoubleRotations/Nodes;  //calculates avg double rotations
       cout<<"A:Average Number Of Single Rotations  ="<<AvgSingleRotations<<endl; //outputs
	   cout<<" Average Number Of Double Rotations  = "<<AvgDoubleRotations<<endl;

        float AvgNumberOfRecursiveCalls =  CountOfRecursiveInserts/Nodes;   //calculates the average recursive inserts
        cout<<"B:Average Number of Recursive Inserts "<<AvgNumberOfRecursiveCalls<<endl; //outputs
        cout<<"  Logarithmic Number for node Log("<<Nodes<<") "<<log(Nodes)<<endl; //calculates actual logarithmic value of nodes

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
     *Internal method to insert words into a subtree.along with the lines they appear on
     * Tree is rebalanced on every indertion using the single and double rotation functions
     *the lines are then pushed into a list associated with every node
     */
    void insertswords(const Comparable & x,int& num,AvlNode *& t,const Value & linenums){

        if(t== NULL){
            t= new AvlNode(x,NULL,NULL,linenums);
              t->Associated.push_back(num);
			  t->Associated.unique();
        }


        if( x < t->Key )
        {
            CountOfRecursiveInserts++;
            insertswords(x, num , t->left,t->Associated);
            if( height( t->left ) - height( t->right ) == 2 ){
                if( x < t->left->Key ){
					NumberOfSingleRotations++;
                    rotateWithLeftChild( t );
					}
                else{
					NumberOfDoubleRotations++;
                    doubleWithLeftChild( t );
					}
           		 }

          }
        else if( t->Key < x )
        {
          	CountOfRecursiveInserts++;
            insertswords( x,num, t->right,t->Associated);
            if( height( t->right ) - height( t->left ) == 2 ){
                if( t->right->Key < x ){
					NumberOfSingleRotations++;
                    rotateWithRightChild( t );
				}
                else{
					NumberOfDoubleRotations++;
                    doubleWithRightChild( t );
				}
            }
        }
        else{
           t->Associated.unique();
           t->Associated.push_back(num);
        }

    t->height = max( height( t->left ), height( t->right ) ) + 1;

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

        numberofops++; //increments number of operations.
        return numberofops; //returns the number
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


	
    /**
     * Calls function levelrecursive through a for loop to print nodes on each level
     **/
    void PrintLevel() const{
        int h = height(root);
            for(int i=0;i<=h;i++){
                levelRecursive(root, i, 0, h);
                cout<<endl;
        }
    }

    /**
     *current level: the level for which all nodes are to be printed
     *level: for comparison if current level is < or >
     * Recursively Prints each node in the level.
     */
    void levelRecursive(AvlNode *t,const int &level,const int currentlevel,int const &height)const{
        if(currentlevel <level){
            if (t != NULL )
                levelRecursive(t->left, level, currentlevel+1, height);
            else
                levelRecursive(NULL, level, currentlevel+1, height);
            if(t != NULL)
                levelRecursive(t->right, level, currentlevel+1, height);
            else
                levelRecursive(NULL, level, currentlevel+1, height);
        }
        else if(currentlevel == level){
            string prespaces= " ";
            string spaces=" ";
            for(int i=0;i<pow(2.0,(double)(height -level));i++){  //calculates for space formating in level order output.
                prespaces += " ";
                spaces +=" ";
            }
            prespaces=prespaces.substr(1);
            cout<<prespaces;
            if(t!=NULL){
                if(t->flag == true)
                    cout<<t->Key<<"[T]";
                else
                    cout<<"NULL[F]";
              }
            else
                cout<<"NULL"<<spaces;
        }
        else return;
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
            t->Associated = y;
    }


    /**
     * Returns true if x is found in the tree.
     * If found also prints out the lines on which it is found
     * by calling function to print the associated list values.
     */
    bool SearchWord( Comparable & x,AvlNode *& t)const{

            while( t != NULL )
                if( x < t->Key )
                    t = t->left;
                else if( t->Key < x )
                    t = t->right;
                else if(t->flag == true){
                    cout<<"The word is found on lines: ";
                    PrintLineNumbers(t->Associated);
                    cout<<endl;
                    return true;
                }                   // Match

            return false;   // No match
        }


    /**
     *Prints the list of line numbers against each the key.
     */
    void PrintLineNumbers(const list<int> & lines) const{

        list<int>::const_iterator i;
        for( i=lines.begin();i != lines.end();++i){
            cout<< *i<<" ";
        }
    }

    /**
     *Calculates path length using a recursive function
     */
    int InternalPathLength(AvlNode *& t,int length){
        if(t == NULL)
        {
            return 0;
        }
        return(length+(InternalPathLength(t->left,length+1)+InternalPathLength(t->right,length+1)));
    }


    /**
     *Calculates path length using a recursive function excluding the deleted nodes.
     */
    int InternalPathLengthwithFlags(AvlNode *&t,int length){
        if(t==NULL){
            return 0;
		}
		
		return(length+(InternalPathLengthwithFlags(t->left,length+1)+InternalPathLengthwithFlags(t->right,length+1)));
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


