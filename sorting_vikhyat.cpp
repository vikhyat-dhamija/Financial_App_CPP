#include "sorting_.h"
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

double sortimpl::fsearch(string searc)
{
	vector<string> row;
	string line, word, temp;
	int flag = 0;

	//srand(time(0));

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




void sortbubble::sort(list* lst)
{
	int flag = 0, swapped = 0;

	if (lst->first == NULL || lst->first == lst->last)
		return;
	else
	{
		node* temp1 = lst->first;
		node* temp2 = lst->last;
		node* temp3 = NULL;

		do
		{
			swapped = 0;
			while (temp2->back != lst->last)
			{
				flag = 0;
				if ((temp2->number_shares * fsearch(temp2->stock_name)) > ((temp2->back)->number_shares * fsearch((temp2->back)->stock_name)))
				{
					flag = 1;
					swapped = 1;
					//Here interchange the two nodes temp2 and its back
					if (temp2 == lst->last && ((temp2->back) == lst->first))//case of two nodes in the doubly linked list
					{

						temp3 = temp2->back;
						temp2->forward = temp3;
						temp3->back = temp2;
						temp2->back = temp3;
						temp3->forward = temp2;

						lst->last = temp3;
						lst->first = temp2;


					}
					else if (temp2 == lst->last)//when the last node is swapped
					{


						temp3 = temp2->back;
						temp3->forward = temp2->forward;
						temp2->back = temp3->back;
						temp3->back = temp2;
						temp2->forward = temp3;
						temp2->back->forward = temp2;
						temp3->forward->back = temp3;
						lst->last = temp3;

					}
					else if (temp2->back == lst->first)//when the one of the swapping node is first
					{
						//cout << "2";
						temp3 = temp2->back;
						temp3->forward = temp2->forward;
						temp2->back = temp3->back;
						temp3->back = temp2;
						temp2->forward = temp3;
						temp2->back->forward = temp2;
						temp3->forward->back = temp3;
						lst->first = temp2;
						temp1 = lst->first;

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


			temp2 = lst->last;
		} while (swapped == 1);

	}

}




void sortselection::sort(list* lst)
{
}



sort_stat::sort_stat() { m_impl = new sortbubble(); }
void sort_stat::upGrade() { delete m_impl; m_impl = new sortselection(); }
void sort_stat::downGrade() { delete m_impl; m_impl = new sortbubble(); }