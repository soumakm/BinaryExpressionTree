	bool isOperand(string x)
	{
		if(x != "+" &&  x != "-" && x != "*" && x != "/" && x != "(" && x != ")")
			return true;
		else
			return false;
	}

	bool isOperator(string x)
	{
		if(x == "+" || x == "-" || x == "*" || x == "/")
			return true;
		else 
			return false;
	}

//This function returns true if 2nd argument has lower precedence than the first
	bool isLowerPrecedence(string operator1, string operator2)
	{
	   
        if(operator2 == "-" && operator1 != "-")
        	return true;
        else if (operator2 == "+" && (operator1 == "*" || operator1 == "/"))
        	return true;
        else if (operator2 == "/" && operator1 == "*")
        	return true;
        else
        	return false;
	}

	//default constructors
	BET::BET() : root{ nullptr }
	{}

	//one parameter constructor, build tree here
	BET::BET(const string &postfix)
	{
		list<string> tokens;
		string buf;
		stringstream ss(postfix);
		while (ss >> buf)
			tokens.push_back(buf);

		for (auto & x: tokens)
	    {
	    	if(isOperand(x))
	    	{
	    		//create one-node tree
	    		BinaryNode *t = new BinaryNode{x, nullptr, nullptr};
	    		s.push(t);
	    	}

	    	if(isOperator(x))
	    	{
	    		//pop two nodes from stack and form a new node with children
	    		BinaryNode *t1;
	    		BinaryNode *t2;

	    		t1 = s.top();
	    		s.pop();
	    		t2 = s.top();
	    		s.pop();

	    		BinaryNode *t = new BinaryNode{x, t2, t1};
	    		s.push(t);
	    	}

	    }
	    //set the root
	    root = s.top();	
	    s.pop();
	}

	//copy constructor
	BET::BET(const BET &rhs) : root{ nullptr }
	{
		root = clone(rhs.root);
	}

	//destructor
	BET::~BET()
	{
		makeEmpty(root);
	}

	//copy assignemnt operator
    const BET & BET::operator= (const BET &rhs)
    {
    //	BET copy = rhs;
    //   std::swap( *this, copy );

        if (&rhs == this)
            return *this;
        makeEmpty(root);
        root = clone(rhs.root);
        return *this;
    }

    bool BET::buildFromPostfix(const string postfix)
    {
    	list<string> tokens;
		string buf;
		stringstream ss(postfix);
		bool success = false;
		while (ss >> buf)
			tokens.push_back(buf);

		makeEmpty(root);
		for (auto & x: tokens)
	    {
	    	if(isOperand(x))
	    	{
	    		//create one-node tree
	    		BinaryNode *t = new BinaryNode{x, nullptr, nullptr};
	    		s.push(t);
	    		success = true;
	    	}

	    	else if(isOperator(x))
	    	{
	    		//pop two nodes from stack and form a new node with children
	    		BinaryNode *t1;
	    		BinaryNode *t2;

	    		t1 = s.top();
	    		s.pop();
	    		t2 = s.top();
	    		s.pop();

	    		BinaryNode *t = new BinaryNode{x, t2, t1};
	    		s.push(t);
	    		success = true;

	    	}
	    	else
	    	{
	    		success = false;
	    		break;
	    	}

	    }	
	    //set the root
	    root = s.top();	
	    s.pop();
	    return success;
    }

    void BET::printInfixExpression()
    {
    	printInfixExpression(root);
    	std::cout << std::endl;

    }

    void BET::printPostfixExpression()
    {
    	printPostfixExpression(root);
    	std::cout << std::endl;
    }

    size_t BET::size()
    {
    	return size(root);
    }

    size_t BET::leaf_nodes()
    {
    	return leaf_nodes(root);
    }

    bool BET::empty()
    {
    	return root == nullptr;
    }

// private methods 
    

    void  BET::makeEmpty(BinaryNode* &t)
    {
    	if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;

    }

    BET::BinaryNode*  BET::clone(BET::BinaryNode *t)
    {
    	 if( t == nullptr )
            return nullptr;
        else
            return new BET::BinaryNode{ t->element, clone( t->left ), clone( t->right ) };

    }

    //this is inorder traversal!!
    void  BET::printInfixExpression(BinaryNode *n)
    {
    	if(n != nullptr)
    	{
    		if(isOperator(n->element) && n != root)
    		{
    			std::cout << "(" << " ";
    		}
    		printInfixExpression(n->left);
    		std::cout << n->element << " ";
    		printInfixExpression(n->right);
    		if(isOperator(n->element)  && n != root)
    		{
    			std::cout << ")" << " ";
    		}
    		

    	}
    }

    //this is postorder traversal!!
    void  BET::printPostfixExpression(BinaryNode *n)
    {
    	if(n != nullptr)
    	{
    		printPostfixExpression(n->left);
    		printPostfixExpression(n->right);
    		std::cout << n->element << " ";
    		
    	}
    }

    size_t  BET::size(BinaryNode *t)
    {
    	size_t count = 0;
    	if(t == nullptr)
    		return 0;

    //	if(t->left !=nullptr || t->right !=nullptr)
    //	{
    		count++;
    		count += size(t->left);
    		count += size(t->right);
    //	}
    	return count;
    }

    size_t  BET::leaf_nodes(BinaryNode *t)
    {
    	size_t count = 0;
    	if(t == nullptr)
    		return 0;

    	if(t->left ==nullptr && t->right ==nullptr)
    	{
    		count++;
    	}
    	else
    	{
    		count += leaf_nodes(t->left);
    		count += leaf_nodes(t->right);
    	}
    	return count;

    }
