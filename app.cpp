#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int control = 10, tpost = 5, fact = 4, whouse = 3, dorm = 3;
int choice, choice2;

// garis nggo nggawe tabel
void Line (int length) {
	for (int i = 0; i <= length; i++) {
		cout <<	"-";
	}
	cout << endl;
}

// nyimpen data Operators
struct Operators {
	string name;
	string skill;
	string position;
	double trust;
	double salary;

	Operators *prev, *next;
} op[100];

// nampilne tabel
void display() {
	int j = 0;
	cout << left << setw(5) << "No." << setw(20) << "Name" << setw(45) << "Skill" << setw(20) << "Position" << setw(10) << right << "Trust" << setw(10) << "Salary" << endl;
	Line(120);
	for (int i = 0; i < 20; i++) {
		if (!op[i].name.empty())
		{
			j++;
			cout << left << setw(5) << j << setw(20) << op[i].name << setw(45) << op[i].skill << setw(20) << op[i].position << right << setw(9) << op[i].trust << "%" << setw(5) << "$" << op[i].salary << endl;
		}		
	}
	Line(120);
}

struct LinkedList {
	Operators* head;
	Operators* tail;

	LinkedList() {
		head = tail = NULL;
	}

	void enqueue(struct Operators q) {
		Operators* newNode = new Operators();
        if (q.name.empty()) {
            return;
        }

        newNode->name = q.name;
        newNode->skill = q.skill;
        newNode->position = q.position;
        newNode->trust = q.trust;
        newNode->salary = q.salary;

		newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode;
	}

	void dequeue() {
		if (head == NULL) {
			cout << "No operators assigned!\n";
		}
		Operators* temp = head;
		head = head->next;
		if (head == NULL) {
			tail = NULL;
		}
		delete temp;
	}

	void printQueue() {
		Operators* temp = head;
		while (temp != NULL) {
			if (temp->next != NULL)
			{
				cout << temp->name << ", ";
			} else
			{
				cout << temp->name;
			}
			temp = temp->next;
		}
	}
};

struct Tree {
	string position;
	Tree* children[5];
	LinkedList* Queue;

	Tree(string value) {
		position = value;
		for (int i = 0; i < 5; i++) {
			children[i] = NULL;
		}
		Queue = NULL;
	}
};

Tree* createNode(string value) {
	return new Tree(value);
}

void addChild(Tree* parent, int index, Tree* child) {
	if (index >= 0 && index < 5) {
		parent->children[index] = child;
	} else {
		cout << "Only 5 buildings maximum.\n";
	}
}

void assign(Tree* parent, struct Operators op[], int choice) {
    int menu;
	string pos;
	cout << "Option :\n";
	Line(120);
	cout << "1. Assign an operator\n";
	cout << "2. Drop an operator\n\n";
	cout << "0. Back";
	Line(120);
	cout << "-> "; cin >> menu;
	if (menu == 0)
	{
		return;
	}
	
	if (menu == 1)
	{
    	if (parent->Queue == NULL) {
    	    parent->Queue = new LinkedList();
    	}
    	Operators temp[10];
    	int tempIndex = 0; 
    	for (int i = 0; i < 10; i++) {
    	    pos = op[i].position;
    	    if ((choice == 0 && pos == "Control Center") ||
    	        (choice == 1 && pos == "Warehouse") ||
    	        (choice == 2 && pos == "Trading Post") ||
    	        (choice == 3 && pos == "Factory") ||
    	        (choice == 4 && pos == "Dormitory")) 
    	    {
    	        temp[tempIndex++] = op[i]; // Simpan data ke array `temp`
    	    }
    	}
    	cout << "\nAvailable Operators :\n";
		int j = 0;
		cout << left << setw(5) << "No." << setw(20) << "Name" << setw(45) << "Skill" << setw(20) << "Position" << setw(10) << right << "Trust" << setw(10) << "Salary" << endl;
		Line(120);
		for (int i = 0; i < tempIndex; i++) {
			if (!temp[i].name.empty())
			{
				j++;
				cout << left << setw(5) << j << setw(20) << temp[i].name << setw(45) << temp[i].skill << setw(20) << temp[i].position << right << setw(9) << temp[i].trust << "%" << setw(5) << "$" << temp[i].salary << endl;
			}		
		}
		Line(120);
    	cout << "Choose -> ";
    	cin >> choice2;
    	if (choice2 < 0 || choice2 > tempIndex) {
    	    cout << "Invalid choice!\n";
    	    return;
    	}
    	parent->Queue->enqueue(temp[choice2-1]);
		cout << "Operator ";
		parent->Queue->printQueue();
		cout << " assigned.";
		for (int i = 0; i < tempIndex; i++) {
    	    if (op[i].name == temp[choice2-1].name) {
    	        op[i].name = "";
    	        op[i].position = "";
    	        op[i].skill = "";
    	        op[i].trust = 0;
    	        op[i].salary = 0;
    	        break;
    	    }
    	}
	}
	if (menu == 2)
	{
		if (parent->Queue == NULL) {
    	    return;
    	}
		cout << "Operator "; 
		parent->Queue->printQueue();
		cout << " dropped.";
		parent->Queue->dequeue();	
	}
	cin.ignore();
	cin.get();
}

