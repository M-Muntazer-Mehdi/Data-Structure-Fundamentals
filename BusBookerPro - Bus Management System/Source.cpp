#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include"Header.h"

using namespace std;
int main() {
	AVL_tree* obj = new AVL_tree[4];
	int cho = 0;
	int bn;
	ifstream myFile("login.txt");
	string username, password, user, pass;
	cout << "Enter Username: ";
	cin >> username;
	cout << "\nEnter Password: ";
	cin >> password;
	while (!myFile.eof()) {
		myFile >> user >> pass;
	}
	if (user == username && pass == password) {
		cout << "Login Successfull" << endl;
		system("pause");
		system("CLS");
		bool loop = true;
		do {


			cout << "Bus no - 1001 available for departure on 12:00" << endl;

			cout << "Bus no - 1002 available for departure on 15:00" << endl;

			cout << "Bus no - 1003 available for departure on 18:00" << endl;

			cout << "Bus no - 1004 available for departure on 21:00" << endl;

			cout << "Enter Bus-no for Booking: ";
			cin >> bn;
			if (bn == 1001)
				menu(obj, 0);
			else if (bn == 1002)
				menu(obj, 1);
			else if (bn == 1003)
				menu(obj, 2);
			else if (bn == 1004)
				menu(obj, 3);
		} while (loop);
	}
	else {
		cout << "\nLogin Failed" << endl;
	}

	system("pause");
	return 0;
}