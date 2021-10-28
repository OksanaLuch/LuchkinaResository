#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
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

vector <Pipe> Pipes; 
vector <KampStation> Stations;
int ap, as, idp, ids; //ap-amount of pipes, as - amount of station, idp and ids - peremenie for id


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
	idp++;
	p.id = idp;
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
	Pipes.push_back(p);
	ap++;
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
	ids++;
	s.id = ids;
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
	Stations.push_back(s);
	as++;
	return s;
}

void PrintStation(const KampStation& s)
{
	if(s.id!=0)
	cout << "Kompressornaya station's id is " << s.id << "\n It's name is " << s.name << "\n It has " << s.at << " tsehov vsego and " << s.atr << " tsehov rabotaut.\n Effectivnost' of station is " << s.eff << "\n";
	else cout << "Dannih net";
}

void outfile(const Pipe& p, const KampStation& s) {
	ofstream outfile("outfile.txt");
	if (p.id != 0) {
		outfile << "pipe \n" << p.id << " \n" << p.d << " \n" << p.l << "\n"<< p.remont << endl;
	
	}
	

	if (s.id != 0)
		outfile << "station \n" << s.id << "\n " << s.name << "\n" << s.at << "\n" << s.atr << "\n" << s.eff << "\n";


}

void fromfile(KampStation& s, Pipe& p) {
	ifstream f;
	f.open("outfile.txt", ios::in);
	if (f.good()) {
		while (!f.eof()) {
			string name;

			f >> name;
			if (name == "pipe")
			{
				f >> p.id;
				f >> p.d;
				f >> p.l;
				f >> p.remont;
			}

			if (name == "station") {
				f >> s.id;
				f.ignore(256, '\n');
				string(s.name);
				getline(f, s.name);
				f >> s.at;
				f >> s.atr;
				f >> s.eff;
			}
		}
		cout << "Gotovo! \n";
	}

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
	//max 5 stations and 5 pipes 
	ap = 0;
	as = 0;
	idp = 0;
	ids = 0; 
	int choice;
	int n;
	string choice1;
	Pipe p = {};
	KampStation s = {};
 
	while (1) {
		cout << "1.Add Pipe\n" << "2.Add Kompressornaya station\n" << "3.See all objects\n" << "4.Edit Pipe\n" << "5.Edit Kompressornaya station\n" << "6.Save data in file\n" << "7.Take data frome file\n" << "0.Exit\n";

			switch (GetInt())
			{

			case 0:
				return 0;
			case 1:
				if (ap<5) 
				p = AddPipe();
				else cout << "There are 5 Pipes. It's maximum. You can't add more but you can delete one of them and add new one.";
				break;
			case 2:
				if (as < 5)
				s = AddStation();
				else cout << "There are 5 Pipes. It's maximum. You can't add more but you can delete one of them and add new one.";
				break;
			case 3:
				if (s.id == 1) PrintStation(s);
				if (p.id == 1) PrintePipe(p);
				if (s.id != 1) cout << "Dannih about station net. Neobhodimo vvesti.\n";
				if (p.id != 1) cout << "Dannih about truba net. Neobhodimo vvesti.\n";
				break;
			case 4:
				cout << "There are " << ap << " pipes. Which would you like do edit? \n";
				cin >> n;
				while (n > ap) {
					cout << "Takoy trubi net. Vvedite snova.\n";
					cin >> n;
				}
				EditPipe(Pipes[n]);
				break;
			case 5:
				cout << "There are " << as << " stations. Which would you like do edit? \n";
				cin >> n;
				while (n > as) {
					cout << "Takoy station net. Vvedite snova.\n";
					cin >> n;
				}
				EditStation(Stations[n]);
				break;
			case 6:
				outfile(p, s);
				break;
			case 7:
				fromfile(s,p);
				break;
			case 8:
				cout << "There are " << ap << " pipes. Which would you like do delete? \n";
				cin >> n;
				while (n > ap) {
					cout << "Takoy trubi net. Vvedite snova.\n";
					cin >> n;
				}
				Pipes.erase(Pipes.cbegin()+(n-1));
				ap--;
			case 9:
				cout << "There are " << as << " stations. Which would you like do delete? \n";
				cin >> n;
				while (n > as) {
					cout << "Takoy station net. Vvedite snova.\n";
					cin >> n;
				}
				Stations.erase(Stations.cbegin() + (n - 1));
				as--;
				break;
			default:
				break;
			}
	}


	return 0;
}


