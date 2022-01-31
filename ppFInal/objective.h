
//   void reserve(size_type new_capacity)
//     Postcondition: The bag's current capacity is changed to the
//     new_capacity (but not less than the number of items already in the
//     bag). The insert function will work efficiently (without allocating
//     new memory) until the new capacity is reached.
//
//   size_type erase(const string target);
//     Postcondition: All copies of target have been removed from the bag.
//     The return value is the number of copies removed (which could be zero).
//
//   void erase_one(const string target)
//     Postcondition: If target was in the bag, then one copy has been removed;
//     otherwise the bag is unchanged. A true return value indicates that one
//     copy was removed; false indicates that nothing was removed.
//
//   void insertResource(string entry);
//     Postcondition: A new copy of entry has been inserted into the bag(resource).
//
//   
#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include <iomanip>
#include <string>
#include <cstdlib>
#include "Date.h"
#include "Task.h"
using namespace date_1;
namespace team3
{
	using namespace std;
	class obj
	{
	public:
		typedef std::size_t size_type;
		//constructor and deconstructor
		obj();
		obj(string oName, string Desc, int Cat,
			int Pri, double mTime, int startMonth,
			int startDay, int startYear, int endMonth,
			int endDay, int endYear);
		obj(const obj& source);
		~obj();
		//member functions
		// objective
		void setObj(string nObj);
		string getObj();

		// description
		void setDescription(string nDesc);
		string getDescription();

		// category
		void setCategory(int nCate);
		int getCategory();

		//sets priority
		void setPriority(int nPrior);
		int getPriority();

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
        obj* link;
                
        //Task - Linked list functions
        void createTask();
        void insertTask(Task*& previousPtr, Task entry);
		void insertTailTask(Task entry);
        void insertHeadTask(Task entry);
        void deleteHeadTask(Task*& headPtr);
		void removeTask(Task*& previousPtr);
		void clearTaskList(Task*& headptr);
        Task* listSearch(Task* headPtr, Task& target);
        // const list_search(const Task* headPtr, const Task& target);
        Task* listLocate(Task* headPtr, std::size_t position);
        // const list_locate(const Task* headPtr, std::size_t position);
        void listRemove(Task*& previousPtr);
        Task* head;
		Task* tail;
		
		obj operator= (obj& entry)
		{
			this->setObj(entry.getObj());
			this->setDescription(entry.getDescription());
			this->setCategory(entry.getCategory());
			this->setPriority(entry.getPriority());
			this->setTime(entry.getTime());
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
			resources = larger_array;
			capacity = new_capacity;
			//clearTaskList(this->head);
			//this->head = entry.head;
			this->used = entry.used;
			head = entry.head;
			tail = entry.tail;
			link = entry.link;
			/*if (head != NULL)
				clearTaskList(head);
			Task* cursor = entry.head;
			Task test;
			if (entry.head != NULL)
			{
				test = *entry.head;
				test.link = NULL;
				insertHeadTask(test);
			}
			tail = this->head;
			for (; cursor != NULL; cursor = cursor->link)
			{
				test = *cursor;
				insertTailTask(test);
			}*/
			return *this;

		}

		obj operator= (obj*& entry)
		{
			this->setObj(entry->getObj());
			this->setDescription(entry->getDescription());
			this->setCategory(entry->getCategory());
			this->setPriority(entry->getPriority());
			this->setTime(entry->getTime());
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
			resources = larger_array;
			capacity = new_capacity;
			//clearTaskList(this->head);
			//this->head = entry->head;
			this->used = entry->used;
			head = entry->head;
			tail = entry->tail;
			link = entry->link;
			/*if (head != NULL)
				clearTaskList(head);
			Task* cursor = entry->head;
			Task test;
			if (entry->head != NULL)
			{
				test = *entry->head;
				test.link = NULL;
				insertHeadTask(test);
			}
			tail = this->head;
			for (; cursor != NULL; cursor = cursor->link)
			{
				test = *cursor;
				insertTailTask(test);
			}*/
			return *this;

		}
		

				
	private:
		string object, description;
		int category, priority;
		double time;
		
		string *resources;
		size_type capacity;
		size_type used;
		bool status;
                date start;
                date end;
                //linked list stuff
				
                
                
	};
	/*
	class bag
	{
	public:
		// TYPEDEFS and MEMBER CONSTANTS
		typedef obj value_type;
		typedef std::size_t size_type;
		static const size_type DEFAULT_CAPACITY = 3;
		// CONSTRUCTORS and DESTRUCTOR
		bag(size_type initial_capacity = DEFAULT_CAPACITY);
		bag(const bag& source);
		~bag();
		// MODIFICATION MEMBER FUNCTIONS
		void reserve(size_type new_capacity);
		bool erase_one(value_type& target);
		size_type erase(value_type& target);
		void insert(const value_type& entry);
		void edit(const value_type& entry, int i);
		void operator +=(const bag& addend);
		void operator =(const bag& source);
		// CONSTANT MEMBER FUNCTIONS
		size_type size() const { return used; }
		size_type count(value_type& target) const;
		value_type getdata(int i) { return data[i]; };
	private:
		value_type *data;     // Pointer to partially filled dynamic array
		size_type used;       // How much of array is being used
		size_type capacity;   // Current capacity of the bag
	};
	*/
	// NONMEMBER FUNCTIONS for the bag class
	//bag operator +(const bag& b1, const bag& b2);
        
 /*       typedef obj value_type;

    std::size_t list_length(const obj* head_ptr);
    void list_head_insert(obj*& headptr, value_type& entry); 
    void list_insert(obj* previous_ptr,  value_type& entry);
    void list_tail_insert(obj*& tailptr,  value_type& entry);
    obj* list_search(obj* head_ptr, const value_type& target);
    const obj* list_search(const obj* head_ptr, const value_type& target);
    obj* list_locate(obj* head_ptr, std::size_t position);
    const obj* list_locate(const obj* head_ptr, std::size_t position);
    void list_head_remove(obj*& head_ptr);
    void list_remove(obj* previous_ptr);
    void list_clear(obj*& head_ptr);
    void list_copy(const obj* source_ptr, obj*& head_ptr, obj*& tail_ptr);
	obj* list_merge(obj* head_ptr1, obj* head_ptr2);
*/
	
}

#endif