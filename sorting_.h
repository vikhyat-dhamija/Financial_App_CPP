#include<string>

// Here in one header file i have made all the class declarations in order to implement sorting behavorial strategy design pattern
using namespace std;

#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED

#include"doubly_linked_lst.h"
//sorting implementation class
class sortimpl
{
public:
	virtual void sort(list*) = 0;
	double fsearch(string);

}; 
//bubble sorting class
class sortbubble : public sortimpl {

public:
	void sort(list* lst);

};
//selection sorting class
class sortselection : public sortimpl {

public:
	void sort(list* lst);


};
//sorting strategy class
class sort_stat {

public:
	sortimpl* m_impl;
	sort_stat();
	void upGrade();
	void downGrade();


};

#endif
// Note that mostly the philosophy adopted is same as that taught in the class