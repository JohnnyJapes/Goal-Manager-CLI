#ifndef GOAL_H
#define GOAL_H

#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include "Date.h"
#include "objective.h"
using namespace std;
using namespace date_1;

namespace team3
{
	class Goal
	{
	public:
		typedef std::size_t size_type;
		//constructor and deconstructor
		Goal();
		Goal(string oName, string Desc,
			int Pri, int startMonth,
			int startDay, int startYear, int endMonth,
			int endDay, int endYear, bool oStat);
		Goal(const Goal& source);
		~Goal();
		//member functions
		//Name
		void setName(string nName);
		string getName();

		// description
		void setDescription(string nDesc);
		string getDescription();


		//sets priority
		void setPriority(int nPrior);
		int getPriority();

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


		void createObjective();
		void insertObjective(obj*& previousPtr, obj entry);
		void insertTailObjective(obj entry);
		void insertHeadObjective(obj entry);
		void deleteHeadObjective(obj*& headPtr);
		void removeObjective(obj*& previousPtr);
		void clearObjectiveList(obj*& headptr);

		obj* head;
		obj* tail;


		Goal* link;

		Goal operator = (Goal*& entry)
		{

			this->setName(entry->getName());
			this->setDescription(entry->getDescription());
			this->setPriority(entry->getPriority());
			this->start = entry->start;
			this->end = entry->end;
			this->setStatus(entry->getStatus());
			
			this->link = entry->link;
			return *this;
		}
		Goal operator = (Goal& entry)
		{

			this->setName(entry.getName());
			this->setDescription(entry.getDescription());
			this->setPriority(entry.getPriority());
			
			this->start = entry.start;
			this->end = entry.end;
			this->setStatus(entry.getStatus());
			

			this->head = entry.head;
			this->tail = entry.tail;

			/*if (head != NULL)
				clearObjectiveList(head);
			obj* cursor = entry.head;
			obj test;
			if (entry.head != NULL)
			{
				test = *entry.head;
				test.link = NULL;
				insertHeadObjective(test);
			}
			tail = this->head;
			for (; cursor != NULL; cursor = cursor->link)
			{
				test = *cursor;
				insertHeadObjective(test);
			}*/
			this->link = entry.link;
			return *this;
		}

		int used;

		

	private:
		string name, description;
		
		int priority;
		date start;
		date end;
		

		
		bool status;

	};

	std::size_t list_length(const Goal* head_ptr);
	void list_head_insert(Goal*& headptr, Goal& entry);
	void list_insert(Goal* previous_ptr, Goal& entry);
	void list_tail_insert(Goal*& tailptr, Goal& entry);
	Goal* list_search(Goal* head_ptr, const Goal& target);
	const Goal* list_search(const Goal* head_ptr, const Goal& target);
	Goal* list_locate(Goal* head_ptr, std::size_t position);
	const Goal* list_locate(const Goal* head_ptr, std::size_t position);
	void list_head_remove(Goal*& head_ptr);
	
	void list_remove(Goal* previous_ptr);
	void list_clear(Goal*& head_ptr);
	void list_copy(const Goal* source_ptr, Goal*& head_ptr, Goal*& tail_ptr);
	Goal* list_merge(Goal* head_ptr1, Goal* head_ptr2);

}


#endif
