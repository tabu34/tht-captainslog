#ifndef SLLIST_H_
#define SLLIST_H_

//#include "CCodeProfiler.h"

template <typename Type> class SLLIter;

template <typename Type>
class SLList
{

	struct Node
	{
		Type Data;
		Node* next;
	};

	Node* Head;


public:

	friend class SLLIter<Type>;

	///////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Notes : constructs an empty list
	///////////////////////////////////////////////////////////////////////////////
	SLList()
	{
		Head = NULL;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : Destroys the list
	///////////////////////////////////////////////////////////////////////////////
	~SLList()
	{
		clear();
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : Assignment Operator
	///////////////////////////////////////////////////////////////////////////////
	SLList<Type>& operator=(const SLList<Type>& that)
	{
		if (this != &that && that.Head)
		{

			this->clear();
			Node* temp = that.Head->next;
			Node* prev = that.Head;
			Node* newPrev;

			Head = new Node;
			Head->Data = that.Head->Data;
			Head->next = NULL;
			newPrev = Head;

			while(temp)
			{
				Node* curr = new Node;
				curr->Data = temp->Data;
				curr->next = NULL;
				newPrev->next = curr;
				newPrev = curr;
				prev = prev->next;
				temp = temp->next;
			}
		}
		else if (!that.Head)
		{
			this->clear();
		}
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : Copy Constructor
	///////////////////////////////////////////////////////////////////////////////
	SLList(const SLList<Type>& that)
	{
		Head = NULL;
		this->clear();
		Node* temp = that.Head->next;
		Node* prev = that.Head;
		Node* newPrev;

		Head = new Node;
		Head->Data = that.Head->Data;
		Head->next = NULL;
		newPrev = Head;

		while(temp)
		{
			Node* curr = new Node;
			curr->Data = temp->Data;
			curr->next = NULL;
			newPrev->next = curr;
			newPrev = curr;
			prev = prev->next;
			temp = temp->next;
		}	
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : addHead
	// Parameters :	v - the item to add to the list
	///////////////////////////////////////////////////////////////////////////////
	void addHead(const Type& v)
	{
		Node* pNode = new Node;
		pNode->Data = v;
		pNode->next = Head;
		Head = pNode;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the list, freeing any dynamic memory
	///////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		Node* pDel;

		while (Head)
		{
			pDel = Head;
			Head = Head->next;
			delete pDel;
		}

	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :	index - an iterator to the location to insert at
	//				v - the item to insert
	// Notes : do nothing on a bad iterator
	///////////////////////////////////////////////////////////////////////////////
	void insert(SLLIter<Type>& index, const Type& v)
	{
		if (index.curr == NULL)
			return;

		if (index.curr == Head)
		{
			Node* newNode = new Node;
			newNode->Data = v;
			newNode->next = Head;
			Head = newNode;
			index.curr = Head;
			index.next = index.curr->next;

		}
		else
		{
			Node* temp = Head->next;
			index.prev = Head;
			index.next = Head->next->next;

			while(temp && temp != index.curr)
			{
				temp = temp->next;
				index.prev = index.prev->next;
				if (index.next)
				{
					index.next = index.next->next;
				}
			}

			Node* newNode = new Node;
			newNode->Data = v;
			newNode->next = index.curr;
			index.prev->next = newNode;
			index.curr = newNode;
			index.next = index.curr->next;

			//Node* curr = Head->next;
			//Node* prev = Head;
			//for (int i = 2; i < index; i++)
			//{
			//	if (curr)
			//	{
			//		curr = curr->next;
			//		prev = prev->next;
			//	}

			//}
			//if (curr)
			//{
			//	Node* newNode = new Node;
			//	newNode->Data = v;
			//	newNode->next = curr;
			//	prev->next = newNode;

			//}
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : remove
	// Parameters :	index - an iterator to the location to remove from
	// Notes : do nothing on a bad iterator
	///////////////////////////////////////////////////////////////////////////////
	void remove(SLLIter<Type>& index)
	{
		if (index.curr == Head)
		{
			if (Head)
			{

				index.next = Head->next;
				delete Head;
				Head = index.next;
				index.curr = index.next;
				if (index.next)
					index.next = index.curr->next;

			}

			//Node* pDel = Head;
			//Head = Head->next;
			//delete pDel;
		}

		else
		{
			Node* temp = Head->next;
			index.prev = Head;
			index.next = Head->next->next;

			while(temp && temp != index.curr)
			{
				temp = temp->next;
				index.prev = index.prev->next;
				if (index.next)
				{
					index.next = index.next->next;
				}
			}

			delete temp;
			index.prev->next = index.next;
			index.curr = index.next;
			if (index.curr)
			{
				index.next = index.curr->next;
			}

			//Node* curr = Head->next;
			//Node* prev = Head;
			//for (int i = 2; i < index; i++)
			//{
			//	if (curr)
			//	{
			//		curr = curr->next;
			//		prev = prev->next;
			//	}

			//}
			//if (curr)
			//{
			//	Node* pDel = curr;
			//	prev->next = curr->next;
			//	delete pDel;
			//}
		}
	}

	inline unsigned int size() const
	{
		unsigned int nSize = 0;

		Node* temp = Head;
		while (temp)
		{
			temp = temp->next;
			nSize++;
		}

		return nSize;
	}


};

template <typename Type>
class SLLIter
{

	SLList<Type>* List;
	typename SLList<Type>::Node * curr;
	typename SLList<Type>::Node * prev;
	typename SLList<Type>::Node * next;

public:

	friend class SLList<Type>;

	///////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Parameters :	listToIterate - the list to iterate
	///////////////////////////////////////////////////////////////////////////////
	SLLIter(SLList<Type>& listToIterate)
	{
		List = &listToIterate;
		curr = prev = next = NULL;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : begin
	// Notes : moves the iterator to the head of the list
	///////////////////////////////////////////////////////////////////////////////
	void begin()
	{
		curr = List->Head;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : end
	// Notes : returns true if we are at the end of the list, false otherwise
	///////////////////////////////////////////////////////////////////////////////
	bool end() const
	{
		return (!curr)?true:false;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : operator++
	// Notes : move the iterator forward one node
	///////////////////////////////////////////////////////////////////////////////
	SLLIter<Type>& operator++()
	{

		if (curr)
		{
			prev = curr;
			curr = curr->next;
			if (next)
				next = next->next;
		}

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : current
	// Notes : returns the item at the current iterator location
	///////////////////////////////////////////////////////////////////////////////
	Type& current() const
	{
		return curr->Data;
	}

};
#endif