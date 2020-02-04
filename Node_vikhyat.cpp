#include<string>
#include "node.h"

using namespace std;


//constructor to initiate the node
//note no default constructor
	node::node(string name, int number)
	{
		stock_name = name;
		number_shares = number;
	}
