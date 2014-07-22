#include "stdafx.h"
#include "CircularList.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	clist <int> mylist1;
	mylist1.Insert(3);
	mylist1.Insert(5);
	mylist1.Insert(2);
	mylist1.Insert(4);
	mylist1.Insert(1);
	mylist1.Insert(2);

	clist <int> mylist2;
	mylist2.Insert(30);
	mylist2.Insert(50);
	mylist2.Insert(20);
	mylist2.Insert(40);
	mylist2.Insert(10);
	mylist2.Insert(20);

	cout << "MyList1:" << endl;
	mylist1.Print();
	cout << endl;

	cout << "MyList2:" << endl;
	mylist2.Print();
	cout << endl;

	mylist1.Insert(mylist2); // слияние списков 
	mylist1.Sort();			// сортировка итогового списка по убыванию

	cout << "MyList1:" << endl;	// вывод итогового списка
	mylist1.Print();

	return 0;
}

