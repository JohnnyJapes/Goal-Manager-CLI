
#include<iomanip>
#include<iostream>
#include<cstdlib>
#include<cassert>
#include<fstream>
#include "Goal.h"

//to do
// sort functions
// polish up edit functions
// display functions may or may not display correctly and need format changes



using namespace team3;

void listGoalName(Goal*);				//lists names of goals in decsending order
void listTaskName(Task*);				//see above
void listObjectiveName(obj*);			//see above
void insertNewGoal(Goal*&, int&);		
void insertNewObjective(Goal*&, int&);
void insertTask(obj*&);
void editGoal(Goal*&, int, Goal*&);				//needs polishing
void editObjective(obj*&, int);
void taskEdit(Task*&);

void removeGoal(Goal*&, Goal*&);		//headptr input needed
void removeObjective(Goal*&);
void removeTask(obj*&);


void display(Goal*, int);
void displayCategory();
void displayPriority();
void write(ofstream&, Goal*&);				//pointer should be to head
void read(ifstream&, Goal*&, Goal*&);				//pointer should be to tail, head
int search(string);
void erase(int);
void displaySmall(Goal*&);
void sortGoals(Goal*&);
void sortDate(Goal*&);
void sortPriority(Goal*&);
void sortStatus(Goal*&);
void SDpriority(Goal*&);
void SDdate(Goal*&);
void SDstatus(Goal*&);






