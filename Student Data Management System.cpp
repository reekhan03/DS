//Student Data Management System


#include <string>
#include <limits>
#include <iostream>
#include <conio.h>
using namespace std;
//BST with AVL
struct node //the structure for representing tree nodes 
{
	int key; //the key value which will be used to sort
	unsigned char height;
	node* left;
	node* right;
	string Name;
	string Subject;
	double Marks;
	int year;
	node(int k, string fn, string course, double gpa, int s_year)
	{
		this->key = k;
		this->left = this->right = 0;
		this->height = 1;
		this->Name = fn;
		this->Subject = course;
		this->Marks = gpa;
		this->year = s_year;
	}

	void update_info(string fn, string course, double gpa, int s_year)
	{
		this->Name = fn;
		this->Subject = course;
		this->Marks = gpa;
		this->year = s_year;
	}

	void print()
	{
		cout << "ID number:" << this->key << endl;
		cout << "Name of the student:" << this->Name << endl;
		cout << "Course subject:" << this->Subject << endl;
		cout << "GPA mark:" << this->Marks << endl;
		cout << "Year of the student:" << this->year << endl;
	}
};

unsigned char height(node* p)
{
	return p ? p->height : 0;
};

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
};

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
};

node* rotateright(node* p) //the right rotation round p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
};

node* rotateleft(node* q) //the left rotation round q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
};

node* balance(node* p) //p node balance
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; //no balance needed
};

node* insert(node* p, int k, string fn, string course, double gpa, int s_year) //k key insertion in the tree with p root  
{
	if (!p)
	{
		return new node(k, fn, course, gpa, s_year);
	}
	if (k < p->key)
		p->left = insert(p->left, k, fn, course, gpa, s_year);
	else
		p->right = insert(p->right, k, fn, course, gpa, s_year);
	return balance(p);
};

node* findmin(node* p) //searching the node with the minimal key in p tree  
{
	return p->left ? findmin(p->left) : p;
};

node* removemin(node* p) //deleting the node with the minimal key from p tree 
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
};