void printTree(Tree* root) {
    if (root->Queue == NULL) {
        cout << "\n\tNo operator assigned at " << root->position << ", Please assign an operator.\n";
    }
    if (root->Queue != NULL) {
        root->Queue->printQueue();
        cout << endl;
    }
}

void printIsEmpty(Tree* root) {
	if (root->Queue == NULL) {
		cout << "There are problem in " << root->position << ".\n";
	}
}

// linear sort
void sortName(struct Operators op[]) {
    int size = 20;
	Operators temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (op[j].name.empty() || op[j + 1].name.empty()) 
			{
                continue;
            }
			if (op[j].name > op[j+1].name)
			{
				temp = op[j];
				op[j] = op[j+1];
				op[j+1] = temp;
			}
		}
	}
	cout << "Operators Inforamation - Sort by Name\n\n";
	display();
	cout << "Press any key to back...";
	cin.ignore();
	cin.get();
}

void sortSkill(struct Operators op[]) {
    int size = 20;
	Operators temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (op[j].skill.empty() || op[j + 1].skill.empty()) 
			{
                continue;
            }
			if (op[j].skill > op[j+1].skill)
			{
				temp = op[j];
				op[j] = op[j+1];
				op[j+1] = temp;
			}
		}
	}
	cout << "Operators Information - Sort by Skill\n\n";
	display();
	cout << "Press any key to back...";
	cin.ignore();
	cin.get();
}

void sortPos(struct Operators op[]) {
    int size = 20;
	Operators temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (op[j].position.empty() || op[j + 1].position.empty()) 
			{
                continue;
            }
			if (op[j].position > op[j+1].position)
			{
				temp = op[j];
				op[j] = op[j+1];
				op[j+1] = temp;
			}
		}
	}
	cout << "Operators Information - Sort by Position\n\n";
	display();
	cout << "Press any key to back...";
	cin.ignore();
	cin.get();
}

void sortTrust(struct Operators op[]) {
    int size = 20;
	Operators temp;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (op[j].trust == 0 || op[j + 1].trust == 0) 
			{
                continue;
            }
			if (op[j].trust > op[j+1].trust)
			{
				temp = op[j];
				op[j] = op[j+1];
				op[j+1] = temp;
			}
		}
	}
	cout << "Operators Information - Sort by Trust\n\n";
	display();
	cout << "Press any key to back...";
	cin.ignore();
	cin.get();
}

