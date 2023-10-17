#ifndef ARRAY_LIST
#define ARRAY_LIST

//Author: Josh Matni
//Date: 10/1/23
//Purpose: The header file for the arrayList class

#include "list.h"

template<class ItemType>
class ArrayList : public ListInterface<ItemType>{
    static const int DEFAULT_CAPACITY = 100;
    ItemType items[DEFAULT_CAPACITY + 1]; //(ignore item[0])
    int itemCount;
    int maxCount;
public:
	ArrayList();
    	ArrayList(const ArrayList<ItemType>& aList);

	bool isEmpty() const;
	int getLength() const;
	bool insert(int position, const ItemType& newEntry);
	bool remove(int position);
	void clear();
	ItemType getEntry(int position) const;
	ItemType replace(int position, const ItemType& newEntry);
	
	~ArrayList() {}
};

#include "arraylist.cpp"
#endif
