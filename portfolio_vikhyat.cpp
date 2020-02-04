#include "portfolio.h"
   
  //default constructor
   portfolio::portfolio()
	{
		listing = NULL;
	}

   //for setting the list pointer in the portfolio at run time to showcase the strutural bridge design pattern
	portfolio::portfolio(list* x)
	{
		listing = x;
	}

