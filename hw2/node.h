#ifndef NODE
#define NODE

//Author: Josh Matni
//Date: 10/1/23
//Purpose: the Node class header file

template<class ItemType>
class Node{
	ItemType item; // A data item
	Node<ItemType>* next; // Points to next node
public:
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
	void setItem(const ItemType& anItem);
	void setNext(Node<ItemType>* nextNodePtr);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;
}; 

#include "node.cpp"
#endif