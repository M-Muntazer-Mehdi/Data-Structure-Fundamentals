#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<ctime>
#include<Windows.h>
#include"Header.h"

using namespace std;
//AVL implimentation
int  AVL_tree::height(nodes* temp)
{
	if (temp == NULL)
	{
		return -1;
	}
	else
	{
		int ldepth = height(temp->left);
		int rdepth = height(temp->right);
		if (ldepth > rdepth)
		{
			return ldepth + 1;
		}
		else
		{
			return rdepth + 1;
		}
	}
}

int AVL_tree::balancefactors(nodes* temp)
{
	if (temp == NULL)
	{
		return 0;
	}
	else
	{
		return height(temp->left) - height(temp->right);
	}
}

nodes* AVL_tree::rightrotate(nodes* temp)
{
	nodes* temp1 = temp->left;
	nodes* temp2 = temp1->right;
	temp1->right = temp;
	temp->left = temp2;
	return temp1;
}

nodes* AVL_tree::leftrotate(nodes* temp)
{
	nodes* temp1 = temp->right;
	nodes* temp2 = temp1->left;
	temp1->left = temp;
	temp->right = temp2;
	return temp1;
}

nodes* AVL_tree::insert(nodes* node1, int data1, string Name)
{
	nodes* newnode = new nodes;
	newnode->seat = data1;
	newnode->name = Name;
	newnode->left = NULL;
	newnode->right = NULL;
	nodes* temp = node1;
	if (root == NULL)
	{
		temp = newnode;
		root = temp;
		return temp;
	}
	else
	{
		while (temp != NULL)
		{
			if (temp->seat < data1)
			{
				if (temp->right == NULL)
				{
					temp->right = newnode;
					break;
				}
				temp = temp->right;
			}
			else if (temp->seat > data1)
			{
				if (temp->left == NULL)
				{
					temp->left = newnode;
					break;
				}
				temp = temp->left;
			}
		}
	}
	int balancefactor = balancefactors(temp);
	if (balancefactor > 1)
	{
		if (data1 < temp->left->seat)
		{
			return rightrotate(temp);
		}
		else if (data1 > temp->left->seat)
		{
			temp->left = leftrotate(temp->left);
			return rightrotate(temp);
		}
	}
	if (balancefactor < -1)
	{
		if (data1 > temp->right->seat)
		{
			return leftrotate(temp);
		}
		else if (data1 < temp->right->seat)
		{
			temp->right = rightrotate(temp->right);
			return leftrotate(temp);
		}
	}
	seatsAvail--;
	return node1;
}

nodes* AVL_tree::deletenode(nodes* node1, int data1)
{
	nodes* temp;
	if (node1 == NULL)
	{
		return node1;
	}
	else if (data1 < node1->seat)
	{
		node1->left = deletenode(node1->left, data1);
	}
	else if (data1 > node1->seat)
	{
		node1->right = deletenode(node1->right, data1);
	}
	else
	{
		if (node1->right == NULL)
		{
			temp = node1;
			node1 = node1->left;
			delete temp;
		}
		else if (node1->left == NULL)
		{
			temp = node1;
			node1 = node1->right;
			delete temp;
		}
		else
		{
			temp = node1->right;
			while (temp->left)
			{
				temp = temp->left;
			}
			temp->left = node1->left;
			temp = node1;
			node1 = node1->right;
			delete temp;
		}
	}
	int balancefactor = balancefactors(node1);
	if (balancefactor > 1)
	{
		if (balancefactors(node1->left) >= 0)
		{
			return rightrotate(node1);
		}
		else
		{
			node1->left = leftrotate(node1->left);
			return rightrotate(node1);
		}
	}
	else if (balancefactor < -1)
	{
		if (balancefactors(node1->right) <= 0)
		{
			return leftrotate(node1);
		}
		else
		{
			node1->right = rightrotate(node1->right);
			return leftrotate(node1);
		}
	}
	seatsAvail++;
	return node1;
}

void AVL_tree::display(nodes* temp)
{
	if (temp != NULL)
	{
		display(temp->left);
		if (temp->seat < 10)
			cout << "|" << setw(10) << left << temp->name << "|" << setw(3) << " " << temp->seat << setw(3) << " " << "|" << endl;
		else
			cout << "|" << setw(10) << left << temp->name << "|" << setw(3) << " " << temp->seat << setw(2) << " " << "|" << endl;
		display(temp->right);
	}
}

void AVL_tree::inorder(nodes* temp)
{
	if (temp != NULL)
	{
		display(temp->left);
		EnQueue(temp->seat);
		display(temp->right);
	}
}

bool AVL_tree::search(int key) {
	nodes* temp = new nodes;
	temp = root;
	if (temp == NULL)
		return false;	//tree is empty / node not found
	else {
		bool loop = true;
		do {
			if (temp->seat == key)
				return true;
			else {
				if (key > temp->seat)
					if (temp->right != NULL)
						temp = temp->right;
					else
						loop = false;
				else if (key < temp->seat)
					if (temp->left != NULL)
						temp = temp->left;
					else
						loop = false;
			}
		} while (loop);
	}
	return false;
}

nodes* AVL_tree::ret_root() {
	cout<<root->seat<<endl;
	return root;
}

int AVL_tree::avail() {
	return seatsAvail;
}

