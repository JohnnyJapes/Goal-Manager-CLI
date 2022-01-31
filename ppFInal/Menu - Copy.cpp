
#include<iomanip>
#include<iostream>
#include<cstdlib>
#include<cassert>
#include<fstream>
#include "objective.h"




using namespace team3;

void listName(obj*);
void insertNew(obj*&, int&);
void insertTask(obj*&);
void edit(obj*&, int);
void taskEdit(Task*&, int);

void display(obj*, int);
void displayCategory();
void displayPriority();
void reserve(size_t );
void insert(const obj& entry);
void write(ofstream&);
void read(ifstream&);
int search(string);
void erase(int);
void displaySmall(obj*&);








int main()
{
	obj* headptr = new obj;
    obj* tailptr = new obj;
	
	int menu;
	int used;
        
	string filename, name;
	int i = 0;

	used = 0;

	for (bool go = true;go == true;)
	{
		cout << "\nChoose menu option\n" << endl;
		cout << "1. New Objective" << endl
			<< "2. Edit objective" << endl
			<< "3. Delete objective" << endl
			<< "4. Display objective information" << endl
			<< "5. Display simple listing" << endl
			<< "6. Display full listing" << endl
			<< "7. Write all objectives to file" << endl
			<< "8. Read objectives from file" << endl
			<< "9. Exit" << endl;
		cin >> menu;



		switch (menu)
		{
		case 1:
                        if(used == 0)
                        {
                            insertNew(headptr, used);
							
                            tailptr = headptr;
                        }
                        else
                            insertNew(tailptr, used);
			break;
		case 2:
			cout << "Please choose an objective" << endl;
			listName(headptr);
			cin >> i;
			edit(headptr,i);
			break;
		case 3:
			/*cout << "Enter objective name" << endl;
			cin >> name;
			i = search(name);
			if (i == -1)
			{
				cout << "No objective with that name" << endl;
				break;
			}*/
                        cout << "Please choose an objective" << endl;
			listName(headptr);
                        cin >> i;
			erase(i);
			break;
		case 4:
			cout << "Please choose an objective" << endl;
			listName(headptr);
            cin >> i;
			
			

			display(headptr,i);
			break;
		case 5:
			/*cout << "Enter objective name" << endl;
			cin >> name;
			i = search(name);
			if (i == -1)
			{
				cout << "No objective with that name" << endl;
				break;
			}*/
			displaySmall(headptr);
			break;
		case 6:
			
			display(headptr, -1);
			break;
		case 7:
		{
			ofstream outFile;
			cout << "Filename?:" << endl;
			cin >> filename;
			outFile.open(filename.c_str(), ios::ate);
			write(outFile);
			outFile.close();
		}
		break;
		case 8:
		{
			ifstream inFile;
			cout << "Filename?:" << endl;
			cin >> filename;
			inFile.open(filename.c_str());
			read(inFile);
			inFile.close();

		}
		break;
		case 9:
			go = false;
			break;
		default:
			cout << "Enter valid menu option" << endl;
			break;
		}
	}
	
}
void listName(obj* head)
{
	int count = 1;
	if (head->link = NULL)
	{
		cout << "1. " << head->getObj() << endl;
	}
	else
	{
		for (obj* cursor = head; cursor != NULL; cursor = cursor->link)
		{
			cout << count << ". " << cursor->getObj() << endl;
			count++;

		}
	}

}
void insertNew(obj*& node,int& used)
{
	
	obj temp;
	char c;
	bool stat, loop;
	int i, m, y;
	double d;
	string s, o, ss;
    char choice, choice2;
	cout << "Please enter name of new objective" << endl;
	cin >> o;
	temp.setObj(o);
	cout << "Please enter description (enter 0 alone to stop)" << endl;
	for (bool loop = true; loop == true;)
	{
		cin >> ss;
		if (ss == "0")
			loop = false;
		else
			s += (" " + ss);

	}
	temp.setDescription(s);
	cout << "Please give a category" << endl;
	displayCategory();
	cin >> i;
        
	temp.setCategory(i);
	displayPriority();
	cin >> i;
	temp.setPriority(i);
	cout << "Please enter number of hours required" << endl;
	cin >> d;
	temp.setTime(d);
	cout << "Please enter the Start date (numeral form, 3 5 2012)" << endl;
	cin >> i>> m>> y;
	temp.setSdate(i, m, y);
	cout << "Please enter the end date (numeral form, 3 5 2012)" << endl;
	cin >> i>> m>> y;
	temp.setEdate(i, m, y);
	cout << "Status of objective?" << endl;
	cout << "Complete (y/n)" << endl;
	cin >> c;
	switch (c)
	{
	case 'Y':
	case 'y':
		stat = true;
		break;
	case 'n':
	case 'N':
		stat = false;
		break;
	default:
		cout << "must be y or n, defaulting to false" << endl;
		break;
	}
	temp.setStatus(stat);
	cout << "Resources? (enter 0 to exit)" << endl;
	for (bool loop = true; loop == true;)
	{
		cin >> ss;
		if (ss == "0")
			loop = false;
		else
			temp.insertResource(ss);

	}
	if (used == 0)
	{
		list_head_insert(node, temp);
		//delete node->link;
		list_remove(node);
		node->link = NULL;
		used++;
		
	}
	else
		list_tail_insert(node, temp);
	//head->data = temp;
        cout << "Add Tasks? (y/n)" << endl;
        cin >> choice;
        choice = toupper(choice);
		Task insert;
		
		switch (choice)
		{
		case 'Y':
			loop = true;
			
			while (loop = true)
			{
				
				cout << "Please enter name of new task" << endl;
				cin >> o;
				insert.setName(o);
				cout << "Please enter description (enter > to stop)" << endl;
				//for (bool loop = true; loop == true;)
				//{
					getline(cin, s, '>');
					/*cin >> ss;
					if (ss == "0")
						loop = false;
					else
						s += (" " + ss);
*/
				//}
				insert.setDescription(s);

				cout << "Please enter number of hours required" << endl;
				cin >> d;
				insert.setTime(d);
				cout << "Please enter the Start date (numeral form, 3 5 2012)" << endl;
				cin >> i >> m >> y;
				insert.setSdate(i, m, y);
				cout << "Please enter the end date (numeral form, 3 5 2012)" << endl;
				cin >> i >> m >> y;
				insert.setEdate(i, m, y);
				cout << "Status of objective?" << endl;
				cout << "Complete (y/n)" << endl;
				cin >> c;
				switch (c)
				{
				case 'Y':
				case 'y':
					stat = true;
					break;
				case 'n':
				case 'N':
					stat = false;
					break;
				default:
					cout << "must be y or n, defaulting to false" << endl;
					break;
				}
				insert.setStatus(stat);
				cout << "Resources? (enter 0 to exit)" << endl;
				bool loop = true;
				while (loop)
				{
					cin >> ss;
					if (ss == "0")
						loop = false;
					else
						insert.insertResource(ss);

				}
				if (node->head->getName() == "stop")
				{
					node->insertHeadTask(insert);
					node->listRemove(node->head);
					node->tail = node->head;
				}
				else
					node->insertTailTask(insert);
				
				cout << "Add another task?(y/n)" << endl;
				cin >> choice2;
				choice2 = toupper(choice2);
				if (choice == 'N')
					loop = false;
				break;


			}
		case 'N':
			break;
		
			
		}

   //     if(used == 0)
   //     {
   //         list_head_insert(node, temp);
   //         //delete node->link;
   //         node->link = NULL;
			//used++;
   //     }
   //     else
   //         list_tail_insert(node, temp);

		
}