int main()
{
	Goal* headptr = NULL;
    Goal* tailptr = NULL;
	
	int menu;
	int used;
        
	string filename, name;
	int i = 0;

	used = 0;

	for (bool go = true;go == true;)
	{
		cout << "\nChoose menu option\n" << endl;
		cout << "1. New Goal" << endl
			<< "2. Edit Goal" << endl
			<< "3. Delete Goal" << endl
			<< "4. Display Goal information" << endl
			<< "5. Display simple listing" << endl
			<< "6. Display full listing" << endl
			<< "7. Sort Goals" << endl
			<< "8. Write all Goals to file" << endl
			<< "9. Read Goals from file" << endl
			<< "10. Search and display list based on priority" << endl
			<< "11. Search and display list based on range of due dates" << endl
			<< "12. Search and display list based on status" << endl
			<< "13. Exit" << endl;
		cin >> menu;



		switch (menu)
		{
		case 1:
                        if(headptr == NULL && tailptr == NULL)
                        {
                            insertNewGoal(headptr, used);
							
                            tailptr = headptr;
                        }
                        else
                            insertNewGoal(tailptr, used);
			break;
		case 2:
			cout << "Please choose a Goal" << endl;
			listGoalName(headptr);
			cin >> i;
			editGoal(headptr,i, tailptr);
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
                        cout << "Please choose a Goal" << endl;
			listGoalName(headptr);
			removeGoal(headptr, tailptr);
			break;
		case 4:
			cout << "Please choose Goal" << endl;
			listGoalName(headptr);
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
			sortGoals(headptr);
			for (Goal* cursor = headptr; cursor != NULL; cursor = cursor->link)
			{
				
				if (cursor->link == NULL)
					tailptr = cursor;
			}
			break;
		case 8:
		{
			ofstream outFile;
			cout << "Filename?:" << endl;
			cin >> filename;
			outFile.open(filename.c_str(), ios::ate);
			write(outFile, headptr);
			outFile.close();
		}
		break;
		case 9:
		{
			ifstream inFile;
			cout << "Filename?:" << endl;
			cin >> filename;
			inFile.open(filename.c_str());
			
			read(inFile, tailptr, headptr);
			inFile.close();

		}
		break;
		case 10:
			SDpriority(headptr);
			break;
		case 11:
			SDdate(headptr);
			break;
		case 12:
			SDstatus(headptr);
			break;
		case 13:
			go = false;
			break;
		default:
			cout << "Enter valid menu option" << endl;
			break;
		}
	}
	
}
void listObjectiveName(obj* head)
{
	int count = 1;
	if (head->link == NULL)
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
void listGoalName(Goal* head)
{
	int count = 1;
	if (head->link == NULL)
	{
		cout << "1. " << head->getName() << endl;
	}
	else
	{
		for (Goal* cursor = head; cursor != NULL; cursor = cursor->link)
		{
			cout << count << ". " << cursor->getName() << endl;
			count++;

		}
	}

}
void listTaskName(Task* head)
{
	int count = 1;
	if (head->link == NULL)
	{
		cout << "1. " << head->getName() << endl;
	}
	else
	{
		for (Task* cursor = head; cursor != NULL; cursor = cursor->link)
		{
			cout << count << ". " << cursor->getName() << endl;
			count++;

		}
	}

}
void insertNewGoal(Goal*& node, int& used)
{
	Goal temp;
	int p, m, d, y;				//temp variables
	string description;
	string mm, dd, yy;
	char choice;
	bool status;
	cout << "Enter goal name" << endl;
	//getline(cin,description, '\n');
	cin >> description;
	getline(cin, description, '\n');		//prevents \n from previous cin being included in the description
	temp.setName(description);
	cout << "Enter goal description(0 to stop)\n";
	getline(cin, description, '0');
	temp.setDescription(description);
	displayPriority();
	cin >> p;
	temp.setPriority(p);
	cout << "Enter start date\n";
	cout << "Please enter the Start date (include slashes, 3/5/2012)" << endl;

	getline(cin, mm, '/');
	getline(cin, dd, '/');
	cin >> yy;	
	temp.setSdate(stoi(mm), stoi(dd), stoi(yy));
	cout << "Please enter the end date (include slashes, 3/5/2012)" << endl;
	getline(cin, mm, '/');
	getline(cin, dd, '/');
	cin >> yy;
	temp.setEdate(stoi(mm), stoi(dd), stoi(yy));

	cout << "Status of Goal?" << endl;
	cout << "Complete (y/n)" << endl;
	cin >> choice;
	switch (choice)
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
	temp.setStatus(status);
	
	
	if (node == NULL)
	{
		list_head_insert(node, temp);
		//delete node->link;
		//list_remove(node);
		node->link = NULL;
		used++;

	}
	else
		list_tail_insert(node, temp);

	cout << "Add objective?" << endl;
	cin >> choice;
	while (toupper(choice) == 'Y')
	{
		insertNewObjective(node, node->used);
		cout << "Enter another objective?" << endl;
		cin >> choice;
		
	}



}
void insertNewObjective(Goal*& node,int& used)
{
	//temp variables
	obj temp;
	char c;
	bool stat, loop;
	int i, m, y;
	double d;
	string s, o, ss;
    char choice, choice2;
	cout << "Please enter name of new objective" << endl;
	cin >> o;
	getline(cin, o, '\n');		//prevents \n from previous cin being included in the description
	temp.setObj(o);
	cout << "Please enter description (enter 0 to stop)" << endl;
	getline(cin, s, '0');
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
	cout << "Please enter the Start date (include slashes, 3/5/2012)" << endl;
	
	getline(cin, s, '/');
	getline(cin, o, '/');
	cin >> ss;
	temp.setSdate(stoi(s), stoi(o), stoi(ss));
	cout << "Please enter the end date (include slashes, 3/5/2012)" << endl;
	getline(cin, s, '/');
	getline(cin, o, '/');
	cin >> ss;
	temp.setEdate(stoi(s), stoi(o), stoi(ss));
	
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
	if (node->head == NULL)
	{
		node->insertHeadObjective(temp);
		//delete node->link;
		//list_remove(node);
		node->link = NULL;
		node->tail = node->head;
		
	}
	else
		node->insertTailObjective(temp);
	//head->data = temp;
        cout << "Add Tasks? (y/n)" << endl;
        cin >> choice;
        choice = toupper(choice);
		Task insert;
		loop = true;
		while (loop)
		{
			switch (choice)
			{
			case 'Y':
					insertTask(node->head);
					cout << "Insert another Task" << endl;
					cin >> choice;
					choice = toupper(choice);
					break;
			
			case 'N':
				loop = false;
				break;
			default:
					cout << "must be y or n" << endl;
					break;
			}
			 
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
			getline(cin, o, '\n');
			insert.setName(o);
			cout << "Please enter description (enter 0 to stop)" << endl;
			//for (bool loop = true; loop == true;)
			//{
			getline(cin, s, '0');
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
			cout << "Please enter the end date (include slashes, 3/5/2012)" << endl;
			getline(cin, s, '/');
			getline(cin, o, '/');
			cin >> ss;
			insert.setSdate(stoi(s), stoi(o), stoi(ss));
			cout << "Please enter the end date (include slashes, 3/5/2012)" << endl;
			getline(cin, s, '/');
			getline(cin, o, '/');
			cin >> ss;
			insert.setEdate(stoi(s), stoi(o), stoi(ss));
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
			loop = true;
			while (loop)
			{
				cin >> ss;
				if (ss == "0")
					loop = false;
				else
					insert.insertResource(ss);

			}
			if (node->head == NULL)
			{
				node->insertHeadTask(insert);
				//node->listRemove(node->head);
				node->tail = node->head;
			}
			else
				node->insertTailTask(insert);

}
void editGoal(Goal*& head, int j, Goal*& tail)
{
	Goal* cursor = head;
	//temp variables
	string str, m, d, y;
	int pri;
	bool status;
	char c;
	for (int count = 1; count != j && cursor->link != NULL; cursor = cursor->link)
	{
		count++;

	}
	int choice;
	cout << "Which aspect would you like to edit?" << endl
		<< "1. Goal name" << endl
		<< "2. Goal description" << endl
		<< "3. Goal priority" << endl
		<< "4. Goal start date" << endl
		<< "5. Goal end date" << endl
		<< "6. Edit an objective" << endl
		<< "7. Add an objective" << endl
		<< "8. Remove an objective" << endl
		<< "9. Goal status" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Current Goal name: " << cursor->getName() << endl;
		cout << "New Name?" << endl;
		cin >> str;
		cursor->setName(str);
		break;
	case 2:
		cout << "Current Description:\n" << cursor->getDescription();
		cout << "\n New Description?(0 to stop)" << endl;
		getline(cin, str, '0');
		cursor->setDescription(str);
		break;
	case 3:
		cout << "Current priority: " << cursor->getPriority() << endl;
		cout << "New Priority?" << endl;
		cin >> pri;
		cursor->setPriority(pri);
		break;
	case 4:
		cout << "Current Start date: " << cursor->getSdate() << endl;
		cout << "New Date?(Ex:3/4/2012, include slashes)" << endl;
		getline(cin, m, '/');
		getline(cin, d, '/');
		cin >> y;
		cursor->setSdate(stoi(m), stoi(d), stoi(y));
		break;
	case 5:
		cout << "Current End date: " << cursor->getSdate() << endl;
		cout << "New Date?(Ex:3/4/2012, include slashes)" << endl;
		getline(cin, m, '/');
		getline(cin, d, '/');
		cin >> y;
		cursor->setEdate(stoi(m), stoi(d), stoi(y));
		break;
	case 6:
		cout << "\n Which objective? \n";
		listObjectiveName(cursor->head);
		cout << "\n ";
		cin >> pri;
		editObjective(cursor->head, pri);
		break;
	case 7:
		insertNewObjective(cursor, cursor->used);
		break;
	case 8:
		cout << "Choose objective: " << endl;
		removeObjective(head);
		break;
	case 9:
		cout << "Current status: ";
		if (cursor->getStatus() == true)
			cout << "Completed" << endl;
		else
			cout << "Incomplete" << endl;
		cout << "New status?" << endl;
		cin >> c;
		c = toupper(c);
		switch (c)
		{
		case 'Y':
			choice = true;
			cursor->setStatus(choice);
			break;
		default:
			choice = false;
			cursor->setStatus(choice);
			break;
		}
		break;
 
	
	}

}
void editObjective(obj*& head, int j)
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
				cout << "Choose Task" << endl;
				listTaskName(cursor->head);
                cin >> i;
                cursor2 = cursor->head;
                for(int count = 1 ; count !=i && cursor2->link != NULL; cursor2 = cursor2->link)
                    {
                        count++;

                    }
                
                taskEdit(cursor2);
                break;
			case 9:
				insertTask(cursor);
				break;
			case 10:
				cout << "Choose Task" << endl;
				listTaskName(cursor->head);
				removeTask(cursor);
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
						cursor2->setStatus(status);
                        break;
                case 'n':
                case 'N':
                        status = false;
						cursor2->setStatus(status);
                        break;
                default:
                        cout << "must be y or n, defaulting to false" << endl;
                        break;
                }
                break;
                
        }
	
	
	
}

