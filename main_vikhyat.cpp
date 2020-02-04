#include"account.h"
#include"bankaccount.h"
#include"doubly_linked_lst.h"
#include"list.h"
#include"node.h"
#include"portfolio.h"
#include"stock_account.h"


#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif

#define HISTORY 5

#include <engine.h>

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
#include "mex.h"

using namespace std;

// Note above are all the header files required by the program to run

int main()
{    // Matlab engine pointer
	Engine* ep;
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		cout << "Error in connecting with MATLAB engine" << endl;

	}
	int check = 1;
	srand(time(0)); // setting the srand for the current run of the program this leads to fresh pseudorandom sequence for current run

	//Graph Variables
	//Value of the variable to be plotted needs an array which will be transformed into the array understood by matlab for plotting
	double* total_val = new double[HISTORY];
	for (int t = 0; t < HISTORY; t++)
	{
		total_val[t] = 0;
		
	}
	fstream f;
	double x, y;
	string s;
	int i = 0;
	int correct1 = 1;
	int correct2 = 1;
	//Above are variables required
	//Graph File variables
	vector<string> row;
	string line, word, temp;
	vector<double> graph;
	string str;
	char* end1, * end2;

	//Major Program Variables
	BankAccount bac;//bank account instance
	StockAccount sac(new doubly_linked_list());
	//Stock account instance with the list type of doubly_linked_list used

	int input;
	string searc;
	int flag1 = 0;
	double success;
	int k = 0;
	string discard;
	string inp;
	//above are the variables used by the program

	do
	{
		cout << endl << "Welcome to the Account Management System." << endl;
		cout << endl << "Please select an account to access:" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		
		//Check the input validity i.e within range and whether number is there or not
		do
		{
			cin >> inp;
			if (isdigit(inp[0]))
			{
				input = inp[0] - 48;
				if (input <= 0 || input > 3)
					cout << endl << "Please enter the correct option" << endl;
				else
					correct1 = 0;
			}
			else
				cout << endl << "Please enter the correct option" << endl;
		} while (correct1 == 1);

		correct1 = 1;

		switch (input)
		{

		case 1:
			do
			{

				cout << endl << "Welcome to the Stock portfolio system" << endl << endl;
				cout << "1.Search for the stock value " << endl;
				cout << "2.Buy Shares " << endl;
				cout << "3.Display the Current Portfolio " << endl;
				cout << "4.Sell Shares " << endl;
				cout << "5.View the Transaction History " << endl;
				cout << "6.View a graph for the portfolio value" << endl;
				cout << "7.Return to previous menu " << endl;

				//Check the input validity i.e within range and whether number is there or not
				do
				{
					cin >> inp;
					if (isdigit(inp[0]))
					{
						input = inp[0] - 48;
						if (input <= 0 || input > 7)
							cout << endl << "Please enter the correct option" << endl;
						else
							correct1 = 0;
					}
					else
						cout << endl << "Please enter the correct option" << endl;

				} while (correct1 == 1);

				correct1 = 1;

				switch (input)
				{

				//for seraching the Stock ticker value
				case 1:
					cout << "Enter stock name to search for (in Caps) : ";
					cin >> searc;
					if (!(sac.fsearch(searc)))
						cout << "Stock Name you entered is not there............" << endl;
					else
						cout << "The price of the " << searc << " is : " << "$ " << sac.fsearch(searc) << endl;
					break;

				case 2:
					if (success = sac.credit())
					{
						bac.debit(success);

					}
					break;
                  // sac credit return the value of the transaction and the amount is debited from the bank account
				case 3:
					
					sac.display();
					
					break;
					//display of the portfolio

				case 4:
					if (success = sac.debit())
					{
						bac.credit(success);

					}
					break;
					//sac debit return the value of the transaction and the amount is credited to the bank account

				case 5:
					sac.trans_history();
					break;
					// Display the transaction history

				case 6:

					//Graphing for which the portfolio file is opened and then the rows are read
					f.open("total_portfolio.txt", ios::in);

					while (f >> temp) {

						row.clear();


						getline(f, line);


						stringstream s(line);


						while (getline(s, word, '\t')) {

							row.push_back(word);

						}

						str = row[1];

						graph.push_back(strtod(temp.c_str(), &end2) + strtod(str.c_str(), &end1));

						//graph named vector is filled with the values
					}

					// In reverse we fill the HISTORY macro suggested number of enteries from the end i.e. from latest timestamed to earlier ones

					for (auto ir = graph.rbegin(); (ir != graph.rend()) && (k < HISTORY); ++ir, k++)
						total_val[HISTORY-1- k] = *ir;
					k = 0;
					f.close();

					//Then the matlab variable of 1 row of values is created out of the double array
					mxArray* m_X;
					m_X = mxCreateDoubleMatrix(1, HISTORY, mxREAL);
					memcpy((void*)mxGetPr(m_X), (void*)total_val, sizeof(double) * HISTORY);
					engPutVariable(ep, "total_val", m_X);

					

					engEvalString(ep, "x = 1:1:5;");// Then x axis length is being taken constant for five values but can be increased or decreased changing the 5
					
					//Bar shaped graph is shown to showcase the change in the total portfolio value
					engEvalString(ep, "b=bar(x, total_val);");
					engEvalString(ep, "xtips1 = b.XEndPoints;");
					engEvalString(ep, "ytips1 = b.YEndPoints;");
					engEvalString(ep, "labels1 = string(b.YData);");
					engEvalString(ep, "text(xtips1,ytips1,labels1,'HorizontalAlignment','center','VerticalAlignment', 'bottom')");
					break;

				case 7:

					break;
				}
			} while (input != 7);

			break;

		case 2:

			do {
				cout << endl;
				cout << "1. View account balance" << endl;
				cout << "2. Deposit money" << endl;
				cout << "3. Withdraw money" << endl;
				cout << "4. Print out history" << endl;
				cout << "5. Return to previous menu" << endl;

				do
				{
					//To check the validity of the input
					cin >> inp;
					if (isdigit(inp[0]))
					{
						input = inp[0] - 48;

						if (input <= 0 || input > 5)
							cout << endl << "Please enter the correct option" << endl;
						else
							correct2 = 0;
					}
					else
						cout << endl << "Please enter the correct option" << endl;

				} while (correct2 == 1);

				correct2 = 1;

				switch (input)
				{
				case 1:
					bac.display_balance();
					break;

				case 2:
					double value;
					// check the validity of the input and then the respective task
					do {
						cout << endl << "Enter the amount to be deposited" << endl;
						if (cin >> value)
						{
							if (value < 0)
								cout << endl << "Please enter the valid value" << endl;
							bac.credit(value);
							check = 0;
						}
						else {
							cout << "Please enter the valid value...." << endl;
							cin.clear();
							cin >> discard;
						}
					} while (check == 1);
					check = 1;
					break;

				case 3:
					double value1;
					//check the validity of the input and then the respective task
					do {
						cout << endl << "Enter the amount to be withdrawn" << endl;
						if (cin >> value1)
						{
							if (value1 < 0)
								cout << endl << "Please enter the valid value" << endl;
							bac.debit(value1);
							check = 0;
						}
						else {
							cout << "Please enter the valid value...." << endl;
							cin.clear();
							cin >> discard;
						}
					} while (check == 1);
					check = 1;
					break;
				case 4:
					bac.display_transactions_history();
					break;
				case 5:
					sac.update_balance_value(bac.get_cash_balance_value());//synchronisation on exit from the current menu
					break;
				}

			} while (input != 5);

			break;

		case 3:
			flag1 = 1;
			
		}
	} while (!flag1);
}