void insertTask(obj*& node)
{
	string s, ss, o;
	double d;
	int i, m, y;
	char c;
	bool stat, loop;
	Task insert;

	
			cout << "Please enter name of new task" << endl;
			cin >> o;
			insert.setName(o);
			cout << "Please enter description (enter > to stop)" << endl;
			//for (bool loop = true; loop == true;)
			//{
			getline(cin, s, '>');
			/*cin >> ss;
			if (ss == "0")
			loop = false;
			else
			s += (" " + ss);
			*/
			//}
			insert.setDescription(s);

			cout << "Please enter number of hours required" << endl;
			cin >> d;
			insert.setTime(d);
			cout << "Please enter the Start date (numeral form, 3 5 2012)" << endl;
			cin >> i >> m >> y;
			insert.setSdate(i, m, y);
			cout << "Please enter the end date (numeral form, 3 5 2012)" << endl;
			cin >> i >> m >> y;
			insert.setEdate(i, m, y);
			cout << "Status of objective?" << endl;
			cout << "Complete (y/n)" << endl;
			cin >> c;
			switch (c)
			{
			case 'Y':
			case 'y':
				stat = true;
				break;
			case 'n':
			case 'N':
				stat = false;
				break;
			default:
				cout << "must be y or n, defaulting to false" << endl;
				break;
			}
			insert.setStatus(stat);
			cout << "Resources? (enter 0 to exit)" << endl;
			bool loop = true;
			while (loop)
			{
				cin >> ss;
				if (ss == "0")
					loop = false;
				else
					insert.insertResource(ss);

			}
			if (node->head->getName() == "stop")
			{
				node->insertHeadTask(insert);
				node->listRemove(node->head);
				node->tail = node->head;
			}
			else
				node->insertTailTask(insert);

}

