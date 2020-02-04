#include "stock_account.h"
#include "doubly_linked_lst.h"
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
// The most important class of our project
	StockAccount::StockAccount(list* x) :stock_prof(x)
	{

		fstream filein;
		// same as the bank account
		filein.open("account_balance.txt");// open the account_balance class 

		if (!filein)// if not opened 
		{
			filein.open("account_balance.txt", ios::out);//open the file in the local directory
			account_balance = (double)10000;//and initialise the account balance
			filein << 10000;//also update the file
		}
		else
		{

			filein >> account_balance;//otherwise if the file is existing then taking the value from that file

		}

		fstream fin;

		vector<string> row;
		string line, word, temp;
		int number;

		fin.open("stock_portfolio.txt");

		// This is for loading the stock portfolio from the text file to the portfolio data structure
		while (fin >> temp)
		{

			fin >> number;
			//cout<<temp<<number;
			stock_prof.listing->insert(new node(temp, number));

		}

		fin.close();


	}

	//destructor put all the stock portfolio into the file and the balance will be put in the file by bank account class object
	StockAccount::~StockAccount()
	{
		fstream fout, fout1;

		fout.open("stock_portfolio.txt", ios::out | ios::trunc);
		fout1.open("total_portfolio.txt", ios::out | ios::app);


		stock_prof.listing->file_add(fout);

		time_t my_time = time(NULL);

		char str[30];

		ctime_s(str, sizeof(str), &my_time);

		fout1 << setw(15) << this->get_cash_balance_value() << "\t" << setw(15) << stock_prof.listing->total() << "\t" << str << "\n";

		fout.close();

		fout1.close();



	}
	//update the stock portfolio file after any change so this function is called
	void StockAccount::update_stock_portfolio()
	{
		fstream fout;
		fout.open("stock_portfolio.txt", ios::out | ios::trunc);// truncate for every storage of data
		stock_prof.listing->file_add(fout);
		fout.close();

	}

	void StockAccount::update_balance_value(double x)
	{
		// for updating the balance value
		account_balance = x;

	}

	void StockAccount::file_txn_add(string event, string stock, int num, double value)
	{
		// for inserting the events into the file
		fstream fout;

		fout.open("stock_transactions.txt", ios::out | ios::app);

		time_t my_time = time(NULL);

		char str[30];

		ctime_s(str, sizeof(str), &my_time);


		// Insert the data to file
		fout << setw(15) << event << "\t" << setw(15) << stock << "\t" << setw(15) << num << "\t" << setw(15) << value << "\t" << setw(15) << (num * value) << "\t" << setw(15) << str << "\n";

		fout.close();

	}



	double StockAccount::credit(double x )//for buying of shares
	{
		// credit has been taken as the buying purpose in the stockaccount
		string input;
		int num;
		double max_val, share_value;
		int flag = 0;
		string discard;
		int check = 1;

		//take the input
		cout << "Please enter the company whose shares you want to purchase" << endl;
		cin >> input;
		//search in the file if returned 0 then not
		if (!fsearch(input))
		{
			cout << "Incorrect Symbol" << endl;
		}
		else
		{  // Then asked to enter the number of shares 
			
			do {
				cout << "Please enter the number of shares you want to purchase" << endl;
				if (!(cin >> num))
				{
					cout <<endl<<"Please enter the valid value...." << endl;
					cin.clear();
					cin >> discard;
				}
				else
				{
					check = 0;
				}
			} while (check == 1);
			
			check = 1;

			cin.seekg(0, ios::end);
			cin.clear();
			

			do {
				cout << "Please enter the maximum value you want to enter......" << endl;
				if (!(cin >> max_val))
				{
					cout << endl << "Please enter the valid value...." << endl;
					cin.clear();
					cin >> discard;
				}
				else
				{
					check = 0;
				}
			} while (check == 1);

			check = 1;

			cin.seekg(0, ios::end);
			cin.clear();

			// above asked the maximum value you are willing to pay
			share_value = fsearch(input);// then value of the demanded share is searched

			if (share_value > max_val)// if maximum willing value is less than the share value then display message
			{
				cout << "The Price of the share is more than you are willing to pay...." << endl;

			}
			else if ((num * share_value) > this->get_cash_balance_value())// if balance insufficient
			{
				cout << "Can not purchase these number of shares due to insufficient balance" << endl;


			}
			else
			{   // if all ok go ahead and insert the new node
				stock_prof.listing->insert(new node(input, num));
				account_balance -= (num * share_value);
				file_txn_add("Buy", input, num, share_value);
				update_stock_portfolio();
				flag = 1;
				cout << "You have purchased " << num <<" shares of " << input << " at $" << share_value << " each for a total of $" << (num * share_value) << endl;
			}
		}

		if (flag)
			return (num * share_value);
		else
			return 0;

	}

	// file searching as done in all the other parts of the project
	double StockAccount::fsearch(string searc)
	{
		vector<string> row;
		string line, word, temp;
		int flag = 0;

		

		fstream input_file1;

		if (rand() % 2)
			input_file1.open("Result_1.txt");
		else
			input_file1.open("Result_2.txt");



		if (!input_file1) {

			cout << "Unable to open file" << endl;

		}

		while (input_file1 >> temp) {

			row.clear();


			getline(input_file1, line);


			stringstream s(line);


			while (getline(s, word, '\t')) {

				row.push_back(word);


			}

			if (temp == searc)
			{
				flag = 1;
				break;
			}

		}
		input_file1.close();

		string str = row[1];
		char* end1;

		if (!flag)
		{

			return 0;
		}
		else
		{
			return strtod(str.c_str(), &end1);
		}
	}

	double StockAccount::debit(double y )//for selling of shares
	{
		string input;
		node* searc;
		int num_sell;
		double min_value;
		double x;
		int flag = 0;
		int check = 1;
		string discard;

		// mostly self explanatory following the problem statement
		cout << "Please enter the share you want to sell...." << endl;
		cin >> input;
		if (stock_prof.listing->search(input) == NULL)// if no node found
			cout << "You do not have this stock . Please retry....." << endl;
		else
		{   // asked for the number of shares want to sell
			//all this has been done to get the valid input as the cin return false when valid input is not given
			do {
				cout << "Please enter the amount of shares you want to sell" << endl;
				if (!(cin >> num_sell))
				{
					cout << endl << "Please enter the valid value...." << endl;
					cin.clear();
					cin >> discard;
				}
				else
				{
					check = 0;
				}
			} while (check == 1);

			check = 1;

			cin.seekg(0, ios::end);//clear the buffer 
			cin.clear();

			//get the address of the node carrying the stock and its numbers
			searc = stock_prof.listing->search(input);
			// if number of shares less than the what it wants to sell then prompt message to the customer or user
			if (searc->number_shares < num_sell)
			{
				cout << "You do not have the sufficient number of this stock . Please retry....." << endl;
			}
			else
			{  // Then minimum value conditions
				// to check the validity of the input as above
				do {
					cout << "Please enter the minimum value at which you want to sell this share...." << endl;
					if (!(cin >> min_value))
					{
						cout << endl << "Please enter the valid value...." << endl;
						cin.clear();
						cin >> discard;
					}
					else
					{
						check = 0;
					}
				} while (check == 1);

				check = 1;

				cin.seekg(0, ios::end);//same as above
				cin.clear();//same as above

				if ((x = fsearch(searc->stock_name)) >= min_value)
				{
					searc->number_shares -= num_sell;

					sst.m_impl->sort(stock_prof.listing);
					
					account_balance += (x * num_sell);

					//add transaction to the transaction file
					file_txn_add("Sell", input, num_sell, x);

					//update portfolio file
					update_stock_portfolio();

					if (searc->number_shares == 0)
						stock_prof.listing->delete_(searc);

					flag = 1;

					cout << "You have sold " << num_sell << " shares of " << input << " at $" << x << " each for a total of $" << (num_sell * x) << endl;
				}
				else
				{
					cout << "Sorry ... the value of share is less than your desired minimum value" << endl;
				}

			}

		}

		if (flag)
			return (x * num_sell);
		else
			return 0;

	}

	// display the total portfolio
	void StockAccount::display()
	{
		double total = 0;
		cout << "Cash Balance : $" << get_cash_balance_value() << endl<<endl;
		total=stock_prof.listing->display();
		cout << endl<<"Total Portfolio Value : $" << (total + get_cash_balance_value()) << endl;
	}
	
	// displaying the transaction history based on the file
	void StockAccount::trans_history()
	{
		fstream fin;
		vector<string> row;
		string line, word, temp;

		fin.open("stock_transactions.txt", ios::in);

		if (!fin) {

			cout << "No transactions yet....." << endl;

		}

		cout << setw(15) << "Event" << "\t" << setw(15) << "CompSymbol" << "\t" << setw(15) << "Number" << "\t" << setw(15) << "Pricepershare" << "\t" << setw(15) << "TotalValue" << "\t" << setw(20) << "Date Time" << endl;

		while (fin >> temp) {

			row.clear();


			getline(fin, line);


			stringstream s(line);


			while (getline(s, word, '\t')) {

				row.push_back(word);

			}

			cout << setw(15) << temp << "\t" << setw(15) << row[1] << "\t" << setw(15) << row[2] << "\t" << setw(15) << row[3] << "\t" << setw(15) << row[4] << "\t" << setw(15) << row[5] << "\t" << endl;

		}
		fin.close();
	}

