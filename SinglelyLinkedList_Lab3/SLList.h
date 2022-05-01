#pragma once
#include "DynArray.h"
template<typename Type> class SLLIter;
template<typename Type> class SLList;




template<typename Type>
class SLList
{
	
	struct Node
	{
		Type data;
		Node* next;

	public:
		Node(Type v = NULL, Node* Next = nullptr)
		{
			data = v;
			next = Next;
		}
		

		friend class SLList<Type>;
		friend class SLLIter<Type>;

	};

private:
	Node* head = nullptr;
	unsigned int Size = 0;


public:
	friend class SLLIter<Type>;
		/////////////////////////////////////////////////////////////////////////////
		// Function : Constructor
		// Notes : Does nothing because members were initialized above.
		//		Still needs to exist due to copy constructor
		/////////////////////////////////////////////////////////////////////////////
	SLList();

		/////////////////////////////////////////////////////////////////////////////
		// Function : Destructor
		// Notes : Destroys the list (call clear())
		/////////////////////////////////////////////////////////////////////////////
	~SLList();

		/////////////////////////////////////////////////////////////////////////////
		// Function : Assignment Operator
		// Notes: Performs a deep copy of that list. HINT: Much easier to do via
		//		recursion. Make a helper function that calls addHead() as the
		//		stack unwinds (meaning it happens backwards).
		/////////////////////////////////////////////////////////////////////////////
	SLList<Type>& operator=(const SLList<Type>& that);

		/////////////////////////////////////////////////////////////////////////////
		// Function : Copy Constructor
		// Notes:	Calls the assignment operator.
		/////////////////////////////////////////////////////////////////////////////
	SLList(const SLList<Type>& that);

		/////////////////////////////////////////////////////////////////////////////
		// Function : addHead
		// Parameters :	v - the item to add to the front of the list
		/////////////////////////////////////////////////////////////////////////////
	void addHead(const Type& v);

		/////////////////////////////////////////////////////////////////////////////
		// Function : clear
		// Notes : clears the list, freeing any dynamic memory
		/////////////////////////////////////////////////////////////////////////////
	void clear();
		/////////////////////////////////////////////////////////////////////////////
		// Function : insert
		// Parameters :	index - an iterator pointing at the location to insert at
		//				v - the item to insert
		// Notes : The new node should be inserted to the left of index's current
		//		pointer. Do nothing if index's current pointer is null
		/////////////////////////////////////////////////////////////////////////////
	void insert(SLLIter<Type>& index, const Type& v);

		/////////////////////////////////////////////////////////////////////////////
		// Function : remove
		// Parameters :	index - an iterator pointing at the node to be deleted
		// Notes : Do nothing if index's current pointer is null
		/////////////////////////////////////////////////////////////////////////////
	void remove(SLLIter<Type>& index);

		/////////////////////////////////////////////////////////////////////////////
		// Function : size
		// Return : the number of items stored in the linked list.
		/////////////////////////////////////////////////////////////////////////////
	inline unsigned int size() const;

	void helper(Node* n);
};

template<typename Type>
inline SLList<Type>::SLList()
{
}

template<typename Type>
inline SLList<Type>::~SLList()
{
	clear();
}

template<typename Type>
inline SLList<Type>& SLList<Type>::operator=(const SLList<Type>& that)
{
	if (this != &that)
	{
		clear();
		helper(that.head);
		
	}
	
	return *this;
}

template<typename Type>
inline SLList<Type>::SLList(const SLList<Type>& that)
{
	*this = that;
	
}

template<typename Type>
inline void SLList<Type>::addHead(const Type& v)
{
	Node* newNode = new Node(v);
	newNode->next = head;
	head = newNode;
	Size++;
	
	
}

template<typename Type>
inline void SLList<Type>::clear()
{
	
	while (head != nullptr)
	{
		Node* curr = head;
		head = head->next;
		delete curr;
		Size--;

	}
	head = nullptr;

}

template<typename Type>
inline void SLList<Type>::insert(SLLIter<Type>& index, const Type& v)
{
	if (index.curr != nullptr)
	{
		if (index.curr == head)
		{
			addHead(v);
			index.curr = head;
		}
		else
		{
			Node* temp = new Node(v);
			index.prev->next = temp;
			temp->next = index.curr;
			index.curr = temp;
			Size++;
		}
	}
}

template<typename Type>
inline void SLList<Type>::remove(SLLIter<Type>& index)
{
	Node* temp = index.curr;
	if (head != nullptr)
	{
		if (index.curr == head)
		{
			head = head->next;
			index.curr = head;
			Size--;
		}
		else if (index.curr == nullptr)
		{
			index.prev->next = index.curr;
		}
		else
		{
			index.curr = index.curr->next;
			index.prev->next = index.curr;
			Size--;
		}
		
			delete temp;
	}
}

template<typename Type>
inline unsigned int SLList<Type>::size() const
{
	return Size;
}

template<typename Type>
inline void SLList<Type>::helper(Node* n)
{
	if (n != nullptr)
	{
		helper(n->next);
		addHead(n->data);
	}
}




template<typename Type>
class SLLIter
{


private:
	SLList<Type>* ptrList;
	typename SLList<Type>::Node* curr;
	typename SLList<Type>::Node* prev;


public:

	friend class SLList<Type>;

	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Parameters :	listToIterate - the list to iterate
	// Notes: Set your list pointer to point at this list's address
	/////////////////////////////////////////////////////////////////////////////
	SLLIter(SLList<Type>& listToIterate);

	/////////////////////////////////////////////////////////////////////////////
	// Function : begin
	// Notes : moves the iterator to the head of the list you are pointing at
	/////////////////////////////////////////////////////////////////////////////
	void begin();

	/////////////////////////////////////////////////////////////////////////////
	// Function : end
	// Notes : return true if current is null. False otherwise 
	/////////////////////////////////////////////////////////////////////////////
	bool end() const;

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator++
	// Notes : Move the current pointer to its own next
	/////////////////////////////////////////////////////////////////////////////
	SLLIter<Type>& operator++();

	/////////////////////////////////////////////////////////////////////////////
	// Function : current
	// Notes : returns the item at the current iterator location. Does not
	//		perform error checking
	/////////////////////////////////////////////////////////////////////////////
	Type& current() const;



};

template<typename Type>
inline SLLIter<Type>::SLLIter(SLList<Type>& listToIterate)
{
	ptrList = &listToIterate;
	
}

template<typename Type>
inline void SLLIter<Type>::begin()
{
	prev = nullptr;
	curr = ptrList->head;
}

template<typename Type>
inline bool SLLIter<Type>::end() const
{
	if (curr == nullptr)
	{
		return true;
	}
	else {

		return false;
	}
}

template<typename Type>
inline SLLIter<Type>& SLLIter<Type>::operator++()
{
	if (end() == false)
	{
		prev = curr;
		curr = curr->next;
	}
	
	
	return *this;
}

template<typename Type>
inline Type& SLLIter<Type>::current() const
{

	return curr->data;
}


//for (begin(); end(); ++)
//{
//	if (index != nullptr)
//	{
//		if (index == curr)
//		{
//			prev->next = curr->next;
//			delete[] curr;
//		}
//	}
//}
//Size--;