void edit(obj*& head, int j)
{
    string temp;
    int i, d,m,y;
    double time;
    char c;
    obj* cursor = head;
    Task* cursor2;
	bool status;
    for(int count = 1 ; count !=j && cursor->link != NULL; cursor = cursor->link)
    {
        count++;
        
    }
    
	cout << "Which aspect would you like to edit?" << endl
		<< "1. Objective name" << endl
		<< "2. Objective description" << endl
		<< "3. Objective category" << endl
		<< "4. Objective priority" << endl
		<< "5. Objective time requirement" << endl
		<< "6. Objective start date" << endl
		<< "7. Objective end date" << endl
		<< "8. Edit a task" << endl
		<< "9. Add a task" << endl
		<< "10. Remove a task" << endl
		<< "11. Objective status" << endl;
	int choice, choice2;
        cin >> choice;
        
        switch(choice)
        {
            case 1:
                cout << "Current objective name = " <<  cursor->getObj() << endl;
                cout << "New name?" << endl;
                cin >> temp;
                cursor->setObj(temp);
                break;
            case 2:
                cout << "Current description: " << endl
                        << cursor->getDescription() << endl;
                cout << "New description?" <<endl;
                cin >> temp;
                cursor->setDescription(temp);
                break;
            case 3:
                cout << "Current category: " << cursor->getCategory() << endl;
                displayCategory();
                cout << "New Category?" << endl;
                cin >> i;
                cursor->setCategory(i);
                break;
            case 4:
                cout << "Current priority: " << cursor->getPriority() << endl;
                cout << "New priority?" << endl;
                cin >> i;
                cursor->setPriority(i);
                break;
            case 5:
                cout << "Current estimated time" << cursor->getTime() << endl;
                cout << "New estimated time?" << endl;
                cin >> time;
                cursor->setTime(time);
                break;
            case 6:
                cout << "Current start date: " << cursor->getSdate() << endl;
                cout << "New start date?" << endl;
                cout << "Month?" << endl;
                cin >> m;
                cout << "Day?" << endl;
                cin >> d;
                cout << "Year?" << endl;
                cin >> y;
                cursor->setSdate(m, d, y);
                
                break;
            case 7:
                cout << "Current end date: " << cursor->getEdate() << endl;
                cout << "New end date?" << endl;
                cout << "Month?" << endl;
                cin >> m;
                cout << "Day?" << endl;
                cin >> d;
                cout << "Year?" << endl;
                cin >> y;
                cursor->setEdate(m, d, y);
            case 8:
                i = 1;
                cout<< "Choose a task" << endl;
                if (cursor->head->link = NULL)
                {
                        cout << "1. " << cursor->head->getName() << endl;
                }
                else
                {
                        for ( cursor2 = cursor->head; cursor2 != NULL; cursor2 = cursor2->link)
                        {
                                cout << i << ". " << cursor2->getName() << endl;
                                i++;

                        }
                }
                cin >> i;
                cursor2 = cursor->head;
                for(int count = 1 ; count !=i && cursor2->link != NULL; cursor2 = cursor2->link)
                    {
                        count++;

                    }
                cout << "Which aspect would you like to edit?" << endl
		<< "1. Task name" << endl
		<< "2. Task description" << endl
		<< "3. Task time requirement" << endl
		<< "4. Task start date" << endl
		<< "5. Task end date" << endl
		<< "6. Task status" << endl;
                cin >> choice2;
                taskEdit(cursor2, choice2);
                break;
			case 9:
				insertTask(cursor);
				break;
            case 11:
                 cout << "Current Status: " << cursor2->getStatus() << endl;
            cout << "New status?" << endl;
             cout << "Complete (y/n)" << endl;
                cin >> c;
                switch (c)
                {
                case 'Y':
                case 'y':
                        status = true;
                        break;
                case 'n':
                case 'N':
                        status = false;
                        break;
                default:
                        cout << "must be y or n, defaulting to false" << endl;
                        break;
                }
                break;
                
        }
	
	/*obj temp;
	char c;
	bool stat;
	int i, m, y;
	double d;
	string s, o, ss;
	cout << "Please enter name of new objective" << endl;
	cin >> o;
	temp.setObj(o);
	cout << "Please enter description (enter 0 alone to stop)" << endl;
	for (bool loop = true; loop == true;)
	{
		cin >> ss;
		if (ss == "0")
			loop = false;
		else
			s += (" " + ss);

	}
	temp.setDescription(s);
	cout << "Please enter category" << endl;
	cin >> i;
	temp.setCategory(i);
	cout << "Please enter priority" << endl;
	cin >> i;
	temp.setPriority(i);
	cout << "Please enter number of hours required" << endl;
	cin >> d;
	temp.setTime(d);
	cout << "Please enter the Start date (numeral form, 3 5 2012)" << endl;
	cin >> i>> m>> y;
	temp.setSdate(i, m, y);
	cout << "Please enter the end date (numeral form, 3 5 2012)" << endl;
	cin >> i>> m>> y;
	temp.setEdate(i, m, y);
	cout << "Status of objective?" << endl;
	cout << "Complete (y/n)" << endl;
	cin >> c;
	switch (c)
	{
	case 'Y':
	case 'y':
		stat = true;
		break;
	case 'n':
	case 'N':
		stat = false;
		break;
	default:
		cout << "must be y or n, defaulting to false" << endl;
		break;
	}
	temp.setStatus(stat);
	cout << "Resources? (enter 0 to exit)" << endl;
	for (bool loop = true; loop == true;)
	{
		cin >> ss;
		if (ss == "0")
			loop = false;
		else
			temp.insertResource(ss);

	}
	*/
}