void sortSalary(struct Operators op[]) {
    int size = 20;
    Operators temp;
    for (int i = 0; i < size - 1; i++) 
	{
        for (int j = 0; j < size - i - 1; j++) 
		{
            if (op[j].salary == 0 || op[j + 1].salary == 0) 
			{
                continue;
            }
            if (op[j].salary > op[j + 1].salary) 
			{
                temp = op[j];
                op[j] = op[j + 1];
                op[j + 1] = temp;
            }
        }
    }
	cout << "Operators Information - Sort by Salary\n\n";
	display();
	cout << "Press any key to back...";
	cin.ignore();
	cin.get();
}


void search(struct Operators op[]) {
	int size = 20;
	string temp;

	string search;
	cout << "Operator Search\n\n";
	cout << "Enter operator name : ";
	cin >> search;

	for (char &c : search)
	{
		c = tolower(c);
	}

	cout << "\nFound matches:\n";
	bool found = false;

	for (int i = 0; i <= size; i++)
	{
		string temp = op[i].name;
		for (char &c : temp)
		{
			c = tolower(c); 
		}
		if (temp == search)
		{
			cout << left << setw(5) << "No." << setw(20) << "Name" << setw(45) << "Skill" << setw(20) << "Position" << setw(10) << right << "Trust" << setw(10) << "Salary" << endl;
			Line(120);
			cout << left << setw(5) << i+1 << setw(20) << op[i].name << setw(45) << op[i].skill << setw(20) << op[i].position << right << setw(9) << op[i].trust << "%" << setw(5) << "$" << op[i].salary << endl;	
			found = true;
		}
	}
	cout << "Press any key to back...";
	cin.ignore();
	cin.get();

	if (!found)
	{
		cout << search << " not found.";
	}
}

void recruit(struct Operators op[]) {
	double pos;
	for (int i = 0; i < 20; i++)
	{
		if (op[i].name.empty())
		{
			cout << "+-------------------------------------------+\n";
            cout << "|               Register Operator           |\n";
            cout << "+-------------------------------------------+\n";
            cin.ignore();
            cout << "Operator Name      : "; getline(cin, op[i].name);
            cout << "Operator Skill     : "; getline(cin, op[i].skill);
            cout << "Operator Position\n";
			cout << "Choose : \n";
			cout << "1 - Control Center\n2 - Warehouse\n3 - Trading Post\n4 - Factory\n5 - Dormitory\n";
			cout << "-> "; 
			cin >> choice;
			if (choice == 1)
			{
				op[i].position = "Control Center";
			}
			if (choice == 2)
			{
				op[i].position = "Warehouse";
			}
			if (choice == 3)
			{
				op[i].position = "Trading Post";
			}
			if (choice == 4)
			{
				op[i].position = "Factory";
			}
			if (choice == 5)
			{
				op[i].position = "Dormitory";
			}
			op[i].trust = 10;
            cout << "Trust Points       : " << op[i].trust << "\n"; 
			if (op[i].position == "Control Center")
			{
				pos = control;
			}
			if (op[i].position == "Warehouse")
			{
				pos = whouse;
			}
			if (op[i].position == "Trading Post")
			{
				pos = tpost;
			}
			if (op[i].position == "Factory")
			{
				pos = fact;
			}
			if (op[i].position == "Dormitory")
			{
				pos = dorm;
			}
			op[i].salary = op[i].trust * pos;
			cout << "Salary				: " << op[i].salary << "\n"; 
            break;
		}
	}
	cout << "Operators Successfully Added.\n\n";
	display();
	cout << "Press any key to back...";
	cin.ignore();
	cin.get();
}

void erase(struct Operators op[]) {
	int choice;
	cout << "Which operator you want to delete?\n\n";
	display();
	cout << "-> "; cin >> choice;
	for (int i = 0; i < 20; i++)
	{
		if (op[i+1].name.empty())
		{
			op[choice-1].name = "";
			op[choice-1].skill = "";
			op[choice-1].position = "";
			op[choice-1].trust = 0;
			break;
		}
	}
	cout << "Press any key to back...";
	cin.ignore();
	cin.get();
}


