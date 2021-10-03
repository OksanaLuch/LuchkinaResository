#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

struct Pipe
{
	int id;
	int d;
	int l; //ot 10 do 200 sdelat' ogranichenie
	string remont;
};

struct KampStation
{
	int id, at, atr; //at - amount of tsehov vsego. atr - amount of tsehov v rabote
	float eff; //eff - effectivnost'
	string name;
};

void PrintePipe(const Pipe& p)
{

	cout << "Pipe number: " << p.id << "\n It's diameter is: " << p.d << " mm " << " \n It's lenght: " << p.l << " km \n" << "If it's in remont? The answer is " << p.remont << "\n";
}

Pipe AddPipe()
{
	Pipe p;
	p.id = 1;
	cout << "Vvedite diameter: ";
	cin >> p.d;
	cout << "Vvedite lenght: ";
	cin >> p.l;
	while (p.l <= 10 or p.l >= 200) {
		cout << "Length of pipe must be from 10 to 200. Enter it again \n";
		cin >> p.l;
	}
	cout << "Vvedite yes, esli truba v remonte. Inache no: ";
	cin >> p.remont;
	return p;
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
	cout << "Vvedite effectivnost' stantsii: ";
	cin >> s.eff;
	return s;
}

void PrintStation(const KampStation& s)
{
	cout << "Kompressornaya station with id " << s.id << " is named " << s.name << " It has " << s.at << " tsehov vsego and " << s.atr << " tsehov rabotaut. Effectivnost' of station is " << s.eff << "\n";
}

int main()
{
	int choice;
	Pipe p = {};
	KampStation s = {};


	cout << "1.Add Pipe\n" << "2.Add Kompressornaya station\n" << "3.See all objects\n" << "4.Edit Pipe\n" << "5.Edit Kompressornaya station\n" << "0.Exit\n";
	cin >> choice;
	while (1) {
		switch (choice)
		{

		case 0:
			return 0; // v menu 
		case 1:
			p = AddPipe();
			break;
		case 2:
			s = AddStation();
			break;
		case 3:
			if (s.id == 1) PrintStation(s);
			if (p.id == 1) PrintePipe(p);
			if (s.id != 1 or p.id != 1) cout << "Dannih net. Neobhodimo vvesti.\n";
			break;
		case 4:
			if (p.id) {
				int g;
				cout << "If you want to edit length of pipe enter 1. Else enter 0."; cin >> g;
				if (g == 1) cin >> p.l;
				cout << "If you want to edit status of remont of pipe enter 1. Else enter 0."; cin >> g;
				if (g == 1) cin >> p.remont;
			}
			else cout << "Pipe doesn't exist";
			break;
		case 5:
			if (s.id) {
				int g;
				cout << "If you want to edit amount of tsehov enter 1. Else enter 0."; cin >> g;
				if (g == 1) cin >> s.at;
				cout << "If you want to edit emount of tsehov v rabote enter 1. Else enter 0."; cin >> g;
				if (g == 1) cin >> s.atr;
				cout << "If you want to edit effectivmost' of station enter 1. Else enter 0."; cin >> g;
				if (g == 1) cin >> s.eff;
			}
			else cout << "Station doesn't exist";
			break;
		default:
			break;
		}
	}

}