void taskEdit(Task*& cursor2, int choice2)
{
     string temp;
    int i, d,m,y;
    double time;
    char c;
	bool status;
    switch(choice2)
    {
        case 1:
            cout << "Current Task name = " <<  cursor2->getName() << endl;
            cout << "New name?" << endl;
            cin >> temp;
            cursor2->setName(temp);
            break;
        case 2:
            cout << "Current description: " << endl
                    << cursor2->getDescription() << endl;
            cout << "New description?" <<endl;
            cin >> temp;
            cursor2->setDescription(temp);
            break;
        
        case 3:
            cout << "Current estimated time" << cursor2->getTime() << endl;
            cout << "New estimated time?" << endl;
            cin >> time;
            cursor2->setTime(time);
            break;
        case 4:
            cout << "Current start date: " << cursor2->getSdate() << endl;
            cout << "New start date?" << endl;
            cout << "Month?" << endl;
            cin >> m;
            cout << "Day?" << endl;
            cin >> d;
            cout << "Year?" << endl;
            cin >> y;
            cursor2->setSdate(m, d, y);

            break;
        case 5:
            cout << "Current end date: " << cursor2->getEdate() << endl;
            cout << "New end date?" << endl;
            cout << "Month?" << endl;
            cin >> m;
            cout << "Day?" << endl;
            cin >> d;
            cout << "Year?" << endl;
            cin >> y;
            cursor2->setEdate(m, d, y);
            break;
        case 6:
            cout << "Current Status: " << cursor2->getStatus() << endl;
            cout << "New status?" << endl;
             cout << "Complete (y/n)" << endl;
                cin >> c;
                switch (c)
                {
                case 'Y':
                case 'y':
                        status = true;
                        break;
                case 'n':
                case 'N':
                        status = false;
                        break;
                default:
                        cout << "must be y or n, defaulting to false" << endl;
                        break;
                }
            break;
     }
}
void display(obj* head, int i)
{
	obj* cursor = head;
	if (i == -1)
	{
		for (; cursor != NULL; cursor = cursor->link)
			cursor->display();
	}
	else
	{
		for (int count = 1; count != i && cursor->link != NULL; cursor = cursor->link)
		{
			count++;

		}
		cursor->display();
	}
}
void displayCategory()
{
    cout << "1. Urgent-Important" << endl
            << "2. Not urgent-Important" << endl
            << "3. Urgent-Not Important" << endl
            << "4. Not urgent-Not Important" << endl;

}
void displayPriority()
{
    cout << "Please give a priority" << endl;
	cout << "1. Very important" << endl
		<< "2. Important" << endl
		<< "3. Sort of Important" << endl
		<< "4. Not very importnat" << endl
		<< "5. unimportant" << endl;
}
/*void reserve(size_t new_capacity)
// Library facilities used: algorithm
{
	obj *larger_array;

	if (new_capacity == capacity)
		return; // The allocated memory is already the right size.

	if (new_capacity < used)
		new_capacity = used; // Can�t allocate less than we are using.

	larger_array = new obj[new_capacity];
	stdext::checked_array_iterator<obj *> chkd_test_array(larger_array, new_capacity);
	copy(bagz, bagz + used, chkd_test_array);
	delete[] bagz;
	bagz = larger_array;
	capacity = new_capacity;
}*/
void insert(const obj& entry)
{
	
	
}

