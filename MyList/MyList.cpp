#include "stdafx.h"
#include "CircularList.h"
#include <iostream>
#include <string>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	double vList1[] = { 1.1, 2.2, 3.3 };
	double vList2[] = { 11.1, 22.2, 33.3 };
	clist <double> mylist1(vList1, 3);
	clist <double> mylist2(vList2, 3);

	cout << "MyList1:" << endl;
	mylist1.Print();
	cout << endl;
		
	cout << "MyList2:" << endl;
	mylist2.Print();
	cout << endl;

	mylist1.Merge(mylist2); // слияние списков 

	cout << "MyList1:" << endl;	// вывод итогового списка
	mylist1.Print();
	cout << endl;

	return 0;
}