void AVL_tree::EnQueue(int data1)
{
	node* newnode = new node;
	newnode->data = data1;
	newnode->next = NULL;
	if (front == NULL)
	{
		front = newnode;
		rear = newnode;
	}
	else
	{
		rear->next = newnode;
		rear = newnode;
	}
}

void AVL_tree::DeQueue()
{
	int value;
	node* temp = front;
	value = temp->data;
	if (front == rear)
	{
		front = NULL;
		rear = NULL;
		delete temp;
		temp = NULL;
	}
	else
	{
		front = front->next;
		delete temp;
		temp = NULL;
	}
	cout << "Popped value is : " << value << endl;
}



//Program

void AVL_tree::bus(int number) {
	node* temp = front;
	while (temp != rear->next)
	{
		DeQueue();
		temp = temp->next;
	}
	HANDLE colors = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i <= 4; i++)
	{
		cout << " __";
	}
	cout << endl;
	cout << "|  " << "  ";
	for (int a = 4; a >= 1; a--)
	{
		if (a == 1)
		{
			cout << "|  ";
		}
		else
		{
			cout << "   ";
		}
		cout << "  ";
		SetConsoleTextAttribute(colors, 7);
	}
	cout << "|  " << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 0 || i == 4)
		{
			cout << "|__";
		}
		else
		{
			if (i == 2)
			{
				cout << "     ";
			}
			else
			{
				cout << " __";
			}
		}
	}
	cout << "|" << endl;
	for (int a = 4; a >= 1; a--)
	{
		cout << "|  ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 3)
			{
				cout << "  " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 3)
			{
				cout << "  " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|  " << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 8; a >= 5; a--)
	{
		cout << "|  ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 7)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 7)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 12; a >= 9; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 11)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				if (a == 9)
				{
					cout << " " << a << " ";
				}
				else
				{
					cout << a << " ";
				}
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 11)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				if (a == 9)
				{
					cout << " " << a << " ";
				}
				else
				{
					cout << a << " ";
				}
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 16; a >= 13; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 15)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 15)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 20; a >= 17; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 19)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 19)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 24; a >= 21; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 23)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 23)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 28; a >= 25; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 27)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 27)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 32; a >= 29; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 31)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 31)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 36; a >= 33; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 35)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 35)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 40; a >= 37; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 39)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 39)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		if (i == 2)
		{
			cout << "|    ";
		}
		else
		{
			cout << "|__";
		}
	}
	cout << "|" << endl;
	for (int a = 44; a >= 41; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			if (a == 43)
			{
				cout << a << " ";
				SetConsoleTextAttribute(colors, 7);
				cout << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			if (a == 43)
			{
				cout << a << " " << "|  " << "  ";
			}
			else
			{
				cout << a << " ";
			}
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		cout << "|__";
	}
	cout << "|" << endl;
	for (int a = 49; a >= 45; a--)
	{
		cout << "| ";
		if (a == number)
		{
			SetConsoleTextAttribute(colors, 12);
			cout << a << " ";
			SetConsoleTextAttribute(colors, 7);
		}
		else
		{
			cout << a << " ";
			SetConsoleTextAttribute(colors, 7);
		}
	}
	cout << "|" << endl;
	for (int i = 0; i <= 4; i++)
	{
		cout << "|__";
	}
	cout << "|" << endl;
}

void booking(AVL_tree obj[], int a) {
	string name;
	int seat;
	cout << "\nEnter your name: ";
	cin >> name;
	cout << "\nHow many tickets you wanna buy? ";
	cin >> seat;
	int left = obj[a].avail();
	if (seat > left) {
		cout << "\nNo enough seats are left." << endl;
		return;
	}
	int s;
	cout << endl;
	bool loop = false;
	for (int i = 0; i < seat; i++) {
		do {
			cout << "Enter Seat num: ";
			cin >> s;
			if (!obj[a].search(s) && s < 47 && s>0) {
				loop = false;
				obj[a].insert(obj[a].root, s, name);
			}
			else {
				cout << "\nSeat Already Reserved\nEnter again!!!" << endl;
				loop = true;
			}
		} while (loop);
	}

	cout << "\nTickets confirmed" << endl;
}

void refund(AVL_tree obj[], int a) {

//	obj[a].bus(0);
	string name;
	int num;
	cout << endl;
	cout << "Enter your name: ";
	cin >> name;
	cout << "Enter your Seat number: ";
	cin >> num;
	if (obj[a].search(num)) {
		obj[a].deletenode(obj[a].root, num);
		cout << "\nRefunded" << endl;
	}
	else
		cout << "\nSeat is not reserved" << endl;
}

void status(AVL_tree obj[], int& time) {

	cout << "|" << setw(10) << left << "Name" << "|" << setw(10) << "Seat No" << "|" << endl;
	obj[time].display(obj[time].root);
}

void menu(AVL_tree obj[], int time) {
	bool loop = true;
	int cho;
	system("pause");
	system("CLS");
	do {
		cout << "Press 1 to Book a ticket \nPress 2 to Refund\nPress 3 to View status\nPress 4 to exit from current bus\nYour choice: ";
		cin >> cho;
		switch (cho)
		{
		case 1:
			booking(obj, time);
			break;
		case 2:
			refund(obj, time);
			break;
		case 3:
			status(obj, time);
			break;
		case 4:
			loop = false;
			cout << "Exiting bus-no" << time << endl;
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}
		system("pause");
		system("CLS");
	} while (loop);
}