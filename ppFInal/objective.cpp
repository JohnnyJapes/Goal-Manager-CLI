#include <iostream>
#include <fstream>
#include <cassert>
#include "objective.h"
#include "Task.h"

using namespace date_1;
namespace team3
{
	//constructor and deconstructor
	obj::obj()
	{
		string name = "";
		string Desc = "";
		int Cat = 0;
		int Pri = 0;
		double mTime = 0.0;
        date con;
		
		bool stat = true;
		object = name;
		description = Desc;
		category = Cat;
		priority = Pri;
		time = mTime;
		start = con;
		end = con;
		status = stat;
		size_t initial_capacity = 10;
		resources = new string[initial_capacity];
		capacity = initial_capacity;
		used = 0;
		;
                head = NULL;
                tail = NULL;
                link = NULL;
	}
	obj::obj(string oName, string Desc, int Cat,
		int Pri, double mTime, int startMonth,
		int startDay, int startYear, int endMonth,
		int endDay, int endYear)
	{

	}
	obj::obj(const obj& source)
	{
		object = source.object;
		description = source.description;
		category = source.category;
		priority = source.priority;
		time = source.time;
		start = source.start;
		end = source.end;

		string *larger_array;
		size_t new_capacity = source.capacity;
		//if (new_capacity == capacity)
		//	return; // The allocated memory is already the right size.

		//if (new_capacity < used)
		//	new_capacity = used; // Cant allocate less than we are using.

		larger_array = new string[new_capacity];
		//stdext::checked_array_iterator<string *> chkd_test_array(larger_array, new_capacity);
		copy(source.resources, source.resources + source.used, larger_array);
		//delete[] resources;
		resources = larger_array;
		capacity = new_capacity;
		used = source.used;
		//clearTaskList(head);
		Task* cursor = source.head;
		Task entry;
		if (source.head != NULL)
		{
			entry = *source.head;
			entry.link = NULL;
			insertHeadTask(entry);
			tail = head;
			for (; cursor != NULL; cursor = cursor->link)
			{
				entry = cursor;
				insertTailTask(entry);
			}
			
		}
		else
		{
			head = NULL;
			tail = NULL;
			link = NULL;
		}
	}
	obj::~obj()
	{
		delete [ ] resources;
	}
	// objective
	void obj::setObj(string nObj){
		object = nObj;
	}
	string obj::getObj(){
		return object;
	}

	// description
	void obj::setDescription(string nDesc){
		description = nDesc;
	}
	string obj::getDescription(){
		return description;
	}

	// category
	void obj::setCategory(int nCate){
		category = nCate;
	}
	int obj::getCategory(){
		return category;
	}

	//sets priority
	void obj::setPriority(int nPrior){
		priority = nPrior;
	}
	int obj::getPriority(){
		return priority;
	}

	// time(military)
	void obj::setTime(double nTime){
		time = nTime;
	}
	double obj::getTime(){
		return time;
	}

	// start date
	void obj::setSdate(int month, int day, int year){
            start.setdate(month, day, year);
	}
	string obj::getSdate(){
		string date = start.getdate();
		return date;
	}

	// end date
	void obj::setEdate(int endMonth, int endDay, int endYear){
            end.setdate(endMonth, endDay, endYear);
	}
	string obj::getEdate(){
		string date = end.getdate();
		return date;
	}

	// status
	void obj::setStatus(bool stat){
		status = stat;
	}
	bool obj::getStatus(){
		return status;
	}

