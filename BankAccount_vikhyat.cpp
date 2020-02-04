#include <iostream>
#include<vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include<new>
#include<string>
#include <ctime>
#include<stdlib.h>
#include<math.h>
#include "bankaccount.h"

using namespace std;


    BankAccount::BankAccount()
	{
		fstream filein;

		filein.open("account_balance.txt");  //Try to open the file

		if (!filein)//If not open
		{
			filein.open("account_balance.txt", ios::out);//Then open the file in the current directory
			account_balance = (double)10000;//Take the balance as the 10000 as desired by the problem statement
			filein << 10000;//also update the file for further taking the account value by the stock account
		}
		else
		{

			filein >> account_balance; // Otherwise incase file exists take the account balance value from the file

		}

	}

	BankAccount::~BankAccount()
	{
		fstream fileout;
		//Open the file for updating the latest value of the balance
		fileout.open("account_balance.txt", ios::out | ios::trunc);

		if (!fileout)
		{
			cout << "file could not be opened" << endl;

		}
		else
		{

			fileout << account_balance;

		}

	}

	void BankAccount::file_update_balance()
	{
		fstream fileout;
		//Same as done in the destructor but here separate function so as to make synchronisation
		fileout.open("account_balance.txt", ios::out | ios::trunc);

		if (!fileout)
		{
			cout << "file could not be opened" << endl;

		}
		else
		{

			fileout << account_balance;

		}

	}

	double BankAccount::debit(double amt)
	{
		if (amt < 0)//checking the amount value for less than 0 as it is invalid
		{
			cout << "Please enter the correct amount value......" << endl;
			return 0;

		}
		
		if ((account_balance -= amt) >= 0)
		{
			cout << endl << "Amount withdrawn sucessfully...." << endl;
			record_transaction("Withdraw", amt, account_balance);
			file_update_balance();
			return 1;
		}
		else
		{
			account_balance += amt;
			cout << "Balance is not sufficient for withdrawal" << endl;
			return 0;

		}

	}

	//Function to record transactions in the file
	void BankAccount::record_transaction(string event, double amount, double balance)//whenever the event of deposit with drwal happen then record transaction function is called
	{
		fstream fout;

		fout.open("bank_transactions.txt", ios::out | ios::app);//open file

		time_t my_time = time(NULL);//for time printing

		char str[30];

		ctime_s(str, sizeof(str), &my_time);//function in time header for getting current time in str


		fout << setw(15) << event << "\t" << setw(15) << amount << "\t" << setw(15) << balance << "\t" << setw(15) << str << "\n";

		fout.close();
	}

	// This function is based on the above function that is it takes input from the bank transactions file and dispaly on the screen
	void BankAccount::display_transactions_history()
	{

		fstream fin;
		vector<string> row;
		string line, word, temp;

		fin.open("bank_transactions.txt", ios::in);

		if (!fin) {

			cout << "Unable to open file" << endl;
		}

		cout << setw(15) << "Event" << "\t" << setw(15) << "Amount" << "\t" << setw(15) << "Balance" << "\t" << setw(20) << "Date Time" << endl;

		while (fin >> temp) {

			row.clear();


			getline(fin, line);


			stringstream s(line);


			while (getline(s, word, '\t')) {

				row.push_back(word);

			}

			cout << setw(15) << temp << "\t" << setw(15) << row[1] << "\t" << setw(15) << row[2] << "\t" << setw(15) << row[3] << "\t" << endl;

		}

		fin.close();

	}

	double BankAccount::credit(double amt)
	{
		if (amt < 0)//check for the value less than 0 as it is invalid
		{
			cout << "Please enter the correct amount value......" << endl;
			
		}
		else
		{
			account_balance += amt;
			cout << endl << "Amount deposited sucessfully...." << endl;
			record_transaction("Deposit", amt, account_balance);
			file_update_balance();
		}
		return 0;

	}

	void BankAccount::display_balance()
	{
		cout << endl << "Account Balance is : $" << account_balance;//Normal display function

	}

	double BankAccount::get_balance_value()
	{
		return account_balance;//normal get balance function

	}

	void BankAccount::update_balance_value(double x)
	{

		account_balance = x;//for updating the account balance

	}

