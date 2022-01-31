#ifndef TASK_H
#define TASK_H

#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include "Date.h"
using namespace std;
using namespace date_1;

namespace team3
{
	class Task
	{
	public:
		typedef std::size_t size_type;
		//constructor and deconstructor
		Task();
		Task(string oName, string Desc, int Cat,
			int Pri, double mTime, int startMonth,
			int startDay, int startYear, int endMonth,
			int endDay, int endYear, bool oStat);
		Task(const Task& source);
		~Task();
		//member functions
		// objective
		void setName(string nName);
		string getName();

		// description
		void setDescription(string nDesc);
		string getDescription();


		// time(military)
		void setTime(double nTime);
		double getTime();

		// start date
		void setSdate(int, int, int);
		string getSdate();

		// end date
		void setEdate(int, int, int);
		string getEdate();

		// status
		void setStatus(bool);
		bool getStatus();


		void write(ofstream&);
		void read(ifstream&);
		void display();

		void insertResource(string entry);
		void reserve(size_type new_capacity);
		bool erase_one(const string target);
		void erase(const string target);

		
                Task* link;

				Task operator = (Task*& entry)
				{
					
					this->setName(entry->getName());
					this->setDescription(entry->getDescription());
					this->setTime(entry->getTime());
					/*string out;
					out = entry.getSdate();
					int i = out.find("/", 0);
					string temp = out.substr(0, i);
					int tempz = temp;
					out.erase(0, i + 1);
					i = out.find("/", 0);
					string temp2 = out.substr(0, i);
					out.erase(0, i + 1);*/

					this->start = entry->start;
					this->end = entry->end;
					this->setStatus(entry->getStatus());
					string *larger_array;
					size_t new_capacity = entry->capacity;
					//if (new_capacity == capacity)
					//	return; // The allocated memory is already the right size.

					//if (new_capacity < used)
					//	new_capacity = used; // Cant allocate less than we are using.

					larger_array = new string[new_capacity];
					//stdext::checked_array_iterator<string *> chkd_test_array(larger_array, new_capacity);
					copy(entry->resources, entry->resources + entry->used, larger_array);
					delete[] resources;
					this->resources = larger_array;
					this->capacity = new_capacity;
					this->link = entry->link;
					return *this;
				}
				Task operator = (Task& entry)
				{

					this->setName(entry.getName());
					this->setDescription(entry.getDescription());
					this->setTime(entry.getTime());
					/*string out;
					out = entry.getSdate();
					int i = out.find("/", 0);
					string temp = out.substr(0, i);
					int tempz = temp;
					out.erase(0, i + 1);
					i = out.find("/", 0);
					string temp2 = out.substr(0, i);
					out.erase(0, i + 1);*/

					this->start = entry.start;
					this->end = entry.end;
					this->setStatus(entry.getStatus());
					string *larger_array;
					size_t new_capacity = entry.capacity;
					//if (new_capacity == capacity)
					//	return; // The allocated memory is already the right size.

					//if (new_capacity < used)
					//	new_capacity = used; // Cant allocate less than we are using.

					larger_array = new string[new_capacity];
					//stdext::checked_array_iterator<string *> chkd_test_array(larger_array, new_capacity);
					copy(entry.resources, entry.resources + entry.used, larger_array);
					delete[] resources;
					this->resources = larger_array;
					this->capacity = new_capacity;
					this->link = entry.link;
					return *this;
				}



				//}

	private:
		string name, description;
		double time;
		date start;
                date end;
		string *resources;
		size_type capacity;
                
		size_type used;
		bool status;
		
	};



}


#endif