int main()
{
	// operator database
	op[0].name = "Amiya";
	op[0].skill = "Boost all operators stamina";
	op[0].position = "Control Center";
	op[0].trust = 150;
	op[0].salary = control * op[0].trust;

	op[1].name = "Chen";
	op[1].skill = "Boost factory operator effectiveness";
	op[1].position = "Control Center";
	op[1].trust = 100;
	op[1].salary = control * op[1].trust;

	op[2].name = "Texas";
	op[2].skill = "Trading post effectiveness +30%";
	op[2].position = "Trading Post";
	op[2].trust = 80;
	op[2].salary = fact * op[2].trust;

	op[3].name = "Exusiai";
	op[3].skill = "Trading post operator stamina +30%";
	op[3].position = "Trading Post";
	op[3].trust = 120;
	op[3].salary = fact * op[3].trust;

	op[4].name = "Sora";
	op[4].skill = "Operator energy restore +50%";
	op[4].position = "Dormitory";
	op[4].trust = 40;
	op[4].salary = fact * op[4].trust;

	op[5].name = "Matterhorn";
	op[5].skill = "Warehouse capacity +30%";
	op[5].position = "Warehouse";
	op[5].trust = 110;
	op[5].salary = whouse * op[5].trust;

	op[6].name = "Haze";
	op[6].skill = "Gold bar production speed +40%";
	op[6].position = "Factory";
	op[6].trust = 150;
	op[6].salary = fact * op[6].trust;

	op[7].name = "Gummy";
	op[7].skill = "Trading post trade limit +4";
	op[7].position = "Trading Post";
	op[7].trust = 100;
	op[7].salary = tpost * op[7].trust;

	op[8].name = "Eyja";
	op[8].skill = "Instantly restore an operator stamina";
	op[8].position = "Dormitory";
	op[8].trust = 140;
	op[8].salary = dorm * op[8].trust;

	op[9].name = "Jessica";
	op[9].skill = "Any production speed +30%";
	op[9].position = "Factory";
	op[9].trust = 50;
	op[9].salary = fact * op[9].trust;

	// tree start
	Tree* root = createNode("AOMS");

    addChild(root, 0, createNode("Control Center"));
    addChild(root, 1, createNode("Warehouse"));
    addChild(root, 2, createNode("Trading Post"));
    addChild(root, 3, createNode("Factory"));
    addChild(root, 4, createNode("Dormitory"));

    Tree* controlCenter = root->children[0];
	Tree* warehouse = root->children[1];
	Tree* tradingPost = root->children[2];
	Tree* factory = root->children[3];
	Tree* dormitory = root->children[4];
    
	// main menu
	while (true) {
		system("cls");
		Line(50);
		cout << "AOMS\n";
		cout << "Arknights Operator Management System\n";
		Line(50);
		cout << "Main Menu\n";
		cout << "1. Base Overview\n";
		cout << "2. Operators Assignment\n";
		cout << "3. Products and Trades\n";
		cout << "4. Operators Information\n";
		cout << "\n0. Exit\n";
		Line(50);
		cout << "-> "; cin >> choice;
		if (choice == 0) {
			cout << "Closing AOMS...\n";
			return 0;
		} 
		if (choice == 1)
		{
			system("cls");
			cout << "+-------------------------------------------+\n";
			cout << "|                  Base Overview            |\n";
			cout << "+-------------------------------------------+\n";
			printIsEmpty(controlCenter);
			printIsEmpty(warehouse);
			printIsEmpty(tradingPost);
			printIsEmpty(factory);
			printIsEmpty(dormitory);
   			cout << "a. Control Center\n";
			cout << "	Controlling all buildings\n";
			cout << "   	Operator currently assigned : "; printTree(controlCenter);
			cout << "b. Warehouse\n";
			cout << "	Managing supplies\n";
			cout << "	Operator currently assigned : "; printTree(warehouse);
			cout << "c. Trading Post\n";
			cout << "	Selling products\n";
			cout << "	Operator currently assigned : "; printTree(tradingPost);
			cout << "d. Factory\n";
			cout << "	Production center\n";
			cout << "	Operator currently assigned : "; printTree(factory);
			cout << "e. Dormitory\n";
			cout << "	Restoring Operators energy\n";
			cout << "	Operator currently assigned : "; printTree(dormitory);
			Line(100);
			cout << "0. Back to main menu\n";
			cout << "1. Go to Operator Assignment\n";
			Line(100);
			cout << "-> "; cin >> choice; 
			if (choice == 1) {
				goto dua;
			}
		} 
		if (choice == 2)
		{
			dua:
			while (choice != 0)
			{
				system("cls");
				cout << "- Operator Assignment -\n\n";
				cout << "Option :\n";
				Line(50);
				cout << "1. Control Center\n";
				cout << "2. Warehouse\n";
				cout << "3. Trading Post\n";
				cout << "4. Factory\n";
				cout << "5. Dormitory\n\n";
				cout << "0. Back to Main Menu\n";
				Line(50);
				cout << "-> "; cin >> choice;
				if (choice == 1)
				{
					cout << "+-------------------------------------------+\n";
            		cout << "|                  Control Center           |\n";
            		cout << "+-------------------------------------------+\n";
					cout << "Assigned operator : ";
					printTree(controlCenter);
					assign(controlCenter, op, 0); 
				}
				if (choice == 2)
				{
					cout << "+-------------------------------------------+\n";
            		cout << "|                    Warehouse              |\n";
            		cout << "+-------------------------------------------+\n";
					cout << "Assigned operator : ";
					printTree(warehouse);
					assign(warehouse, op, 1);
				}
				if (choice == 3)
				{
					cout << "+-------------------------------------------+\n";
            		cout << "|                   Trading Post            |\n";
            		cout << "+-------------------------------------------+\n";
					cout << "Assigned operator : ";
					printTree(tradingPost);
					assign(tradingPost, op, 2);
				}
				if (choice == 4)
				{
					cout << "+-------------------------------------------+\n";
            		cout << "|                      Factory              |\n";
            		cout << "+-------------------------------------------+\n";
					cout << "Assigned operator : ";
					printTree(factory);
					assign(factory, op, 3);
				}
				if (choice == 5)
				{
					cout << "+-------------------------------------------+\n";
            		cout << "|                   Dormitory               |\n";
            		cout << "+-------------------------------------------+\n";
					cout << "Assigned operator : ";
					printTree(dormitory);
					assign(dormitory, op, 4);	
				}
			}
		}
		if (choice == 3)
		{
			cout << "- Products -\n\n";
			cout << "tabel";
		}
		if (choice == 4) {
			while(choice != 0) {
				system("cls");
				Line(80);
				cout << "\n- Operators Information -\n\n";
				Line(80);
				cout << "Option :\n";
				cout << "1. Sort by Name\n";
				cout << "2. Sort by Skill\n";
				cout << "3. Sort by Position\n";
				cout << "4. Sort by Trust\n";
				cout << "5. Sort by Salary\n\n";
				cout << "6. Search operator\n";
				cout << "7. Register operator\n";
				cout << "8. Delete operator\n\n";
				cout << "0. Back to main menu\n";
				Line(80);
				cout << "-> "; cin >> choice;

				if (choice == 1)
				{
					sortName(op);
				}
				if (choice == 2)
				{
					sortSkill(op);
				}
				if (choice == 3)
				{
					sortPos(op);
				}
				if (choice == 4)
				{
					sortTrust(op);
				}
				if (choice == 5)
				{
					sortSalary(op);
				}
				if (choice == 6)
				{
					search(op);
				}
				if (choice == 7)
				{
					recruit(op);
				}
				if (choice == 8)
				{
					erase(op);
				}				
			}
		}
		 
		else {
			cout << "Invalid input.";
		}
	}
	return 0;
}