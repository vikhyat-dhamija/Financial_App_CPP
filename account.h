#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED

class Account
{
protected:
	double account_balance;// account balance 

public:

	virtual double credit(double) = 0;  // virtual function for credit

	virtual double debit(double) = 0;   // virtual function for debit 

	double get_cash_balance_value();// for getting the cash balance
	


};


#endif