void write(ofstream& outFile)
{
	for (size_t i = 0; i <20 ; i++);
		//bagz[i].write(outFile);



}
void read(ifstream& inFile)
{
	/*obj temp;
	for (size_t i = used; (!inFile.eof()) && (i != 3); i++)
		if (!inFile.eof())
		{
			if (i < (capacity - 1))
			{
				//cout << "under" << i << endl;		//debug purposes, count loop
				bagz[i].read(inFile);
				++used;
			}
			else
			{
				//cout << "insert" << i << endl; //here for debug purposes
				temp.read(inFile);
				insert(temp);
			}
		}*/
}
int search(string name)
{
    /*
	int i;
	for (i = 0; (i < used) && (bagz[i].getObj() != name); i++);
	if (bagz[i].getObj() != name)
	{
		return (-1);
	}
	return i;
*/
	return(0);
}
void erase(int i)
{
	
	

}
void displaySmall(obj*& headptr)
{
	cout << left << setw(15) << "objective" << setw(15) << "category" << " " << setw(15)
		<< "priority" << " " << setw(15) << "Time" << " " << setw(15) << "Status" << setw(15) << endl;
	obj* cursor = headptr;

	for (; cursor != NULL; cursor = cursor->link)
	{
		cout << left << setw(15) << cursor->getObj() << setw(15) << cursor->getCategory() << " " << setw(15)
			<< cursor->getPriority() << " " << setw(15) << cursor->getTime() << " " << setw(15);
		if (cursor->getStatus() == false)
			cout << "Incomplete" << endl;
		else
			cout << "Complete" << endl;
	}

}