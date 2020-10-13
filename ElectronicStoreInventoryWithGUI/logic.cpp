#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <shellapi.h>

using namespace std;

fstream f;

struct info {
	char y = 'b';
	string produs;
	string customer;
	string list;
	char date[9] = { 'r', 'a', 'n', 'd', 'o', 'm' };
	int x = 0;
};

void populate(info* l) {
	f.open("baza.xcj", ios::app);
	f << "Name: " << l->customer << endl;
	f << "Stuff: " << l->produs << endl;
	f << "Date: ";
	for (int i = 0; i < 8; i++) {
		if (i > 0 && i <= 4 && i % 2 == 0) {
			f << "/";
		}
		f << l->date[i];
	}
	f << endl;
	for (int i = 0; i < 15; i++)
		f << "-";
	f << "\n\n";
	f.close();
}

void start(info* l) {
	cout << "\n\n";
	cout << "Hello there and welcome to my broken program :)\n\n";
	cout << "Enter customer name: ";
	getline(cin, l->customer);
	cout << endl;
	cout << "Products: ";
	getline(cin, l->produs);
	cout << endl;
	cout << "Today's date: ";
Q:
	cin >> l->date;
	cout << endl;
	if (strlen(l->date) > 8 || strlen(l->date) < 6) {
		cout << "Incorrect date pls enter again: ";
		goto Q;
	}
	cout << endl;
	populate(l);
}

void print(info* l) {
	ifstream f;
	f.open("Baza.xcj");
	while (!f.eof()) {
		getline(f, l->list);
		cout << l->list << endl;
	}
	f.close();
}

int main() {
	f.open("baza.xcj");
A:
	info d;
	info* l;
	l = &d;
	cout << "1.New entry\n\n";
	cout << "2.List all entries\n\n";
	cout << "3.Check for CUI \n\n";
	cout << "4.Exit\n\n";
	cout << "Enter your choice: ";

	cin >> l->x;
	cin.ignore();
	cout << endl;

	if (l->x > 4) {
		cout << "INVALID OPTION \n\n";
		system("pause");
		system("cls");
		goto A;
	}
	switch (l->x) {

	case 1:
	B:
		start(l);
		cout << "Go to Main Menu -y- -n-: ";
		cin >> l->y;
		cin.ignore();
		if (l->y != 'y' && l->y != 'n')
			cout << "INVALID OPTION \n\n";
		if (l->y == 'y') {
			system("cls");
			goto A;
			f.close();
		}
		else
			cin.ignore();
		system("cls");
		goto B;
		f.close();

	case 2:
		print(l);
		system("pause");
		system("cls");
		goto A;

	case 3:
		ShellExecute(0, 0, L"https://www.mfinante.gov.ro/infocodfiscal.html", 0, 0, SW_SHOW);
		system("cls");
		goto A;

	case 4:
		break;
	}
	f.close();
	cin.get();
	return 0;

}