	// write
	void obj::write(ofstream& outFile)
	{
		//ofstream outFile;
		//string file = '"' + filename + '"';
		//outFile.open(file);
            
				outFile  << object << " " << description << "|" << category << " "
					<< priority << " " << time << " " << this->getSdate() << " " << this->getEdate() << " "; 
	//	for (int i = 0; i < used; i++)
		//	outFile << resources[i] << " ";
		//outFile << "|";
		for (int i = 0; i < used; i++)
			outFile << resources[i] << " ";
		outFile << "| ";
		if (status == true)
			outFile << "true " ;
		else
			outFile << "false ";
		//outFile.close();

		Task* cursor = head;
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

	// read
	void obj::read(ifstream& inFile){
		string month, day, year, st, ti;
		int m, d, y;
		double t;
		getline(inFile, object, ' ');
		getline(inFile, description, '|');
		getline(inFile, month, ' ');
		category = stoi(month);
		getline(inFile, month, ' ');
		priority = stoi(month);
		
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
		getline(inFile, st, ' ');
		if (st == "*")
		{
			inFile.ignore(1);
			return;
		}
		else if (head != NULL)
			for (Task* cursor = head; cursor != NULL; cursor = cursor->link)
			{
			cursor->read(inFile);
			
			getline(inFile, st, ' ');
			if (st == "+")
			{
				cursor->link = new Task;
				tail = cursor->link;
			}
			else
				inFile.ignore(1);
			}
		else
		{
			head = new Task;
			tail = head;
			for (Task* cursor = head; cursor != NULL ; cursor = cursor->link)
				
			{
				cursor->read(inFile);
				getline(inFile, st, ' ');
				if (st == "+")
				{
					cursor->link = new Task;
					tail = cursor->link;
				}
				else;
					//inFile.ignore(1);
			}
		}
	}

	// display
	void obj::display()
	{
                cout << "Objective: " << object << endl;
                cout << "Description:" << endl << description << endl;
                cout << left << setw(15) << "category" << " " << setw(15)
				<< "priority" << " " << setw(15) << "time" << " " << setw(15) << "Start Date" << setw(15) << "End Date" <<
                                 setw(15) << "status" <<endl;
		cout << left << setw(15) <<  category << " " << setw(15)
			<< priority << " " << setw(15) << time << " "<< setw(15) << start.getdate()  << " "<< setw(15) << end.getdate() << " ";
		/*for (int i = 0; i < used; i++)
			cout  << setw(10) << resources[i] << " ";*/
		
		if (status == true)
			cout << "true" << "\n";
		else
			cout << "false" << "\n";
                cout << "Resources:" << endl;
                for (int i = 0; i < used; i++)
					cout  << resources[i] << " ";
                cout << "\n-------\nTask(s)" << endl;
//                bool loop = true;
                Task* cursor = head;
                if (cursor == NULL)
                    cout << "No tasks" << endl;
                else
                    for (;cursor != NULL; cursor = cursor->link)
                    {
                        cursor->display();
						if (cursor->link != NULL)
							cout << "\n-----------------------" << endl;
                    }
				
                //cout << "\n------------------------------------------------------------------------------------" << endl;
//                while (loop == true)
//                {
//                    
//                }
	}

	// resources
	
	void obj::reserve(size_type new_capacity)
	{
		string *larger_array;

		if (new_capacity == capacity)
			return; // The allocated memory is already the right size.

		if (new_capacity < used)
			new_capacity = used; // Can�t allocate less than we are using.

		larger_array = new string[new_capacity];
		//stdext::checked_array_iterator<string *> chkd_test_array(larger_array, new_capacity);
		copy(resources, resources + used, larger_array);
		delete [ ] resources;
		resources = larger_array;
		capacity = new_capacity;

	}
	//obj* obj::getLink(){
	//	return link;
	//}
	void obj::insertResource(string entry)
	{
		if (used == capacity)
			reserve(used + 1);
		resources[used] = entry;
		++used;
	}
	
	bool obj::erase_one(const string target)
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
	void obj::erase(const string target)
	{

	}
        
        void obj::insertHeadTask(Task entry)
        {
            Task* insertPtr = new Task;
            *insertPtr = entry;
            insertPtr->link = head;
            head = insertPtr;
                        
        }
        void obj::insertTask(Task*& previousPtr, Task entry)
        {
            Task* insertPtr = new Task;
            *insertPtr = entry;
            insertPtr->link = previousPtr->link;
            previousPtr->link = insertPtr;
                        
        }
		void obj::insertTailTask(Task entry)
		{
			Task* insertPtr = new Task;
			*insertPtr = entry;
			insertPtr->link = NULL;
			tail->link = insertPtr;


		}
                
        void obj::deleteHeadTask(Task*& headPtr)
        {
			Task *remove_ptr;

			remove_ptr = headPtr;
			headPtr = headPtr->link;
			delete remove_ptr;
        }
		void obj::removeTask(Task*& previousPtr)
		{
			Task *remove_ptr;

			remove_ptr = previousPtr->link;
			previousPtr->link = remove_ptr->link;
			delete remove_ptr;

		}
		void obj::clearTaskList(Task*& headptr)
		{
			while (headptr != NULL)
				deleteHeadTask(headptr);

		}
        Task* obj::listSearch(Task* headPtr, Task& target)
        {
			return(headPtr);
        }
              
        Task* obj::listLocate(Task* headPtr, std::size_t position)
        {
			return(headPtr);
            
        }
               
        void obj::listRemove(Task*& previousPtr)
        {
			Task *removePtr = new Task;
			removePtr = previousPtr->link;
			previousPtr->link = removePtr->link;
			delete removePtr;

        }
		//obj*& obj::operator=(obj);
       //Linked-List implementation
        //
        //
        //
        //
        //////////////////////////////////////////////////////////////////////////////////////////////
  //       size_t list_length(const obj* head_ptr)
  //  // Library facilities used: cstdlib
  //  {
		//const obj *cursor;
		//size_t answer;

		//answer = 0;
		//for (cursor = head_ptr; cursor != NULL; cursor = cursor->link)
		//	++answer;
	
		//return answer;
  //  }
  //  
  //  void list_head_insert(obj*& head_ptr,  value_type& entry)
  //  {
		//obj* insert_ptr = new obj;
		//*insert_ptr = entry;
		//insert_ptr->link = head_ptr;
		//head_ptr = insert_ptr;
  //  }

  //  void list_insert(obj* previous_ptr,  value_type& entry) 
  //  {
		//obj *insert_ptr = new obj;
  //  
		//*insert_ptr  = entry,
		//insert_ptr->link = previous_ptr->link;
		//previous_ptr->link = insert_ptr;
  //  }
  //  void list_tail_insert(obj*& tailptr,  value_type& entry)
  //  {
  //              obj* insert_ptr = new obj;
		//*insert_ptr = entry;
		//tailptr->link = insert_ptr;
		//insert_ptr->link = NULL;
  //              tailptr = insert_ptr;
  //  }
  //  
  //  obj* list_search(obj* head_ptr,  value_type& target) 
  //  // Library facilities used: cstdlib
  //  {
		//obj *cursor;
  // 
		//for (cursor = head_ptr; cursor != NULL; cursor = cursor->link)
		//	if (target.getObj() == cursor->getObj())
		//	return cursor;
		//return NULL;
  //  }

  ////  const obj* list_search(const obj* head_ptr, const value_type& target) 
  ////  // Library facilities used: cstdlib
  ////  {
		////const obj *cursor;
  //// 
		////for (cursor = head_ptr; cursor != NULL; cursor = cursor->link)
		////	if (target.getObj() == cursor->getObj())
		////	return cursor;
		////return NULL;
  ////  }

  //  obj* list_locate(obj* head_ptr, size_t position) 
  //  // Library facilities used: cassert, cstdlib
  //  {
		//obj *cursor;
		//size_t i;
  //  
		//assert (0 < position);
		//cursor = head_ptr;
		//for (i = 1; (i < position) && (cursor != NULL); i++)
		//	cursor = cursor->link;
		//return cursor;
  //  }

  //  const obj* list_locate(const obj* head_ptr, size_t position) 
  //  // Library facilities used: cassert, cstdlib
  //  {
		//const obj *cursor;
		//size_t i;
  //  
		//assert (0 < position);
		//cursor = head_ptr;
		//for (i = 1; (i < position) && (cursor != NULL); i++)
		//	cursor = cursor->link;
		//return cursor;
  //  }

  //  void list_head_remove(obj*& head_ptr)
  //  {
		//obj *remove_ptr;

		//remove_ptr = head_ptr;
		//head_ptr = head_ptr->link;
		//delete remove_ptr;
  //  }

  //  void list_remove(obj* previous_ptr)
  //  {
		//obj *remove_ptr;

		//remove_ptr = previous_ptr->link;
		//previous_ptr->link = remove_ptr->link;
		//delete remove_ptr;
  //  }

  //  void list_clear(obj*& head_ptr)
  //  // Library facilities used: cstdlib
  //  {
		//while (head_ptr != NULL)
		//    list_head_remove(head_ptr);
  //  }

  //  void list_copy(const obj* source_ptr, obj*& head_ptr, obj*& tail_ptr) 
  //  // Library facilities used: cstdlib
  //  {
		//head_ptr = NULL;
		//tail_ptr = NULL;

		//// Handle the case of the empty list.
		//if (source_ptr == NULL)
		//	return;
  //  
		//// Make the head obj for the newly created list, and put data in it.
		//list_head_insert(head_ptr, source_ptr->data);
		//tail_ptr = head_ptr;
  //  
		//// Copy the rest of the objs one at a time, adding at the tail of new list.
		//source_ptr = source_ptr->link; 
		//while (source_ptr != NULL)
		//{
		//	list_insert(tail_ptr, source_ptr->data);
		//	tail_ptr = tail_ptr->link;
		//	source_ptr = source_ptr->link;
		//}
    }

	//obj* list_merge(obj* head_ptr1, obj* head_ptr2)
	//{
	//	obj* merge = NULL;
	//	obj* tail = NULL;
	//	 
	//	// loop to process through both linked lists creating new merged list



	//	return merge;
	//}
	
//}