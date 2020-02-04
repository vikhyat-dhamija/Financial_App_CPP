#include "account.h"
#include "portfolio.h"
#include "sorting_.h"

#ifndef STOCK_ACCOUNT_H_INCLUDED
#define STOCK_ACCOUNT_H_INCLUDED



class StockAccount :public Account
{

protected:

	sort_stat sst; // sorting strategy class object

	portfolio stock_prof; // portfolio the abstraction over the list as an object for maintaing the stock portfolio

public:



	StockAccount(list* x=NULL);// default as well as the initialising constructor


	~StockAccount();//destructor for doing exiting activities


	void update_stock_portfolio();//stock portfolio updation to the file


	void update_balance_value(double x);//update the balance value for maintaing the synchronisation between bank account and stock account


	void file_txn_add(string event, string stock, int num, double value);// for adding events to the file after successful events of buy and sell


	double credit(double x=0 ); //for buying of shares



	double fsearch(string searc);// for searching the values from reads files randomly


	double debit(double y=0);//for selling of shares

	void display();// for display of the portfolio


	void trans_history();// for displaying the transaction history

};
	

#endif
