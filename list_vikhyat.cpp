#include "node.h"
//same as the header only as all functions are virtual here
class list
{
protected:

	node* first;
	node* last;

public:

	virtual void insert(node*) = 0;
	virtual void sort() = 0;
	virtual double display() = 0;
	virtual void file_add(fstream&) = 0;
	virtual node* search(string) = 0;
	virtual double total() = 0;
	virtual void delete_(node*) = 0;
	virtual ~list()
	{};
};
