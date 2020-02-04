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
#include<vector>
#include "doubly_linked_lst.h"




	doubly_linked_list::doubly_linked_list()//constructor
	{
		first = NULL;
		last = NULL;
	}

	double doubly_linked_list::fsearch(string searc)//file search for searching the stock value inputting the stock name
	{
		vector<string> row;
		string line, word, temp;
		int flag = 0;

		
		// based on the random value one of the file is opened and then the value is taken out of it
		fstream input_file1;

		if (rand() % 2)
			input_file1.open("Result_1.txt");
		else
			input_file1.open("Result_2.txt");

		if (!input_file1) {

			cout << "Unable to open file" << endl;

		}
		// The purpose of the above is to check is there is something left for us to get
		while (input_file1 >> temp) {

			row.clear();//vector is cleared


			getline(input_file1, line);//line is taken from the file


			stringstream s(line);//string stream is like a buffer 


			while (getline(s, word, '\t')) {

				row.push_back(word);// here every word separated by tab is put into the row vector


			}

			if (temp == searc)// and when the search key is found then flagging that event break
			{
				flag = 1;
				break;
			}

		}
		input_file1.close();

		string str = row[1];
		char* end1;

		if (!flag)//if not found
		{

			return 0;
		}
		else
		{
			return strtod(str.c_str(), &end1);//else return the value
		}
	}

	void doubly_linked_list::insert(node* temp)
	{

		node* temp1 = first;
		node* temp2 = NULL;
		node* temp3 = NULL;
		int flag = 0;

		if (first == NULL)//first if the list is empty
		{
			first = temp;
			last = temp;
			temp->forward = temp; // insert in the list and change the first and last
			temp->back = temp;
		}
		else if (doubly_linked_list::search(temp->stock_name))
		{
			doubly_linked_list::search(temp->stock_name)->number_shares += temp->number_shares;//if there is alreday the node with stock name then just add the value

		}
		else
		{   // when not the above case search node where to insert because descending order
			while (temp2 != first)
			{
				if ((temp1->number_shares * fsearch(temp1->stock_name)) < (temp->number_shares * fsearch(temp->stock_name)))
				{
					flag = 1;
					break;
				}
				temp2 = temp1->forward;
				temp1 = temp1->forward;
			}

			if (flag)//behind temp1
			{
				if (temp1 == first)//when the new node has to be inserted behind the first node only
				{

					temp->forward = temp1;
					temp->back = temp1->back;
					temp1->back = temp;
					first = temp;
					last->forward = first;

				}
				else//else case where to be inserted
				{
					temp3 = temp1->back;
					temp3->forward = temp;
					temp->back = temp3;
					temp->forward = temp1;
					temp1->back = temp;

				}

			}
			else//at last when to be inserted
			{

				last->forward = temp;
				temp->back = last;
				temp->forward = first;
				last = temp;
				first->back = last;
			}



		}

		doubly_linked_list::sort(); // sort after the list mostly sorted because of our insertion style
	}



	void doubly_linked_list::sort()
	{

		int flag = 0, swapped = 0;

		if (first == NULL || first == last)
			return;
		else
		{
			node* temp1 = first;
			node* temp2 = last;
			node* temp3 = NULL;

			do// this loop outer is to check when there is no swap
			{
				swapped = 0;
				while (temp2->back != last)//we are starting from back side of the list and checking whether its back is last
				{
					flag = 0;
					if ((temp2->number_shares * fsearch(temp2->stock_name)) > ((temp2->back)->number_shares * fsearch((temp2->back)->stock_name)))
					{
						flag = 1;
						swapped = 1;
						//Here interchange the two nodes temp2 and its back
						if (temp2 == last && ((temp2->back) == first))//case of two nodes in the doubly linked list
						{

							temp3 = temp2->back;
							temp2->forward = temp3;
							temp3->back = temp2;
							temp2->back = temp3;
							temp3->forward = temp2;

							last = temp3;
							first = temp2;


						}
						else if (temp2 == last)//when the last node is swapped
						{


							temp3 = temp2->back;
							temp3->forward = temp2->forward;
							temp2->back = temp3->back;
							temp3->back = temp2;
							temp2->forward = temp3;
							temp2->back->forward = temp2;
							temp3->forward->back = temp3;
							last = temp3;

						}
						else if (temp2->back == first)//when the one of the swapping node is first
						{
							//cout << "2";
							temp3 = temp2->back;
							temp3->forward = temp2->forward;
							temp2->back = temp3->back;
							temp3->back = temp2;
							temp2->forward = temp3;
							temp2->back->forward = temp2;
							temp3->forward->back = temp3;
							first = temp2;
							temp1 = first;

						}
						else//when two nodes swapped will not have any effect on the first and the last pointer
						{
							temp3 = temp2->back;
							temp3->forward = temp2->forward;
							temp2->back = temp3->back;
							temp3->back = temp2;
							temp2->forward = temp3;
							temp2->back->forward = temp2;
							temp3->forward->back = temp3;

						}

					}

					if (flag != 1)
						temp2 = temp2->back;




				}


				temp2 = last;
			} while (swapped == 1);

		}



	}



	double doubly_linked_list::display()
	{
		//normal traversal to display all the stocks in the list
		node* temp1 = first;
		node* temp2 = NULL;
		int i = 1;
		double value=0;
		double total_value = 0;
		if (first == NULL)
		{
			cout << "No stocks in Stocks Portfolio" << endl;
		}
		else
		{
			
			cout << setw(15) << "Company Symbol" << setw(15) << "Number"<< setw(15) << "PriceperShare" << setw(15) << "Total Value" << endl;
			while (temp2 != first)
			{
				cout << setw(15) << temp1->stock_name << setw(15) << temp1->number_shares << setw(15) << (value = fsearch(temp1->stock_name) )<< setw(15) << ((temp1->number_shares) * value)<<endl;
				total_value += ((temp1->number_shares) * value);
				temp2 = temp1->forward;
				temp1 = temp1->forward;
				
				
			}

		}
		return total_value;
	}

	void doubly_linked_list::file_add(fstream& fout)
	{

		node* temp1 = first;
		node* temp2 = NULL;

		//just add the all the stocks with the number in the file
		if (first == NULL)
		{

		}
		else
		{

			while (temp2 != first)
			{
				fout << setw(15) << temp1->stock_name << "\t" << setw(15) << temp1->number_shares << endl;

				temp2 = temp1->forward;
				temp1 = temp1->forward;


			}

		}
	}


	node* doubly_linked_list::search(string stock_name) //search by the stock name and send the number of the node containing that stock
	{
		//Traversal and search and when the node with particular value is find just return the node address
		node* temp1 = first;
		node* temp2 = NULL;
		int flag = 0;

		if (first == NULL)
		{
			return NULL;
		}
		else
		{
			while (temp2 != first)
			{
				if (temp1->stock_name == stock_name)
				{
					flag = 1;
					break;

				}
				temp2 = temp1->forward;
				temp1 = temp1->forward;
			}

			if (flag)
				return temp1;
			else
				return NULL;

		}


	}
	//delete the node with particular address
	void doubly_linked_list::delete_(node* x)
	{
		if (x == first && x == last)//when first and only node to deleted
		{
			first = NULL;
			last = NULL;
		}
		else if (x == last)//if last then 
		{

			(x->back)->forward = x->forward;
			(x->forward)->back = x->back;
			last = x->back;
		}
		else if (x == first)//if first then
		{
			(x->back)->forward = x->forward;
			(x->forward)->back = x->back;
			first = x->forward;
		}
		else//else cases
		{
			(x->back)->forward = x->forward;
			(x->forward)->back = x->back;
		}

		delete x;//delete the node after the adjustment
	}

	double  doubly_linked_list::total()// this function is to calculate the total value 
	{ // This function is specific to our needs in this project but still i made it part because reduce functions are popular to generate a value out of all nodes
		node* temp1 = first;
		node* temp2 = NULL;
		double sum = 0;

		if (first == NULL)
		{
			return 0;
		}
		else
		{

			while (temp2 != first)
			{
				sum += temp1->number_shares * fsearch(temp1->stock_name);
				temp2 = temp1->forward;
				temp1 = temp1->forward;


			}

		}

		return sum;

	}

	doubly_linked_list::~doubly_linked_list()
	{
		node* temp = last;
		node* temp2 = NULL;

		if (first == NULL)// when list is empty
			return;
		else if (first == last)// when only one node which is deleted
			delete first;
		else
		{   // else delete all the nodes going from the last to back
			while (temp2 != first)
			{
				temp2 = temp->back;
				delete temp;
			}
			//delete temp2 as it contains the first node address
			delete temp2;
		}
	
	}