void taskEdit(Task*& cursor2)
{
     string temp;
    int i, d,m,y;
    double time;
    char c;
	bool status;
	cout << "Which aspect would you like to edit?" << endl
		<< "1. Task name" << endl
		<< "2. Task description" << endl
		<< "3. Task time requirement" << endl
		<< "4. Task start date" << endl
		<< "5. Task end date" << endl
		<< "6. Task status" << endl;
	int choice2;
	cin >> choice2;
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
void removeGoal(Goal*& head, Goal*& tail)
{
	int i;
	Goal* cursor = head;
	listGoalName(head);
	cin >> i;

	for (int count = 1; count != (i-1) && cursor->link != NULL; cursor = cursor->link)
	{
		count++;

	}
	if (cursor->link->link == NULL)
	{
		list_remove(cursor);
		tail = cursor;
	}
	else
	{
		list_remove(cursor);
		
	}
}
void removeObjective(Goal*& node)
{
	int i;
	obj* cursor = node->head;
	listObjectiveName(cursor);
	cin >> i;

	for (int count = 1; count != (i - 1) && cursor->link != NULL; cursor = cursor->link)
	{
		count++;

	}
	if (cursor->link->link == NULL)
	{
		node->removeObjective(cursor);
		node->tail = cursor;
	}
	else
	{
		node->removeObjective(cursor);

	}
}
void removeTask(obj*& node)
{
	int i;
	Task* cursor = node->head;
	listTaskName(cursor);
	cin >> i;

	for (int count = 1; count != (i - 1) && cursor->link != NULL; cursor = cursor->link)
	{
		count++;

	}
	if (cursor->link->link == NULL)
	{
		node->removeTask(cursor);
		node->tail = cursor;
	}
	else
	{
		node->removeTask(cursor);

	}
}

void display(Goal* head, int i)
{
	Goal* cursor = head;
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



void write(ofstream& outFile, Goal*& head)
{
	for (Goal* cursor = head; cursor != NULL; cursor = cursor->link)
	{
		cursor->write(outFile);
		if (cursor->link == NULL)
		{
			outFile << "_ ";
			
		}
		else
		{
			outFile << "- ";
		}
	}

}
void read(ifstream& inFile, Goal*& tail, Goal*& head)
{
	
	
	while(!inFile.eof())
	{
		Goal temp;
			temp.read(inFile);
			if (head == NULL && tail == NULL)
			{
				list_head_insert(head, temp);
				tail = head;
			}
			else
				list_tail_insert(tail, temp);

		
	}
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
void displaySmall(Goal*& headptr)
{
	cout << left << setw(15) << "Goal" << setw(15) << "Priority" << " " << setw(15)
		<< "Due Date" << " " << setw(15) << "Status"  << setw(15) /*<< "Objectives" << setw(15)*/ << endl;
	Goal* cursor = headptr;

	for (; cursor != NULL; cursor = cursor->link)
	{
		cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
			<< cursor->getEdate() << " " << setw(15) ;
		if (cursor->getStatus() == false)
			cout << "Incomplete" /*<< setw(15)*/;
		else
			cout << "Complete" /*<< setw(15)*/ ;
	/*	for (obj* cursor2 = cursor->head; cursor2 != NULL; cursor2 = cursor2->link)
		{
			cout << cursor2->getObj() << ", ";

		}*/
		cout << "\n";
	}

}
void sortGoals(Goal*& head)
{
	int menu;
	cout << "Sort by?" << endl;
	cout << "1. Due date(earliest first)" << endl
		<< "2. Priority(Highest priority first)" << endl
		<< "3. Status (complete first)" << endl;
	cin >> menu;
	switch (menu)
	{
	case 1:
		sortDate(head);

		break;
	case 2:
		sortPriority(head);
		break;
	case 3:
		sortStatus(head);
		break;
	default:
		cout << "Invalid entry" << endl;
		break;
	}
}
void sortDate(Goal*& head)
{
	Goal* cursor = head;
	Goal* cursorP = head;
	Goal* cursor2 = head;
	Goal* cursorH = head;
	cursor = cursor->link;
	string mm, dd, yy, date;
	string hm, hd, hy, hdate;
	int pos = 0, pos2 = 0;
	while (cursor != NULL)
	{
		//extracting dates to compare
		//cursor
		date = cursor->getEdate();
		pos = date.find('/');
		mm = date.substr(0, pos );
		date.erase(0, pos+1);
		pos = date.find('/');
		dd = date.substr(0, pos );
		date.erase(0, pos+1);
		yy = date;
		//head pointer
		hdate = head->getEdate();
		pos = hdate.find('/');
		hm = hdate.substr(0, pos - 1);
		date.erase(0, pos);
		pos = hdate.find('/');
		hd = hdate.substr(0, pos - 1);
		date.erase(0, pos);
		hy = hdate;
		//comparing
		if (stoi(yy) < stoi(hy))
		{
			cursor2->link = cursor->link;
			cursor->link = head;
			head = cursor;
			cursor = head->link;
			cursor2 = head;
		}
		else if (stoi(mm) < stoi(hm))
		{
			cursor2->link = cursor->link;
			cursor->link = head;
			head = cursor;
			cursor = head->link;
			cursor2 = head;
		}
		else if (stoi(dd) < stoi(hd))
		{
			cursor2->link = cursor->link;
			cursor->link = head;
			head = cursor;
			cursor = head->link;
			cursor2 = head;
		}
		cursor = cursor->link;
		cursor2 = cursor2->link;
	};

	cursorH = head;
	cursor2 = cursorH->link;
	cursor = cursor2->link;
	cursorP = cursor2;
	while (cursor2 != NULL)
	{
		while (cursor != NULL)
		{
			//extracting dates to compare
			//cursor
			date = cursor->getEdate();
			pos = date.find('/');
			mm = date.substr(0, pos - 1);
			date.erase(0, pos);
			pos = date.find('/');
			dd = date.substr(0, pos - 1);
			date.erase(0, pos);
			yy = date;
			//psuedo head pointer
			hdate = cursor2->getEdate();
			pos = hdate.find('/');
			hm = hdate.substr(0, pos - 1);
			date.erase(0, pos);
			pos = hdate.find('/');
			hd = hdate.substr(0, pos - 1);
			date.erase(0, pos);
			hy = hdate;
			//comparing
			if (yy < hy)
			{
				cursorH->link = cursor;
				cursorP->link = cursor->link;
				cursor->link = cursor2;
				cursor2 = cursor;
				cursorP = cursorH;
			}
			else if (mm < hm)
			{
				cursorH->link = cursor;
				cursorP->link = cursor->link;
				cursor->link = cursor2;
				cursor2 = cursor;
				cursorP = cursorH;
			}
			else if (dd < hd)
			{
				cursorH->link = cursor;
				cursorP->link = cursor->link;
				cursor->link = cursor2;
				cursor2 = cursor;
				cursorP = cursorH;
			}
			cursor = cursor->link;
			cursorP = cursorP->link;
		}
		cursor2 = cursor2->link;
		cursorH = cursorH->link;
		cursor = cursor2->link;
		cursorP = cursor2;

	}
}

void sortPriority(Goal*& head)
{
	
	Goal* cursor = head;
	Goal* cursorP = head;
	Goal* cursor2 = head;
	Goal* cursorH = head;
	cursor = cursor->link;
	
	while (cursor != NULL)
	{
		//extracting dates to compare
		//cursor
		
		//comparing
		if (cursor->getPriority() > head->getPriority())
		{
			cursor2->link = cursor->link;
			cursor->link = head;
			head = cursor;
			cursor = head->link;
			cursor2 = head;
		}
		
		cursor = cursor->link;
		cursor2 = cursor2->link;
	};

	cursorH = head;
	cursor2 = cursorH->link;
	cursor = cursor2->link;
	cursorP = cursor2;
	while (cursor2 != NULL)
	{
		while (cursor != NULL)
		{
				
			//comparing
			if (cursor->getPriority() > cursor2->getPriority())
			{
				cursorH->link = cursor;
				cursorP->link = cursor->link;
				cursor->link = cursor2;
				cursor2 = cursor;
				cursorP = cursorH;
			}
			
			cursor = cursor->link;
			cursorP = cursorP->link;
		}
		cursor2 = cursor2->link;
		cursorH = cursorH->link;
		cursor = cursor2->link;
		cursorP = cursor2;

	}
	

}

void sortStatus(Goal*& head)
{
	Goal* cursor = head;
	Goal* cursorP = head;
	Goal* cursor2 = head;
	Goal* cursorH = head;
	cursor = cursor->link;

	while (cursor != NULL)
	{
		//extracting dates to compare
		//cursor

		//comparing
		if (cursor->getStatus() == true)
		{
			cursor2->link = cursor->link;
			cursor->link = head;
			head = cursor;
			cursor = head->link;
			cursor2 = head;
		}

		cursor = cursor->link;
		cursor2 = cursor2->link;
	};
}
void SDpriority(Goal*& head)
{
	int pri;
	cout << "Enter priority you want to search for: ";
	cin >> pri;
	cout << "\n";
	int i = 0;
	Goal* cursor = head;
	cout << left << setw(3) << " " << setw(15) << "Goal" << setw(15) << "Priority" << " " << setw(15)
		<< "Due Date" << " " << setw(15) << "Status" << endl;
	while (cursor != NULL)
	{
		if (cursor->getPriority() == pri)
		{
			i++;
			//cout << i << ". " << cursor->getName();
			cout << left << i << setw(2) << ". " ;
			cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
				<< cursor->getEdate() << " " << setw(15);
			if (cursor->getStatus() == false)
				cout << "Incomplete" << setw(15);
			else
				cout << "Complete" << setw(15);
		}
		cursor = cursor->link;
	}


}
void SDdate(Goal*& head)
{
	int i = 0, pos = 0;
	string date;
	string mm, dd, yy;
	int m, d, y;
	int sm, sd, sy;
	int em, ed, ey;
	Goal* cursor = head;
	bool search, loop = false;
	cout << "Search is done by due dates" << endl
		<< "Enter starting date of range(format 3/4/2014)" << endl;
	getline(cin, mm, '/');
	getline(cin, dd, '/');
	cin >> yy;
	sm = stoi(mm);
	sd = stoi(dd);
	sy = stoi(yy);
	cout << "Enter ending date of range(format 3/4/2014)" << endl;
	getline(cin, mm, '/');
	getline(cin, dd, '/');
	cin >> yy;
	em = stoi(mm);
	ed = stoi(dd);
	ey = stoi(yy);
	cout << left << setw(3) << " " << setw(15) << "Goal" << setw(15) << "Priority" << " " << setw(15)
		<< "Due Date" << " " << setw(15) << "Status" << endl;
	while (cursor != NULL)
	{
		date = cursor->getEdate();
		pos = date.find('/');
		mm = date.substr(0, pos);
		date.erase(0, pos+1);
		pos = date.find('/');
		dd = date.substr(0, pos);
		date.erase(0, pos+1);
		yy = date;
		m = stoi(mm);
		d = stoi(dd);
		y = stoi(yy);
		if (y < ey && y > sy)
		{
			i++;
			//cout << i << ". " << cursor->getName() << " Due Date: " << cursor->getEdate();
			cout << left << i << setw(2) << ". " ;
			cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
				<< cursor->getEdate() << " " << setw(15);
			if (cursor->getStatus() == false)
				cout << "Incomplete" ;
			else
				cout << "Complete" ;
			cout << "\n";
		}
		else if (y == ey && y > sy)
		{
			if (m < em)
			{
				i++;
				//cout << i << ". " << cursor->getName() << " Due Date: " << cursor->getEdate();
				cout << left << i << setw(2) << ". " ;
				cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
					<< cursor->getEdate() << " " << setw(15);
				if (cursor->getStatus() == false)
					cout << "Incomplete" ;
				else
					cout << "Complete" ;
				cout << "\n";
			}
			else if (m == em)
			{
				if (d <= ed)
				{
					i++;
					//cout << i << ". " << cursor->getName() << " Due Date: " << cursor->getEdate();
					cout << left << i << setw(2) << ". " ;
					cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
						<< cursor->getEdate() << " " << setw(15);
					if (cursor->getStatus() == false)
						cout << "Incomplete" ;
					else
						cout << "Complete" ;
					cout << "\n";
				}
			}
		}
		else if (y < ey && y == sy)
		{
			if (m > sm)
			{
				i++;
				//cout << i << ". " << cursor->getName() << " Due Date: " << cursor->getEdate();
				cout << left << i << setw(2) << ". " ;
				cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
					<< cursor->getEdate() << " " << setw(15);
				if (cursor->getStatus() == false)
					cout << "Incomplete" ;
				else
					cout << "Complete" ;
				cout << "\n";
			}
			else if (m == sm)
			{
				if (d >= ed)
				{
					i++;
					//cout << i << ". " << cursor->getName() << " Due Date: " << cursor->getEdate();
					cout << left << i << setw(2) << ". " ;
					cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
						<< cursor->getEdate() << " " << setw(15);
					if (cursor->getStatus() == false)
						cout << "Incomplete" ;
					else
						cout << "Complete" ;
					cout << "\n";
				}
			}
		}
		else if (y == ey && y == sy)
		{
			if (m > sm && m< em)
			{
				i++;
				//cout << i << ". " << cursor->getName() << " Due Date: " << cursor->getEdate();
				cout << left << i << setw(2) << ". " ;
				cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
					<< cursor->getEdate() << " " << setw(15);
				if (cursor->getStatus() == false)
					cout << "Incomplete" ;
				else
					cout << "Complete" ;
				cout << "\n";
			}
			else if (m == sm && m < em)
			{
				if (d >= sd)
				{
					i++;
					//cout << i << ". " << cursor->getName() << " Due Date: " << cursor->getEdate();
					cout << left << i << setw(2) << ". " ;
					cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
						<< cursor->getEdate() << " " << setw(15);
					if (cursor->getStatus() == false)
						cout << "Incomplete"  ;
					else
						cout << "Complete" ;
					cout << "\n";
				}
			}
			else if (m > sm && m == em)
			{
				if (d <= ed)
				{
					i++;
					//cout << i << ". " << cursor->getName() << " Due Date: " << cursor->getEdate();
					cout << left << i << setw(2) << ". ";
					cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
						<< cursor->getEdate() << " " << setw(15);
					if (cursor->getStatus() == false)
						cout << "Incomplete" ;
					else
						cout << "Complete" ;
					cout << "\n";
				}
			}
			else if (m == sm && m == em)
			{
				if (d >= sd && d <= ed)
				{
					i++;
					//cout << i << ". " << cursor->getName() << " Due Date: " << cursor->getEdate();
					cout << left << i << setw(2) << ". " ;
					cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
						<< cursor->getEdate() << " " << setw(15);
					if (cursor->getStatus() == false)
						cout << "Incomplete" ;
					else
						cout << "Complete" ;
					cout << "\n";
				}
			}
		}
		cursor = cursor->link;
	}

}
void SDstatus(Goal*& head)
{
	int pri, cho;
	int i = 0;
	Goal* cursor = head;
	bool search, loop = true;
	cout << "Search for complete or incomplete?" << endl;
	cout << "1. Complete" << endl
		<< "2. Incomplete" << endl;
	cin >> cho;
	while (loop)
	{
		loop = false;
		switch (cho)
		{
		case 1:
			search = true;
			break;
		case 2:
			search = false;
			break;
		default:
			cout << "Invalid selection" << endl;
			loop = true;
			break;
		}
	}
	cout << "\n";
	//cout << "Names(Please use display function for more information)" << endl;
	cout << left << setw(3) << " " << setw(15) << "Goal" << setw(15) << "Priority" << " " << setw(15)
		<< "Due Date" << " " << setw(15) << "Status" << endl;
	

	
		
		
		cout << "\n";
	while (cursor != NULL)
	{
		if (cursor->getStatus() == search)
		{
			i++;
			cout << left << i << setw(2) << ". " ;
			cout << left << setw(15) << cursor->getName() << setw(15) << cursor->getPriority() << " " << setw(15)
				<< cursor->getEdate() << " " << setw(15);
			if (cursor->getStatus() == false)
				cout << "Incomplete" << setw(15);
			else
				cout << "Complete" << setw(15);
		}
		cursor = cursor->link;
	}

}