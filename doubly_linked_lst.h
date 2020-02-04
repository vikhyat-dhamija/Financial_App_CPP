#include "list.h"
#include "sorting_.h"
//This is the derived class of the list class
#ifndef  DOUBLE_LL_H_INCLUDED
#define DOUBLE_LL_H_INCLUDED

class doubly_linked_list :public list
{
protected:

public:
	// Implement the same functions as the list
	doubly_linked_list();

	double fsearch(string searc);

	void insert(node* temp);

	void sort();

	double display();

	void file_add(fstream& fout);

	node* search(string stock_name); //search by the stock name and send the number of the node containing that stock

	double total();

	void delete_(node* x);
	//friend classes for the same reason so as to make these classes access the private variables
	
	~doubly_linked_list();
	
	friend class sort_stat;

	friend class sortimpl;

	friend class sortselection;

	friend class sortbubble;
	
	

};

#endif
