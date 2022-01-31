#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include "Task.h"

using namespace date_1;
namespace team3
{
	//constructor and deconstructor
	Task::Task()
	{
		string namez = "stop";
		string Desc = "";
		int Cat = 0;
		int Pri = 0;
		double mTime = 0.0;
		date con;

		bool stat = true;
		name = namez;
		description = Desc;
		time = mTime;
		start = con;
		end = con;
		status = stat;
		size_t initial_capacity = 10;
		resources = new string[initial_capacity];
		capacity = initial_capacity;
		used = 0;
		link = NULL;
	}
	Task::Task(string oName, string Desc, int Cat,
		int Pri, double mTime, int startMonth,
		int startDay, int startYear, int endMonth,
		int endDay, int endYear, bool oStat)
	{

	}
	Task::Task(const Task& source)
	{
		name = source.name;
		description = source.description;
		time = source.time;
		start = source.start;
		end = source.end;

		string *larger_array;
		//size_t new_capacity = source.capacity;
		//if (new_capacity == capacity)
		//	return; // The allocated memory is already the right size.

		//if (new_capacity < source.used)
		//	new_capacity = source.used; // Cant allocate less than we are using.

		larger_array = new string[source.capacity];
		//stdext::checked_array_iterator<string *> chkd_test_array(larger_array, new_capacity);
		copy(source.resources, source.resources + source.used, larger_array);
		/*if (this->used == 0)
		{
		insertResource("test");
		delete[] resources;

		}
		else
		delete[] resources;*/
		resources = larger_array;
		capacity = source.capacity;
		used = source.used;
	}
	Task::~Task()
	{
		delete[] resources;
	}
	// name
	void Task::setName(string nName){
		name = nName;
	}
	string Task::getName(){
		return name;
	}

	// description
	void Task::setDescription(string nDesc){
		description = nDesc;
	}
	string Task::getDescription(){
		return description;
	}



	// time(military)
	void Task::setTime(double nTime){
		time = nTime;
	}
	double Task::getTime(){
		return time;
	}

	// start date
	void Task::setSdate(int month, int day, int year){
		start.setdate(month, day, year);
	}
	string Task::getSdate(){
		string date = start.getdate();
		return date;
	}

	// end date
	void Task::setEdate(int endMonth, int endDay, int endYear){
		end.setdate(endMonth, endDay, endYear);
	}
	string Task::getEdate(){
		string date = end.getdate();
		return date;
	}

	// status
	void Task::setStatus(bool stat){
		status = stat;
	}
	bool Task::getStatus(){
		return status;
	}

	// write
	void Task::write(ofstream& outFile)
	{
		outFile << name << " " << description << "|" << time << " " << getSdate() << " " << getEdate() << " ";
		for (int i = 0; i < used; i++)
			outFile << resources[i] << " ";
		outFile << "| ";
		if (status == true)
			outFile << "true ";
		else
			outFile << "false ";

	}
	//read
	void Task::read(ifstream& inFile)
	{
		string month, day, year, st, ti;
		int m, d, y;
		double t;
		getline(inFile, name, ' ');
		getline(inFile, description, '|');
		
		

		getline(inFile, ti, ' ');
		time = stod(ti);

		getline(inFile, month, '/');
		getline(inFile, day, '/');
		getline(inFile, year, ' ');
		m = stoi(month);
		d = stoi(day);
		y = stoi(year);
		setSdate(m, d, y);
		getline(inFile, month, '/');
		getline(inFile, day, '/');
		getline(inFile, year, ' ');
		m = stoi(month);
		d = stoi(day);
		y = stoi(year);
		setEdate(m, d, y);
		int i = 0;
		for (bool loop = true; loop != false; i++)
		{
			getline(inFile, st, ' ');
			if (st == "|")
				loop = false;
			else
			{
				insertResource(st);
			}
		}

		getline(inFile, st, ' ');
		if (st == "true")
			status = true;
		else
			status = false;
	}

	// display
	void Task::display()
	{
		cout << "Name: " << name << endl;
		cout << "Description:" << endl << description << endl;
		cout << left << setw(15) << "time" << " " << setw(15) << "Start Date" << setw(15) << "End Date" <<
			setw(15) << "status" << endl;
		cout << left << setw(15) << time << " " << setw(15) << start.getdate() << " " << setw(15) << end.getdate() << " ";
		/*for (int i = 0; i < used; i++)
			cout  << setw(10) << resources[i] << " ";*/

		if (status == true)
			cout << "true" << "\n";
		else
			cout << "false" << "\n";
		cout << "Resources:" << endl;
		for (int i = 0; i < used; i++)
			cout << resources[i] << " ";
	}

	// resources

	void Task::reserve(size_type new_capacity)
	{
		string *larger_array;

		if (new_capacity == capacity)
			return; // The allocated memory is already the right size.

		if (new_capacity < used)
			new_capacity = used; // Cant allocate less than we are using.

		larger_array = new string[new_capacity];
		//stdext::checked_array_iterator<string *> chkd_test_array(larger_array, new_capacity);
		copy(resources, resources + used, larger_array);
		cout << "d" << endl;
		delete[] resources;
		resources = larger_array;
		capacity = new_capacity;

	}
	//obj* obj::getLink(){
	//	return link;
	//}
	void Task::insertResource(string entry)
	{
		if (used == capacity)
			reserve(used + 1);
		resources[used] = entry;
		++used;
	}

	bool Task::erase_one(const string target)
	{
		size_type index; // The location of target in the data array    

		// First, set index to the location of target in the data array,
		// which could be as small as 0 or as large as used-1.
		// If target is not in the array, then index will be set equal to used.
		index = 0;
		for (; (index < used) && (resources[index] != target);)
			++index;

		if (index == used) // target isn't in the bag, so no work to do
			return false;

		// When execution reaches here, target is in the bag at data[index].
		// So, reduce used by 1 and copy the last item onto data[index].
		--used;
		resources[index] = resources[used];
		return true;

	}
	void Task::erase(const string target)
	{

	}
}