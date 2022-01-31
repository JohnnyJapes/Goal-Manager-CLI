#include<iostream>
#include <cstdlib>
#include <string>
#include "date.h"
using namespace std;


namespace date_1
{
	date::date()
	{
		month = 5;
		day = 6;
		year = 1935;
	}
	//date::date(int mm, int dd, int yy)
	//{
	//	month = mm;
	//	day = dd;
	//	year = yy;
	//}
	void date::setdate(int mm, int dd, int yy)
	{
		//precondition: Values passed for month, day and year must be of type integer
		//postcondition: The date has been set
		month = mm;
		day = dd;
		year = yy;
	}
	string date::getdate()
	{
            string out;
			out = to_string(month) + "/" + to_string(day);
			out+= "/" + to_string(year);
			//cout << "tst" << endl;	//debug text
            return(out);
	}
}