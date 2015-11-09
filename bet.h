#ifndef BET_H
#define BET_H
#include <iostream>
#include <stack>
#include <string>
#include <list>
#include <sstream>
#include <algorithm>

using namespace std;

	class BET {
	private:
		struct BinaryNode
    	{
    		string element;
    		BinaryNode *left;
    		BinaryNode *right;

    		BinaryNode( const string & theElement, BinaryNode *lt, BinaryNode *rt )
          	: element{ theElement }, left{ lt }, right{ rt } { }
        
        	BinaryNode( string && theElement, BinaryNode *lt, BinaryNode *rt )
          	: element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    	};
	
	public:
		//default constructors
		BET();
		//one parameter constructor
		BET(const string &postfix);
		//copy constructor
		BET(const BET &rhs);
		//destructor
		~BET();
         
        bool buildFromPostfix(const string postfix);
        //copy assignemnt operator
        const BET & operator= (const BET &rhs); 

        void printInfixExpression();

        void printPostfixExpression();

        size_t size();

        size_t leaf_nodes();

        bool empty();

    private:
    	void printInfixExpression(BinaryNode *n);
    	void makeEmpty(BinaryNode* &t);
    	BinaryNode* clone(BinaryNode *t);
    	void printPostfixExpression(BinaryNode *n);
    	size_t size(BinaryNode *t);
    	size_t leaf_nodes(BinaryNode *t);

    	
    	BinaryNode *root;
    	std::stack<BinaryNode*> s;
	};    

	// include the implementation file here
#include "bet.hpp"

#endif