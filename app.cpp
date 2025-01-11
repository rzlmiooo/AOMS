// changelog : display() added parameter, finalizing menu no 4, 

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int control = 10, tpost = 5, fact = 4, whouse = 3, dorm = 3;
int choice, choice2;


// garis tabel
void Line (int length) {
	for (int i = 0; i <= length; i++) {
		cout <<	"-";
	}
	cout << endl;
}

// data Operators
struct Operators {
	string name;
	string skill;
	string position;
	double trust;
	double salary;

	Operators *prev, *next;
} op[100];

// nampilne tabel
void display(struct Operators op[]) {
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

struct Queue {
	Operators* head;
	Operators* tail;

	Queue() {
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

	// void queueIsFUll(Tree* root) {
	// 	if (head == NULL) {
	// 		cout << "No operators assigned!\n";
	// 	} else {
	// 		cout << "";
	// 	}
		
	// }

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

	void printQueueTable() {
		Operators* temp = head;
		while (temp != NULL) {
			cout << left << setw(5) << "No." << setw(20) << "Name" << setw(45) << "Skill" << setw(20) << "Position" << setw(10) << right << "Trust" << setw(10) << "Salary" << endl;
			Line(120);
			for (int i = 0; i < 20; i++) {
				if (!temp->name.empty())
				{
					cout << left << setw(5) << i+1 << setw(20) << temp->name << setw(45) << temp->skill << setw(20) << temp->position << right << setw(9) << temp->trust << "%" << setw(5) << "$" << temp->salary << endl;
					temp = temp->next;
				}		
			}
			Line(120);
			cin.ignore();
			cin.get();
		}
	}
};

struct Tree {
	string position;
	Tree* children[5];
	Queue* childQueue;

	Tree(string value) {
		position = value;
		for (int i = 0; i < 5; i++) {
			children[i] = NULL;
		}
		childQueue = NULL;
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

void addSubChild(Tree* parent, struct Operators op[], int choice) {
    string pos;
	if (parent->childQueue == NULL) {
		parent->childQueue = new Queue();
	}
    Operators temp[10], q;
	for (int i = 0; i < 10; i++) {
    	pos = op[i].position;
		if (choice == 0) {
    	    if (pos == "Control Center") {
    	        temp[i] = op[i];
    		}
    	}
		if (choice == 1) {
    	    if (pos == "Warehouse") {
    	        temp[i] = op[i];
    		}
    	}
		if (choice == 2) {
    	    if (pos == "Trading Post") {
    	        temp[i] = op[i];
    		}
    	}
		if (choice == 3) {
    	    if (pos == "Factory") {
    	        temp[i] = op[i];
    		}
    	}
		if (choice == 4) {
    	    if (pos == "Dormitory") {
    	        temp[i] = op[i];
    		}
    	}	
	}
    for (int i = 0; i < 10; i++) {
        q = temp[i];
	    parent->childQueue->enqueue(q);
    }    
}

void assign(Tree* parent, struct Operators op[], int choice) {
	string pos;
	if (parent->childQueue == NULL) {
		parent->childQueue = new Queue();
	}
    Operators temp[10], q;
	for (int i = 0; i < 10; i++) {
    	pos = op[i].position;
		if (choice == 0) {
    	    if (pos == "Control Center") {
    	        temp[i] = op[i];
    		}
    	}
		if (choice == 1) {
    	    if (pos == "Warehouse") {
    	        temp[i] = op[i];
    		}
    	}
		if (choice == 2) {
    	    if (pos == "Trading Post") {
    	        temp[i] = op[i];
    		}
    	}
		if (choice == 3) {
    	    if (pos == "Factory") {
    	        temp[i] = op[i];
    		}
    	}
		if (choice == 4) {
    	    if (pos == "Dormitory") {
    	        temp[i] = op[i];
    		}
    	}	
	}
	display(temp);
	cout << "Choose -> "; cin >> choice2;
    q = temp[choice2];
	parent->childQueue->enqueue(q);
}


void printTree(Tree* root) {
    if (root->childQueue == NULL) {
        cout << "\n\tWARNING! No operator assigned at " << root->position << ", Please assign an operator.\n";
    }
    if (root->childQueue != NULL) {
        root->childQueue->printQueue();
        cout << endl;
    }
}

void printBaseIsEmpty(Tree* root) {
	if (root->childQueue == NULL) {
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
}


void search(struct Operators op[]) {
	int size = 20;
	string temp;

	string search;
	cout << "Enter word to Search: ";
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
}

void erase(struct Operators op[], int choice) {
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

    // addSubChild(controlCenter, op, 0);
	// addSubChild(warehouse, op, 1);
	// addSubChild(tradingPost, op, 2);
	// addSubChild(factory, op, 3);
	// addSubChild(dormitory, op, 4);
    
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
			Line(100);
			cout << "\nBase Overview\n\n";
    		Line(100);
			printBaseIsEmpty(controlCenter);
			printBaseIsEmpty(warehouse);
			printBaseIsEmpty(tradingPost);
			printBaseIsEmpty(factory);
			printBaseIsEmpty(dormitory);

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
					cout << "Currently assigned operators : "; printTree(controlCenter);
					assign(controlCenter, op, 0); 
					cin.ignore();
					cin.get();
				}
				if (choice == 2)
				{
					cout << "Currently assigned operators : "; printTree(warehouse);
					assign(warehouse, op, 1);
					cin.ignore();
					cin.get();
				}
				if (choice == 3)
				{
					cout << "Currently assigned operators : "; printTree(tradingPost);
					assign(tradingPost, op, 2);
					cin.ignore();
					cin.get();
				}
				if (choice == 4)
				{
					cout << "Currently assigned operators : "; printTree(factory);
					assign(factory, op, 3);
					cin.ignore();
					cin.get();
				}
				if (choice == 5)
				{
					cout << "Currently assigned operators : "; printTree(dormitory);
					assign(dormitory, op, 4);
					cin.ignore();
					cin.get();	
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
					cout << "Operators Inforamation - Sort by Name\n\n";
					display(op);
					cout << "Press any key to back...";
					cin.ignore();
					cin.get();
				}
				if (choice == 2)
				{
					sortSkill(op);
					cout << "Operators Information - Sort by Skill\n\n";
					display(op);
					cout << "Press any key to back...";
					cin.ignore();
					cin.get();
				}

				if (choice == 3)
				{
					sortPos(op);
					cout << "Operators Information - Sort by Position\n\n";
					display(op);
					cout << "Press any key to back...";
					cin.ignore();
					cin.get();
				}
				if (choice == 4)
				{
					sortTrust(op);
					cout << "Operators Information - Sort by Trust\n\n";
					display(op);
					cout << "Press any key to back...";
					cin.ignore();
					cin.get();
				}
				if (choice == 5)
				{
					sortSalary(op);
					cout << "Operators Information - Sort by Salary\n\n";
					display(op);
					cout << "Press any key to back...";
					cin.ignore();
					cin.get();
				}
				if (choice == 6)
				{
					cout << "Operator Search\n\n";
					search(op);
					cout << "Press any key to back...";
					cin.ignore();
					cin.get();
				}
				if (choice == 7)
				{
					recruit(op);
					cout << "Operators Overview - Sort by Name\n\n";
					display(op);
					cout << "Press any key to back...";
					cin.ignore();
					cin.get();
				}
				if (choice == 8)
				{
					cout << "Which operator you want to delete?\n\n";
					display(op);
					cout << "-> "; cin >> choice;
					erase(op, choice);
					cout << "Press any key to back...";
					cin.ignore();
					cin.get();
				}				
			}
		}
		 
		else {
			cout << "Invalid input.";
		}
	}
}