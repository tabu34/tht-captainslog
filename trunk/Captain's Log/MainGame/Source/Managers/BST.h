template<typename Type>
class BST
{
	struct Node
	{
		Type element;
		Node * left;
		Node * right;
	};

	Node * m_nRoot;

	void insertRecur(const Type& v, Node * cur)
	{
		Node * tempNode = new Node;

		tempNode->element = v;
		tempNode->left = NULL;
		tempNode->right = NULL;

		if(m_nRoot == NULL)
		{
			m_nRoot = tempNode;
		} else if(v < cur->element)
		{
			if(cur->left == NULL)
			{
				cur->left = tempNode;
				return;
			} else
			{
				insertRecur(v, cur->left);
			}
		} else if(v > cur->element)
		{
			if(cur->right == NULL)
			{
				cur->right = tempNode;
				return;
			} else
			{
				insertRecur(v, cur->right);
			}
		}
	}

	bool findRecur(const Type& v, Node * cur) const
	{
		if(cur == NULL)
		{
			return false;
		} else if(cur->element > v)
		{
			findRecur(v, cur->left);
		} else if(cur->element < v)
		{
			findRecur(v, cur->right);
		} else if(v == cur->element)
		{
			return true;
		}
	}



	void clearRecur(Node * cur)
	{
		if(cur == NULL)
			return;
		if(cur->left)
			clearRecur(cur->left);
		if(cur->right)
			clearRecur(cur->right);
		delete cur;
	}

	void printInOrderRecur(Node * cur) const
	{
		if(cur != NULL)
		{
			if(cur->left)
				printInOrderRecur(cur->left);
			cout << cur->element << " ";
			if(cur->right)
				printInOrderRecur(cur->right);
		}
	}

	void removeCase0(Node * node, Node * parent)
	{
		if(node == m_nRoot)
		{
			delete node;
			m_nRoot = NULL;
			return;
		}
		if(parent->left == node)
			parent->left = NULL;	
		if(parent->right == node)
			parent->right = NULL;
		delete node;
	}
	void removeCase1(Node * node, Node * parent)
	{
		Node * tempNode = node;

		if(node == m_nRoot)
		{
			if(tempNode->left)
				tempNode = tempNode->left;
			else if(tempNode->right)
				tempNode = tempNode->right;

			m_nRoot = tempNode;
		}
		else if(parent->left == tempNode)
		{
			if(tempNode->left)
				parent->left = tempNode->left;
			else if(tempNode->right)
				parent->left = tempNode->right;
		} else if(parent->right == tempNode)
		{
			if(tempNode->left)
				parent->right = tempNode->left;
			else if(tempNode->right)
				parent->right = tempNode->right;
		} 

		delete node;
	}
    
	BST<Type>& operator=(const BST<Type>& other);
	BST(const BST<Type>& other);
 
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function : Constuctor
	// Notes : constucts an empty BST
	///////////////////////////////////////////////////////////////////////////////
	BST()
	{
		m_nRoot = NULL;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : destroys the BST cleaning up any dynamic memory
	///////////////////////////////////////////////////////////////////////////////
	~BST()
	{
		clear();
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :  v - the item to insert 
	///////////////////////////////////////////////////////////////////////////////
	void insert(const Type& v)
	{
		insertRecur(v, m_nRoot);
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : findAndRemove
	// Parameters : v - the item to find (and remove if it is found)
	// Return : bool - true if the item was removed, false otherwise
	///////////////////////////////////////////////////////////////////////////////
	bool findAndRemove(const Type& v)
	{
		// Find the target node and parent
		Node * targetNode = NULL;
		Node * parentNode = NULL;

		Node * iter = m_nRoot;
		bool found = false;

		while(true)
		{
			if(iter == NULL)
			{
				return false;
			}
			else if(iter->element > v)
			{
				parentNode = iter;
				iter = iter->left;
			}
			else if(iter->element < v)
			{
				parentNode = iter;
				iter = iter->right;
			}
			else if(iter->element == v)
			{
				targetNode = iter;
				found = true;
				break;
			}

			
		}

		// remove item

		// case 2
		if(targetNode->left != NULL && targetNode->right != NULL)
		{

			iter = targetNode->right;
			Node * minElement = iter;
			Node * minElementParent = iter;

			while(true)
			{
				minElementParent = minElement;
				if(iter->element < minElement->element)
				{
					minElement = iter;
				}

				if(iter->left != NULL)
				{
					iter = iter->left;
				}
				else
				{
					break;
				}
			}


			Node * tempNode = targetNode;
			targetNode->element = minElement->element;
			minElement->element = tempNode->element;

			// case 0
			if(minElement->left == NULL && minElement->right == NULL)
			{
				removeCase0(minElement, minElementParent);
			}

			// case 1
			else if(minElement->left != NULL || minElement->right != NULL)
			{
				removeCase1(minElement, minElementParent);
			}


			
		}

		// case 0
		else if(targetNode->left == NULL && targetNode->right == NULL)
		{
			removeCase0(targetNode, parentNode);
		}

		// case 1
		else if(targetNode->left != NULL || targetNode->right != NULL)
		{
			removeCase1(targetNode, parentNode);
		}

		

		return true;

	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : find
	// Parameters : v - the item to find
	// Return : bool - true if the item was found, false otherwise
	///////////////////////////////////////////////////////////////////////////////
	bool find(const Type& v) const
	{
		return findRecur(v, m_nRoot);
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the BST, cleaning up any dynamic memory
	///////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		clearRecur(m_nRoot);
		m_nRoot = NULL;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : printInOrder
	// Notes : prints the contents of the BST to the screen, in ascending order
	///////////////////////////////////////////////////////////////////////////////
	void printInOrder() const
	{
		printInOrderRecur(m_nRoot);
		cout << '\n';
	}

};