#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include "objective.h"
#include "Goal.h"

using namespace date_1;
namespace team3
{
	//constructor and deconstructor
	Goal::Goal()
	{
		string name = "";
		string Desc = "";
		int Cat = 0;
		int Pri = 0;
		double mTime = 0.0;
		date con;

		bool stat = true;

		description = Desc;

		priority = Pri;

		start = con;
		end = con;
		status = stat;

		used = 0;
		head = NULL;
		tail = NULL;
		link = NULL;
	}
	Goal::Goal(string oName, string Desc,
		int Pri, int startMonth,
		int startDay, int startYear, int endMonth,
		int endDay, int endYear, bool oStat)
	{

	}
	Goal::Goal(const Goal& source)
	{
		name = source.name;
		description = source.description;

		priority = source.priority;

		start = source.start;
		end = source.end;


		//clearObjectiveList(head);
		/*obj* cursor = source.head;
		obj entry;
		if (source.head != NULL)
		{
			entry = *source.head;
			entry.link = NULL;
			insertHeadObjective(entry);

			tail = head;

			for (; cursor != NULL; cursor = cursor->link)
			{
				entry = *cursor;
				insertTailObjective(entry);
			}
		}*/
		//if (head != NULL)
		//	clearObjectiveList(head);
		obj* cursor = source.head;
		obj test;
		if (source.head != NULL)
		{
			test = *source.head;
			test.link = NULL;
			insertHeadObjective(test);
		}
		tail = head;
		for (; cursor != NULL; cursor = cursor->link)
		{
			test = *cursor;
			insertTailObjective(test);
		}

	}
	Goal::~Goal()
	{

	}
	// Goalective
	void Goal::setName(string nGoal){
		name = nGoal;
	}
	string Goal::getName(){
		return name;
	}

	// description
	void Goal::setDescription(string nDesc){
		description = nDesc;
	}
	string Goal::getDescription(){
		return description;
	}




	//sets priority
	void Goal::setPriority(int nPrior){
		priority = nPrior;
	}
	int Goal::getPriority(){
		return priority;
	}


	// start date
	void Goal::setSdate(int month, int day, int year){
		start.setdate(month, day, year);
	}
	string Goal::getSdate(){
		string date = start.getdate();
		return date;
	}

	// end date
	void Goal::setEdate(int endMonth, int endDay, int endYear){
		end.setdate(endMonth, endDay, endYear);
	}
	string Goal::getEdate(){
		string date = end.getdate();
		return date;
	}

	// status
	void Goal::setStatus(bool stat){
		status = stat;
	}
	bool Goal::getStatus(){
		return status;
	}
	void Goal::display()
	{
		cout << "Goal: " << name << endl;
		cout << "Description:" << endl << description << endl;
		cout << left << setw(15) << "priority" << " " << setw(15) << "Start Date" << setw(15) << "End Date" <<
			setw(15) << "status" << endl;
		cout << left << setw(15) 
			<< priority << " " << setw(15) << start.getdate() << " " << setw(15) << end.getdate() << " ";
		/*for (int i = 0; i < used; i++)
		cout  << setw(10) << resources[i] << " ";*/

		if (status == true)
			cout << "true" << "\n";
		else
			cout << "false" << "\n";

		//                bool loop = true;
		obj* cursor = head;
		cout << "\n--------\nObjective(s)" << endl;
		if (cursor == NULL)
			cout << "No objectives" << endl;
		else
			for (; cursor != NULL; cursor = cursor->link)
			{
			cursor->display();
			if (cursor->link != NULL)
				cout << "\n-----------------------" << endl;
			}
		if (link != NULL)
		cout << "\n------------------------------------------------------------------------------------" << endl;
		//                while (loop == true)
		//                {
		//                    
		//                }
	}

	void Goal::write(ofstream& outFile)
	{
		outFile << name << " " << description << "|" << priority << " " << getSdate() << " " << getEdate() << " ";
		if (status == true)
			outFile << "true ";
		else
			outFile << "false ";
		obj* cursor = head;
		if (cursor == NULL)
		{
			outFile << "* ";
			return;
		}
		else
		{
			outFile << "| ";
			for (; cursor != NULL; cursor = cursor->link)
			{
				cursor->write(outFile);
				if (cursor->link != NULL)
					outFile << "+ ";
				else
					outFile << "* ";
			}

		}
	}

