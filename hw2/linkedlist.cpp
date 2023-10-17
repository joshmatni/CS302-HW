//Author: Josh Matni
//Date: 10/1/23
//Purpose: Implementation for LinkedList Class

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const{
	// enforce precondition
	if((position >= 1) && (position <= itemCount)){
		// Count from the beginning of the chain
		Node<ItemType>* curPtr = headPtr;
		for (int skip = 1; skip < position; skip++){
			curPtr = curPtr->getNext();
		}
		return curPtr;
	}
	return nullptr;
} 

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0){}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList)
{
	headPtr = nullptr;
	itemCount = 0;
	Node<ItemType>* currentPtr = aList.headPtr;
	Node<ItemType>* newListTail = nullptr;  // pointer to last node in new list

	while(currentPtr != nullptr)
	{
		Node<ItemType>* newNode = new Node<ItemType>(currentPtr->getItem());

		if(headPtr == nullptr) // case for empty new list
		{
			headPtr = newNode;
		}
		else  // attach the new node to the end of the new list
        {
            newListTail->setNext(newNode);
        }

        newListTail = newNode; // tail becomes last inputted node
        currentPtr = currentPtr->getNext(); // move to next node in original list
        itemCount++;
	}
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const{
	return itemCount == 0;
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const{
	return itemCount;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
    bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
    
    if(ableToInsert)
    {
        Node<ItemType>* newEntry_node = new Node<ItemType>(newEntry); // allocate new node for newEntry
        
        // insert at start
        if(newPosition == 1)
        {
            newEntry_node->setNext(headPtr);
            headPtr = newEntry_node;
        }
        else
        {
            Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
            if(prevPtr != nullptr) // check if were at end of list
            {
                newEntry_node->setNext(prevPtr->getNext()); // point to prev's old node
                prevPtr->setNext(newEntry_node);
            }
        }
        itemCount++;
        return true;
    }
    return false;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(int position){
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove){
		Node<ItemType>* ptrToDelete = nullptr;
		if (position == 1){
			// Remove the first node in the chain
			ptrToDelete = headPtr; // Save pointer to node 
			headPtr = headPtr->getNext();// save pointer to next node
		}
		else{
			// Find node that is before the one to remove
			Node<ItemType>* prevPtr = getNodeAt(position - 1);
			// Point to node to remove
			ptrToDelete = prevPtr->getNext();
			// Disconnect indicated node from chain by connecting the prior node with the one after
			prevPtr->setNext(ptrToDelete->getNext());
		}

		ptrToDelete->setNext(nullptr);
		delete ptrToDelete;
		ptrToDelete = nullptr;
		itemCount--; // Decrease count of entries
	}
	return ableToRemove;
}

template<class ItemType>
void LinkedList<ItemType>::clear()
{
	Node<ItemType>* currentPtr = headPtr;
	while(currentPtr != nullptr)
	{
		Node<ItemType>* nextNode = currentPtr->getNext(); // get addr of Next Node
		delete currentPtr; // delete current Node
		currentPtr = nextNode; // update current node
	}
	headPtr = nullptr; // shows list is now empty
	itemCount = 0;
}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const 
{
	Node<ItemType>* currentNode = getNodeAt(position);
	if(currentNode != nullptr) //check for a seg fault
	{
		return currentNode->getItem();
	}
	throw "Node not found";
} 

template<class ItemType>
ItemType LinkedList<ItemType>::replace(int position, const ItemType& newEntry){
	// enforce precondition
	bool ableToReplace = (position >= 1) && (position <= itemCount);
	if (ableToReplace){
		Node<ItemType>* nodePtr = getNodeAt(position);
		ItemType oldEntry = nodePtr->getItem();
		nodePtr->setItem(newEntry);	
		return oldEntry;	
	} 
	throw "Item not found";
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList(){
	clear();
} 
