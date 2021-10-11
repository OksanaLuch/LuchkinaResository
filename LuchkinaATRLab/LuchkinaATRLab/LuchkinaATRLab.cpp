#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Pipe
{
	int id;
	int d;
	int l;
	bool remont;
};

struct KampStation
{
	int id, at, atr; //at - amount of tsehov vsego. atr - amount of tsehov v rabote
	float eff; //eff - effectivnost'
	string name;
};

void PrintePipe(const Pipe& p)
{
	if (p.id != 0) {
		cout << "Pipe number: " << p.id << "\n It's diameter is: " << p.d << " mm " << " \n It's lenght: " << p.l << " km \n" << "If it's in remont? The answer is ";
		if (p.remont) cout << "yes \n"; else cout << "no\n";
	}
	else cout << "No dannih about truba";
}

Pipe AddPipe()
{
	Pipe p;
	p.id = 1;
	cout << "Vvedite diameter: ";
	cin >> p.d;
	cout << "Vvedite lenght: ";
	cin >> p.l;
	while (p.l < 10 or p.l > 200) {
		cout << "Length of pipe must be from 10 to 200. Enter it again \n";
		cin >> p.l;
	}
	cout << "Vvedite 1, esli truba v remonte. Inache 0: ";
	cin >> p.remont;
	return p;
}

void EditPipe(Pipe& p){
	if (p.id==1) {
		int choice;
		cout << "If you want to edit length of pipe enter 1. Else enter 0.\n"; cin >> choice;
		if (choice == 1) {
			cout << "Vvedite novoe znachenie\n";
			cin >> p.l;
		}
		cout << "If you want to edit status of remont of pipe enter 1. Else enter 0.\n"; cin >> choice;
		if (choice == 1) {
			cout << "Vvedite 1 if truba v remonte. Else vvedite 0 \n";
			cin >> p.remont;
		}
	}
	else cout << "Pipe doesn't exist\n";
}

void EditStation(KampStation& s) { 
	if (s.id==1) {
		int g;
		cout << "If you want to edit amount of tsehov enter 1. Else enter 0.\n"; cin >> g; 
		if (g == 1){
			cout << "Vvedite novoe znachenie\n";
			cin >> s.at;
		}
		cout << "If you want to edit emount of tsehov v rabote enter 1. Else enter 0."; cin >> g;
		if (g == 1) {
			cout << "Vvedite novoe znachenie\n";
			cin >> s.atr;
		}
		cout << "If you want to edit effectivmost' of station enter 1. Else enter 0."; cin >> g;
		if (g == 1) {
			cout << "Vvedite novoe znachenie\n";
			cin >> s.eff;
		}
	}
	else cout << "Station doesn't exist";

}

KampStation AddStation() {
	KampStation s;
	s.id = 1;
	cout << "Vvedite name of station: ";
	cin >> s.name;
	cout << "Vvedite obshee kolichestvo tsehov: ";
	cin >> s.at;
	cout << "Vvedite kolichestvo rabitaushih tsehov: ";
	cin >> s.atr;
	while (s.atr > s.at) {
		cout << "Amount of rabauschih tsehov can't be more than amount of tsehov vsego. Please vvedite correktnoe znachenie.\n";
		cin >> s.atr;
	}
	cout << "Vvedite effectivnost' stantsii: ";
	cin >> s.eff;
	return s;
}

void PrintStation(const KampStation& s)
{
	if(s.id!=0)
	cout << "Kompressornaya station's id is " << s.id << "\n It's name is " << s.name << "\n It has " << s.at << " tsehov vsego and " << s.atr << " tsehov rabotaut.\n Effectivnost' of station is " << s.eff << "\n";
	else cout << "Dannih net";
}

void outfile(const Pipe& p,const KampStation& s) {
	ofstream outfile("outfile.txt");
	if (p.id != 0) {
		outfile << "Pipe number: " << p.id << "\n It's diameter is: " << p.d << " mm " << " \n It's lenght: " << p.l << " km \n" << "If it's in remont? The answer is ";
		if (p.remont) cout << "yes \n"; else cout << "no\n";
	}
	else outfile << "No dannih about truba\n";

	if(s.id!=0)
	outfile << "Kompressornaya station's id is " << s.id << "\n It's name is " << s.name << "\n It has " << s.at << " tsehov vsego and " << s.atr << " tsehov rabotaut.\n Effectivnost' of station is " << s.eff << "\n";
	else outfile << "No dannih about station\n";

}

void fromfile(KampStation& s) {
	char name[11];
	s.name = "";
	ifstream fromfile("infile.txt");
	fromfile.getline(name,11);
	for (int i = 0; i <= 11; i++) {
		s.name = s.name + name[i];
	}
	fromfile.close();
}
int GetInt()
{
	int choice;
	while (!(cin >> choice) || (cin.peek() != '\n'))
	{
		cout << "Vvedite tsifry iz menu\n";
		cin.clear();
		cin.ignore(1000, '\n');
		//cin >> choice;
	}
	return choice;
}

int main()
{
	int choice;
	string choice1;
	Pipe p = {};
	KampStation s = {};
 
	while (1) {
		cout << "1.Add Pipe\n" << "2.Add Kompressornaya station\n" << "3.See all objects\n" << "4.Edit Pipe\n" << "5.Edit Kompressornaya station\n" << "6.Save data in file\n" << "7.Take name of station frome file\n" << "0.Exit\n";

			switch (GetInt())
			{

			case 0:
				return 0;
			case 1:
				p = AddPipe();
				break;
			case 2:
				s = AddStation();
				break;
			case 3:
				if (s.id == 1) PrintStation(s);
				if (p.id == 1) PrintePipe(p);
				if (s.id != 1) cout << "Dannih anout station net. Neobhodimo vvesti.\n";
				if (p.id != 1) cout << "Dannih about truba net. Neobhodimo vvesti.\n";
				break;
			case 4:
				EditPipe(p);
				break;
			case 5:
				EditStation(s);
				break;
			case 6:
				outfile(p, s);
				break;
			case 7:
				fromfile(s);
				break;
			default:
				break;
			}
	}


	return 0;
}