	void Goal::read(ifstream& inFile)
	{
		string month, day, year, st, pri;
		int m, d, y;
		getline(inFile, name, ' ');
		getline(inFile, description, '|');
		getline(inFile, pri, ' ');

		setPriority(stoi(pri));
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
		getline(inFile, st, ' ');
		if (st == "true")
			status = true;
		else
			status = false;
		getline(inFile, st, ' ');
		if (st == "*")
		{
			inFile.ignore(1);
			return;
		}
		else if (head != NULL)
			for (obj* cursor = head; cursor != NULL; cursor = cursor->link)
			{
			cursor->read(inFile);

			getline(inFile, st, ' ');
			if (st == "+")
			{
				cursor->link = new obj;
				tail = cursor->link;
			}
			else
				inFile.ignore(1);
			}
		else
		{
			head = new obj;
			//obj temp;
			//temp.read(inFile);
			//insertHeadObjective(temp);
			tail = head;
			for (obj* cursor = head; cursor != NULL; cursor = cursor->link)
			{

				//temp.read(inFile);
				//insertHeadObjective(temp);
				cursor->read(inFile);
				getline(inFile, st, ' ');
				if (st == "+")
				{
					cursor->link = new obj;
					tail = cursor->link;
				}
				else;
					//inFile.ignore(1);
			}
		}
		getline(inFile, st, ' ');
		if (st == "_")
		{
			inFile.ignore(100, EOF);
			return;
		}
	}

	void Goal::insertHeadObjective(obj entry)
	{
		obj* insertPtr = new obj;
		*insertPtr = entry;
		insertPtr->link = head;
		head = insertPtr;

	}
	void Goal::insertObjective(obj*& previousPtr, obj entry)
	{
		obj* insertPtr = new obj;
		*insertPtr = entry;
		insertPtr->link = previousPtr->link;
		previousPtr->link = insertPtr;

	}
	void Goal::insertTailObjective(obj entry)
	{
		obj* insertPtr = new obj;
		*insertPtr = entry;
		insertPtr->link = NULL;
		tail->link = insertPtr;


	}

	void Goal::deleteHeadObjective(obj*& headPtr)
	{
		obj *remove_ptr;

		remove_ptr = headPtr;
		headPtr = headPtr->link;
		delete remove_ptr;
	}
	void Goal::removeObjective(obj*& previousPtr)
	{
		obj *remove_ptr;

		remove_ptr = previousPtr->link;
		previousPtr->link = remove_ptr->link;
		delete remove_ptr;

	}
	void Goal::clearObjectiveList(obj*& headptr)
	{
		while (headptr != NULL)
			deleteHeadObjective(headptr);

	}

	size_t list_length(const Goal* head_ptr)

	{
		const Goal *cursor;
		size_t answer;

		answer = 0;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link)
			++answer;

		return answer;
	}

	void list_head_insert(Goal*& head_ptr, Goal& entry)
	{
		Goal* insert_ptr = new Goal;
		*insert_ptr = entry;
		insert_ptr->link = head_ptr;
		head_ptr = insert_ptr;
	}

	void list_insert(Goal* previous_ptr, Goal& entry)
	{
		Goal *insert_ptr = new Goal;

		*insert_ptr = entry,
			insert_ptr->link = previous_ptr->link;
		previous_ptr->link = insert_ptr;
	}
	void list_tail_insert(Goal*& tailptr, Goal& entry)
	{
		Goal* insert_ptr = new Goal;
		*insert_ptr = entry;
		tailptr->link = insert_ptr;
		insert_ptr->link = NULL;
		tailptr = insert_ptr;
	}

	Goal* list_search(Goal* head_ptr, Goal& target)
		// Library facilities used: cstdlib
	{
		Goal *cursor;

		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link)
			if (target.getName() == cursor->getName())
				return cursor;
		return NULL;
	}



	Goal* list_locate(Goal* head_ptr, size_t position)

	{
		Goal *cursor;
		size_t i;

		assert(0 < position);
		cursor = head_ptr;
		for (i = 1; (i < position) && (cursor != NULL); i++)
			cursor = cursor->link;
		return cursor;
	}

	const Goal* list_locate(const Goal* head_ptr, size_t position)

	{
		const Goal *cursor;
		size_t i;

		assert(0 < position);
		cursor = head_ptr;
		for (i = 1; (i < position) && (cursor != NULL); i++)
			cursor = cursor->link;
		return cursor;
	}

	void list_head_remove(Goal*& head_ptr)
	{
		Goal *remove_ptr;

		remove_ptr = head_ptr;
		head_ptr = head_ptr->link;
		delete remove_ptr;
	}

	void list_remove(Goal* previous_ptr)
	{
		Goal *remove_ptr;

		remove_ptr = previous_ptr->link;
		previous_ptr->link = remove_ptr->link;
		delete remove_ptr;
	}

	void list_clear(Goal*& head_ptr)

	{
		while (head_ptr != NULL)
			list_head_remove(head_ptr);
	}

}