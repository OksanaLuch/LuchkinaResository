#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Pipe
{
	int id=0;
	int d;
	int l;
	bool remont;
};

struct KampStation
{
	int id = 0;
	int at, atr; //at - amount of tsehov vsego. atr - amount of tsehov v rabote
	float eff; //eff - effectivnost'
	string name;
};

vector <Pipe> Pipes(5); 
vector <KampStation> Stations(5);
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
	++idp;
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

void EditStation(KampStation& s) { 
	
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

KampStation AddStation() {
	KampStation s;
	++ids;
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

void EditFiltrPipe() {
	int choice1, choice2;
	int flength, fremont; //length for filtr 
	cout << "If you want to get all pipes with konkretnym length enter 1. If you want to get all pipes with konkretnym priznakom about remont enter 2. ";
	cin >> choice1;
	if (choice1 == 1) {
		cout << "Enter length\n";
		cin >> flength;
		for (int i = 0; i <= ap; i++) {
			if (Pipes[i].l == flength) {
				cout << "We have pipe you need. Look: \n";
				PrintePipe(Pipes[i]);
				cout << "If you want to edit it, enter 1. Else enter 0. \n";
				cin >> choice2;
				if (choice2 == 1) EditPipe(Pipes[i]);
			}
		}

	}

	if (choice1 == 2) {
		cout << "Enter status of remont: 1 or 0.\n";
		cin >> fremont;
		for (int i = 0; i <= ap; i++) {
			if (Pipes[i].remont == fremont) {
				cout << "We have pipe you need. Look: \n";
				PrintePipe(Pipes[i]);
				cout << "If you want to edit it, enter 1. Else enter 0. \n";
				cin >> choice2;
				if (choice2 == 1) EditPipe(Pipes[i]);
			}
		}
	}
}

void EditFiltrStation() 
{
	int choice1, choice2;
	string fname;
	int ftsehi; //name and protsent of nezadeistvovannih tsehov for filtr 
	cout << "If you want to get all stations with konkretnym name enter 1. If you want to get all statons with konkretnym protsent of nezadeistvovannih tsehov enter 2. ";
	cin >> choice1;

	if (choice1 == 1) {
		cout << "Vvedite name for filtr \n";
		cin >> fname;
		for (int i = 0; i <= as; i++) {
			if (Stations[i].name == fname)
				cout << "We have station you need. Look: \n";
			PrintStation(Stations[i]);
			cout << "If you want to edit it, enter 1. Else enter 0. \n";
			cin >> choice2;
			if (choice2 == 1) EditStation(Stations[i]);
		}
	}
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
		cout << "1.Add Pipe\n" << "2.Add Kompressornaya station\n" << "3.See all objects\n" << "4.Edit Pipe\n" << "5.Edit Kompressornaya station\n" << "6.Save data in file\n" << "7.Take data frome file\n" << "8.Delete pipe\n" << "9.Delete station\n" <<"0.Exit\n";

			switch (GetInt())
			{

			case 0:
				return 0;
			case 1:
				if (ap < 5) 
				Pipes[ap] = AddPipe();
				else cout << "There are 5 Pipes. It's maximum. You can't add more but you can delete one of them and add new one.";
				break;
			case 2:
				if (as < 5)
				Stations[as] = AddStation();
				else cout << "There are 5 Pipes. It's maximum. You can't add more but you can delete one of them and add new one.";
				break;
			case 3:
				if (as == 0) cout << "Dannih about stations net. Neobhodimo vvesti.\n";
				else 
					for (int i = 1; i <= as; i++) {
						PrintStation(Stations[i]);
						cout << "\n";
					}

				if (ap == 0) cout << "Dannih about pipes net. Neobhodimo vvesti.\n";
				else 
					for (int i = 1; i <= ap; i++) {
						PrintePipe(Pipes[i]);
						cout << "\n";
					}
				break;
			case 4:
				if (ap > 0) {
				cout << "There are " << ap << " pipes. Which would you like do edit? \n";
				cin >> n;
				while (n > ap) {
					cout << "Takoy trubi net. Vvedite snova.\n";
					cin >> n;
				}
				EditPipe(Pipes[n-1]);
				}
				else cout << "There are no pipes.";
				break;
			case 5:
				if (as>0){
				cout << "There are " << as << " stations. Which would you like do edit? \n";
				cin >> n;
				while (n > as) {
					cout << "Takoy station net. Vvedite snova.\n";
					cin >> n;
				}
				EditStation(Stations[n-1]);
			}
				else cout << "There are no pipes.";
				break;
			case 6:
				outfile(p, s);
				break;
			case 7:
				fromfile(s,p);
				break;
			case 8:
				if (ap > 0) {
					cout << "There are " << ap << " pipes. Which would you like do delete? \n";
					cin >> n;
					while (n > ap) {
						cout << "Takoy trubi net. Vvedite snova.\n";
						cin >> n;
					}
					Pipes.erase(Pipes.cbegin() + (n - 1));
					ap--;
				}
				else cout << "There are no stations.\n";
				break;
			case 9:
				if (as > 0) {
					cout << "There are " << as << " stations. Which would you like do delete? \n";
					cin >> n;
					while (n > as) {
						cout << "Takoy station net. Vvedite snova.\n";
						cin >> n;
					}
					Stations.erase(Stations.cbegin() + (n - 1));
					as--;
				}
				else cout << "There are no pipes.\n";
				break;
			case 10: //poisk po fil'try
				int choice;
				cout << "If you want to find pipe enter 1. If you want to find station enter 2. \n";
				cin >> choice;
				if (choice == 1) {
					if (ap >  0) EditFiltrPipe();
					else cout << "Trub net.\n";
				}
				if (choice == 2) {
					if (as > 0) EditFiltrStation();
					else cout << "Stations net.\n";
				}
	
				break;
			default:
				break;
			}
	}


	return 0;
}


