#ifndef DATE_H
#define DATE_H
#include <string>

using namespace std;
namespace date_1
{
	class date
	{
	private:
		int month;
		int day;
		int year;
                
	public:
		date();
		//date(int = 7, int = 4, int = 94);  // constructor
		void setdate(int, int, int); // member function to assign a date
		string getdate();            // member function to display a date
	};
}
#endif
