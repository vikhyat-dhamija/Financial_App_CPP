#include "list.h"

#ifndef PORTFOLIO_H_INCLUDED
#define PORTFOLIO_H_INCLUDED

class portfolio
{

public:
	//List pointer abstracting the implementation of the list and hence used to show the structural bridge pattern
	list* listing;


	portfolio();
	

	portfolio(list* x);
	

};



#endif
