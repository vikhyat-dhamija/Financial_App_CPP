#include<string>

using namespace std;

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
//Data structure for the node has been made through the class
class node
{
public:
	string stock_name;
	int number_shares;

	node* forward;
	node* back;

	node(string name, int number);//constructor
	

};


#endif
