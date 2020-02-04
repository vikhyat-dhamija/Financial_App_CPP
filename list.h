#include "node.h"



#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
//This class has been made to make the bridge structural design pattern
class list
{
protected:

	node* first;
	node* last;

	

public:
	//All functions as template for the children or derived class to implement themselves
	virtual void insert(node*) = 0;//insert
	virtual void sort() = 0;//sort
	virtual double display() = 0;//display
	virtual void file_add(fstream&) = 0;//file adding
	virtual node* search(string) = 0;//search
	virtual double total() = 0;//kind of reduce function as explained in the description
	virtual void delete_(node*) = 0;//delete
	virtual double fsearch(string) = 0;//file serach
	virtual ~list()
	{};

	// These friend classes are made to make these classes to acces the private variables of the list i.e. the first and the last 
	//in order to sort the list
	friend class sort_stat;

	friend class sortimpl;

	friend class sortselection;

	friend class sortbubble;

	

};




#endif