node* remove(node* p, int k) //k key deletion from p tree
{
	if (!p)
	{
		cout << "There is no student with the ID: " << k << endl;
		return 0;
	}
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		cout << "The recorded data is deleted successfully." << endl;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

node* search(node* p, int k) //k key search in the tree with p root  
{
	if (!p)
	{
		cout << "There is no student with the ID: " << k << endl;
		return 0;//if there is no any node whith following key it will return 0
	}
	if (k < p->key)
		return search(p->left, k);
	else if (k > p->key)
		return search(p->right, k);
	else //k == p->key
	{
		return p;
	}
};

node* update(node* p, int k, string fn, string course, double gpa, int s_year) //k key update in the tree with p root  
{
	if (!p)
	{
		cout << "There is no student with the ID: " << k << endl;
		return 0;
	}
	if (k < p->key)
		return update(p->left, k, fn, course, gpa, s_year);
	else if (k > p->key)
		return update(p->right, k, fn, course, gpa, s_year);
	else //k == p->key 
	{
		p->update_info(fn, course, gpa, s_year);
		cout << "The data is updated successfully." << endl;
		return p;
	} //if there is no any node whith following key it will return 0
};

void inOrder(node* p)
{
	if (p != NULL)
	{
		inOrder(p->left);
		p->print();
		cout << endl << "========================" << endl << endl;
		inOrder(p->right);
	}
}

int main() {
	//Usage
	//Node is element of the tree, for using avladded new property of height
	//User comands only 2, all others will be done automatic
	//1) insert (node p, int k) where k is the value which u want to enter and p is the root node, if p is False, then in will make K as root node
	//2) remove (node p, int k) where k is the value which u want to enter and p is the root node, if tree doesn't exist it will return 0
	string course_subject;
	string full_name;
	char enter;
	int id_number;
	double gpa_mark;
	int student_year;
	int choice;
	node* bst = NULL;
	node* result = NULL;
	int temp = 0;
	do {
		temp = 0;
		cout << "\n\t\t\t\t\t\tStudent Data Management System\n";
		cout << "\nWhich of these operations below do you want to perform? Select the option number." << endl;
		cout << "\n\tPress" << endl;
		cout << "\t\t\t1. Create a new student data record." << endl;
		cout << "\t\t\t2. Delete a student data record." << endl;
		cout << "\t\t\t3. Search a student data record by unique ID number." << endl;
		cout << "\t\t\t4. Show all available students data record." << endl;
		cout << "\t\t\t5. Update the data of student by his/her ID number." << endl;
		cout << "\t\t\t0. Exit program." << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			exit(0);
			break;
		case 1:
			while (true)
			{
				cout << "Enter year of the student:\n";
				cin >> student_year;
				if (!cin)
				{
					cout << "Enter again! Year consists of only integer numbers." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else if (student_year <= 0 || student_year >= 5)
				{
					cout << "Year ranges between 1 to 4" << endl;
				}
				else break;
			}
			cout << "Enter full name of a student:\n";
			while (temp < 2)
			{
				getline(cin, full_name);
				temp++;
			}
			while (true)
			{
				cout << "Enter ID number of a student:\n";
				cin >> id_number;
				if (!cin)
				{
					cout << "Enter again! ID consists of only integer numbers." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else break;
			}
			cout << "Enter course subject of a student:\n";
			temp = 0;
			while (temp < 2)
			{
				getline(cin, course_subject);
				temp++;
			}
			while (true)
			{
				cout << "Enter subject GPA mark of a student:\n";
				cin >> gpa_mark;
				if (!cin)
				{
					cout << "Enter again! Grade consists of only numbers." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else if (gpa_mark < 0 || gpa_mark > 100)
				{
					cout << "Grade must be between 0 and 100." << endl;
				}
				else break;
			}
			bst = insert(bst, id_number, full_name, course_subject, gpa_mark, student_year);
			cout << "Recorded data is inserted successfully." << endl;
			cout << "Please press enter to continue:";
			_getch();
			system("cls");
			break;
		case 2:
			while (true)
			{
				cout << "Enter ID number of the student whose data you want to delete\n";
				cin >> id_number;
				if (!cin)
				{
					cout << "Enter again! ID consists of only integer numbers." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else break;
			}
			bst = remove(bst, id_number);
			cout << "Please press enter to continue:";
			_getch();
			system("cls");
			break;
		case 3:
			while (true)
			{
				cout << "Enter ID number of the student whose data you want to search\n";
				cin >> id_number;
				if (!cin)
				{
					cout << "Enter again! ID consists of only integer numbers." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else break;
			}
			result = search(bst, id_number);
			if (result != 0) {
				result->print();
			}
			else
				cout << "No recorded data." << endl;
			result = NULL;
			cout << "Please press enter to continue:";
			_getch();
			system("cls");
			break;
		case 4:
			inOrder(bst);
			cout << "Please press enter to continue:";
			_getch();
			system("cls");
			break;
		case 5:
			while (true)
			{
				cout << "Enter the ID of the student whose data you want to update." << endl;
				cin >> id_number;
				if (!cin)
				{
					cout << "Enter again! ID consists of only integer numbers." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else break;
			}
			cout << "Now enter new name of the student:" << endl;
			temp = 0;
			while (temp < 2)
			{
				getline(cin, full_name);
				temp++;
			}
			while (true)
			{
				cout << "Now enter year of the student:\n";
				cin >> student_year;
				if (!cin)
				{
					cout << "Enter again! Year consists of only integer numbers." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else if (student_year <= 0 || student_year >= 5)
				{
					cout << "Year ranges between 1 to 4" << endl;
				}
				else break;
			}
			cout << "Now enter new subject to replace the previous:" << endl;
			temp = 0;
			while (temp < 2)
			{
				getline(cin, course_subject);
				temp++;
			}
			while (true)
			{
				cout << "Now enter new grade of the course subject:" << endl;
				cin >> gpa_mark;
				if (!cin)
				{
					cout << "Enter again! Grade consists of only numbers." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				else if (gpa_mark < 0 || gpa_mark > 100)
				{
					cout << "Grade must be between 0 and 100." << endl;
				}
				else break;
			}
			update(bst, id_number, full_name, course_subject, gpa_mark, student_year);
			cout << "Please press enter to continue:";
			_getch();
			system("cls");
			break;
		default:
			cout << "Enter proper number option." << endl;
			break;
		}
	} while (choice != 0);
	system("pause");
	return 0;
}