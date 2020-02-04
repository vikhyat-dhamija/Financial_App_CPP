#include<string>
#include "account.h"

using namespace std;

#ifndef BANK_ACCOUNT_H_INCLUDED
#define BANK_ACCOUNT_H_INCLUDED

class BankAccount :public Account
{


public:

	BankAccount();  //Constructor
	

	~BankAccount(); //Destructor
	

	void file_update_balance();  //Function to update balance in file
	

	double debit(double amt);   // Implementation of debit virtual function


	void record_transaction(string event, double amount, double balance);  // function to record the transactions in the file
	


	void display_transactions_history(); // function to display the transactions history 
	

	double credit(double amt);  // Implementation of credit virtual function
	

	void display_balance();  // Function for displaying balance
	

	double get_balance_value(); //get balance function
	

	void update_balance_value(double x); // update balance function so as to make synchronisation between bankaccount and stockaccount balance
	

};

#endif