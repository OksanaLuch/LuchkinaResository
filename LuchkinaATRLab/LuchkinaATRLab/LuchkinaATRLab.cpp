#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Pipe
{
public:
	int id;
	int d;
	int l;
	bool remont;

	friend ostream& operator<< (ostream &out, const Pipe &p);
};

ostream& operator<< (ostream &out, const Pipe &p)
{
	cout << "Pipe's diameter is: " << p.d << " mm " << " \n It's lenght: " << p.l << " km \n" << "If it's in remont? The answer is ";
	if (p.remont) cout << "yes \n";
	else cout << "no\n";
	return out;
}

class KampStation
{
public:
	int at, atr; //at - amount of tsehov vsego. atr - amount of tsehov v rabote
	float eff; //eff - effectivnost'
	string name;

	friend std::ostream& operator<< (std::ostream &out, const KampStation &s);
};

ostream& operator<< (ostream &out, const KampStation &s)
{
	out << "Station's name is " << s.name << "\n It has " << s.at << " tsehov vsego and " << s.atr << " tsehov rabotaut.\n Effectivnost' of station is " << s.eff << "\n";
	return out;
}

Pipe AddPipe(map <int,Pipe> &, int &, int &);
KampStation AddStation(map <int,KampStation> &, int &, int &);
void EditPipe(map <int, Pipe> &, map <int, Pipe > ::iterator);
void EditStation(map <int, KampStation> &, map <int, KampStation> ::iterator);
void EditFiltrPipe(map <int, Pipe> &, map <int, Pipe > ::iterator);
void EditFiltrStation(map <int, KampStation> &, map <int, KampStation> ::iterator);
void outfile(map <int, KampStation> &, map <int, Pipe> &, map <int, KampStation> ::iterator, map <int, Pipe> ::iterator);
void fromfile(map <int, KampStation> &, map <int, Pipe> &, int &, int &);
void SeeAllObj(map <int, KampStation> & , map <int, Pipe> &, map <int, KampStation> ::iterator, map <int, Pipe> ::iterator);
void DeletePipe(map <int, Pipe> &, map <int, Pipe> ::iterator);
void DeleteStation(map <int, KampStation> &, map <int, KampStation> ::iterator);
int GetInt();

int main()
{
	map <int, Pipe > Pipes;
	map <int, KampStation > Stations;
	map <int, Pipe > ::iterator it_p;
	map <int, KampStation > ::iterator it_s;
	int ap, as, idp, ids; //ap-amount of pipes, as - amount of station, idp and ids - peremenie for id 
	idp = 0;
	ids = 0; 
	int choice;
	int n;
	string choice1;
 
	while (1) {
		cout<< "1.Add Pipe\n" 
			<< "2.Add Kompressornaya station\n" 
			<< "3.See all objects\n" 
			<< "4.Edit Pipe\n" 
			<< "5.Edit Kompressornaya station\n" 
			<< "6.Save data in file\n" 
			<< "7.Take data frome file\n" 
			<< "8.Delete pipe\n" 
			<< "9.Delete station\n" 
			<< "10.Find and edit with filet\n"
			<< "0.Exit\n";

		switch (GetInt())
		{

		case 0:
			return 0;
		case 1:
			AddPipe(Pipes, ap, idp);
			break;
		case 2:
			AddStation(Stations, as, ids);
			break;
		case 3:
			SeeAllObj(Stations, Pipes, it_s, it_p);
			break;
		case 4:
			EditPipe(Pipes, it_p);
			break;
		case 5:
			EditStation(Stations, it_s);
			break;
		case 6:
				outfile(Stations, Pipes, it_s, it_p);
				break;
		case 7:
			fromfile(Stations, Pipes, idp, ids);
			break;
		case 8:
			DeletePipe(Pipes, it_p);
			break;
		case 9:
			DeleteStation(Stations, it_s);
			break;
		case 10: //poisk po fil'try
			int choice;
			cout << "If you want to find pipes enter 1. If you want to find stations enter 2. \n";
			cin >> choice;
			if (choice == 1) EditFiltrPipe(Pipes, it_p);
			if (choice == 2) EditFiltrStation(Stations, it_s);
			break;
		default:
			break;
			}
	}


	return 0;
}


Pipe AddPipe(map <int, Pipe>& Pipes, int &ap, int &idp)
{
	Pipe p;
	++idp;
	//p.id = idp;
	cout << "Vvedite diameter: ";
	p.d = GetInt();
	cout << "Vvedite lenght: ";
	p.l = GetInt();
	while (p.l < 10 or p.l > 200) {
		cout << "Length of pipe must be from 10 to 200. Enter it again \n";
		p.l= GetInt();
	}
	cout << "Vvedite 1, esli truba v remonte. Inache 0: ";
	cin >> p.remont;
	Pipes.insert(make_pair(idp, p));
	return p;
}

KampStation AddStation(map <int, KampStation>& Stations, int &as, int &ids) {
	KampStation s;
	++ids;
	//s.id = ids;
	cout << "Vvedite name of station: ";
	cin >> s.name;
	cout << "Vvedite obshee kolichestvo tsehov: ";
	s.at= GetInt();
	cout << "Vvedite kolichestvo rabitaushih tsehov: ";
	s.atr= GetInt();
	while (s.atr > s.at) {
		cout << "Amount of rabauschih tsehov can't be more than amount of tsehov vsego. Please vvedite correktnoe znachenie.\n";
		s.atr= GetInt();
	}
	cout << "Vvedite effectivnost' stantsii: ";
	cin >> s.eff;
	Stations.insert(make_pair(ids, s));
	return s;
}

void EditPipe(map <int, Pipe> & Pipes, map <int, Pipe > ::iterator it_p) {

	int choice,n;

	if (!Pipes.empty())
	{
		cout << "Which pipe would you like to edit? Enter its ID \n";
		cin >> n;
		it_p = Pipes.find(n);

		while (it_p == Pipes.end()) {
			cout << "Pipe with ID " << n << " net. Vvedite snova.\n";
			cin >> n;
			it_p = Pipes.find(n);
		}

	cout << "If you want to edit length of pipe enter 1. Else enter 0.\n"; cin >> choice;
	if (choice == 1) {
		cout << "Vvedite novoe znachenie\n";
		Pipes[n].l= GetInt();
	}
	cout << "If you want to edit status of remont of pipe enter 1. Else enter 0.\n"; cin >> choice;
	if (choice == 1) {
		cout << "Vvedite 1 if truba v remonte. Else vvedite 0 \n";
		cin >> Pipes[n].remont;
	}
	}
	else cout << "There are no pipes.";
}

void EditStation(map <int, KampStation> & Stations, map <int, KampStation> ::iterator it_s) {

	int g, n;

	if (!Stations.empty())
	{
		cout << "Which station would you like to edit? Enter its ID \n";
		cin >> n;
		it_s = Stations.find(n);

		while (it_s == Stations.end()) {
			cout << "Station with ID " << n << " net. Vvedite snova.\n";
			cin >> n;
			it_s = Stations.find(n);
		}

	cout << "If you want to edit amount of tsehov enter 1. Else enter 0.\n"; cin >> g;
	if (g == 1) {
		cout << "Vvedite novoe znachenie\n";
		Stations[n].at= GetInt();
	}
	cout << "If you want to edit emount of tsehov v rabote enter 1. Else enter 0."; cin >> g;
	if (g == 1) {
		cout << "Vvedite novoe znachenie\n";
		Stations[n].atr= GetInt();
		while (Stations[n].atr > Stations[n].at) {
			cout << "Amount of rabauschih tsehov can't be more than amount of tsehov vsego. Please vvedite correktnoe znachenie.\n";
			Stations[n].atr = GetInt();
		}
	}
	cout << "If you want to edit effectivmost' of station enter 1. Else enter 0."; cin >> g;
	if (g == 1) {
		cout << "Vvedite novoe znachenie\n";
		cin >> Stations[n].eff;
	}
	}
	else cout << "There are no pipes.";
}

void EditFiltrPipe(map <int, Pipe> & Pipes, map <int, Pipe > ::iterator it_p) {
	if (!Pipes.empty()) {
	int choice1, choice2, amountofpipes;
	amountofpipes = 0;
	int flength;//length for filtr 
	bool fremont;
	cout << "If you want to get all pipes with konkretnym length enter 1. If you want to get all pipes with konkretnym priznakom about remont enter 2. ";
	cin >> choice1;
	if (choice1 == 1) {
		cout << "Enter length\n";
		cin >> flength;
		it_p = Pipes.begin();
		for (int i = 0; it_p != Pipes.end(); it_p++, i++) {
			if (it_p->second.l == flength) {
				cout << "We have pipe you need. Look: \n";
				amountofpipes++;
				cout<<Pipes[it_p->first];
				cout << "If you want to edit it, enter 1. Else enter 0. \n";
				cin >> choice2;
				if (choice2 == 1) EditPipe(Pipes, it_p);
			}
		}
		if (amountofpipes == 0) cout << "There are no such pipes";
	}

	amountofpipes = 0;
	if (choice1 == 2) {
		cout << "Enter status of remont: 1 or 0.\n";
		cin >> fremont;

		it_p = Pipes.begin();
		for (int i = 0; it_p != Pipes.end(); it_p++, i++) {
			if (it_p->second.remont == fremont) {
				cout << "We have pipe you need. Look: \n";
				amountofpipes++;
				cout << Pipes[it_p->first];
				cout << "If you want to edit it, enter 1. Else enter 0. \n";
				cin >> choice2;
				if (choice2 == 1) EditPipe(Pipes, it_p);
			}
		}
		if (amountofpipes == 0) cout << "There are no such pipes";
	}
	}
	else cout << "Dannih about stations net. Neobhodimo vvesti.\n";
}

void EditFiltrStation(map <int, KampStation> & Stations, map <int, KampStation> ::iterator it_s)
{
	if (!Stations.empty()) {

	int choice1, choice2, amountofstations, fprotsent;
	amountofstations = 0;
	string fname; //name for filtr 
	int ftsehi; //protsent of nezadeistvovannih tsehov for filtr 
	cout << "If you want to get all stations with konkretnym name enter 1. If you want to get all stations with konkretnym protsent of nezadeistvovannih tsehov enter 2. ";
	cin >> choice1;

	if (choice1 == 1) {
		cout << "Vvedite name for filtr \n";
		cin >> fname;
		it_s = Stations.begin();
		for (int i = 0; it_s != Stations.end(); it_s++, i++) {
			if (it_s->second.name == fname) {
				cout << "We have station you need. Look: \n";
				amountofstations++;
				cout << Stations[it_s->first];
				cout << "If you want to edit it, enter 1. Else enter 0. \n";
				cin >> choice2;
				if (choice2 == 1) EditStation(Stations, it_s);
			}
		}
		if (amountofstations == 0) cout << "There are no such stations \n";
	}
	amountofstations = 0;
	float protsent;
	if (choice1 == 2) {
		cout << "Enter protsent of nezadeistvovannih tsehov \n";
		cin >> fprotsent;

		it_s = Stations.begin();
		for (int i = 0; it_s != Stations.end(); it_s++, i++) {
			protsent = (float)((Stations[it_s->first].at * 100 - Stations[it_s->first].atr * 100) / Stations[it_s->first].at); 
			//cout << protsent << "\n";
			if (protsent == fprotsent) {
				cout << "We have station you need. Look: \n";
				amountofstations++;
				cout << Stations[it_s->first];
				cout << "If you want to edit it, enter 1. Else enter 0. \n";
				cin >> choice2;
				if (choice2 == 1) EditStation(Stations, it_s);
			}
		}
		if (amountofstations == 0) cout << "There are no such stations \n";
	}
	}
	else cout << "Dannih about stations net. Neobhodimo vvesti.\n";
}

void outfile(map <int, KampStation> & Stations, map <int, Pipe> & Pipes, map <int, KampStation> ::iterator it_s, map <int, Pipe> ::iterator it_p) {
	string fname;

	int np, ns;
	if ((!Stations.empty()) && (!Pipes.empty())) {
		cout << "Which pipe would you like to print in file ? Enter its ID \n";
		cin >> np;
		it_p = Pipes.find(np);
		while (it_p == Pipes.end()) {
			cout << "Pipe with ID " << np << " net. Vvedite snova.\n";
			cin >> np;
			it_p = Pipes.find(np);
		}

		cout << "Which station would you like to print in file ? Enter its ID \n";
		cin >> ns;
		it_s = Stations.find(ns);
		while (it_s == Stations.end()) {
			cout << "Station with ID " << ns << " net. Vvedite snova.\n";
			cin >> ns;
			it_s = Stations.find(ns);
		}

	cout << "Enter name for output file. Don't forget to add .txt \n";
	cin >> fname;

	ofstream outfile(fname);
	outfile << "pipe \n" << Pipes[np].d << "\n" << Pipes[np].l << "\n" << Pipes[np].remont<<"\n";
	outfile << "station \n" << Stations[ns].name << "\n" << Stations[ns].at << "\n" << Stations[ns].atr << "\n" << Stations[ns].eff << "\n";
	}
	else
		cout << "Stations or Pipes is empti. Enter data.\n";
}

void fromfile(map <int, KampStation> & Stations, map <int, Pipe> & Pipes, int & idp, int & ids) {
	ifstream f;
	string fname;
	KampStation s;
	Pipe p;
	cout << "Enter name of file you want to take data from. Don't forget to add .txt \n";
	cin >> fname;
	f.open(fname, ios::in);
	if (f.good()) {
		while (!f.eof()) {
			string name;

			f >> name;
			if (name == "pipe")
			{
				f >> p.d;
				f >> p.l;
				f >> p.remont;
			}

			f >> name;
			if (name == "station") {
				f.ignore(256, '\n');
				string(s.name);
				getline(f, s.name);
				f >> s.at;
				f >> s.atr;
				f >> s.eff;
			}

		}
		ids++;
		idp++;
		Pipes.insert(make_pair(idp, p));
		Stations.insert(make_pair(ids, s));
		cout << "Gotovo! \n";
	}

}

int GetInt()
{
	int choice;
	while (!(cin >> choice) || (cin.peek() != '\n'))
	{
		cout << "Error of entering!!! Vvedite snova\n";
		cin.clear();
		cin.ignore(1000, '\n');
		//cin >> choice;
	}
	return choice;
}

void SeeAllObj(map <int, KampStation> & Stations, map <int, Pipe> & Pipes, map <int, KampStation> ::iterator it_s, map <int, Pipe> ::iterator it_p) {
	if (!Stations.empty()) {
		it_s = Stations.begin();
		for (int i = 0; it_s != Stations.end(); it_s++, i++) {
			cout << "ID:  " << it_s->first << "\n " << it_s->second << endl;
		}
	}
	else cout << "Dannih about stations net. Neobhodimo vvesti.\n";

	if (!Pipes.empty()) {
		it_p = Pipes.begin();
		for (int i = 0; it_p != Pipes.end(); it_p++, i++) {
			cout << "ID:  " << it_p->first << "\n " << it_p->second << endl;
		}
	}
	else cout << "Dannih about pipes net. Neobhodimo vvesti.\n";
}

void DeletePipe(map <int, Pipe> & Pipes, map <int, Pipe> ::iterator it_p) {
	int n;
	if (!Pipes.empty()) {
		cout << "Which pipe would you like do delete? Enter its ID \n";
		cin >> n;
		it_p = Pipes.find(n);
		while (it_p == Pipes.end()) {
			cout << "Pipe with ID " << n << " net. Vvedite snova.\n";
			cin >> n;
			it_p = Pipes.find(n);
		}
		Pipes.erase(it_p);
	}
	else cout << "There are no pipes.\n";
}


void DeleteStation(map <int, KampStation> & Stations, map <int, KampStation> ::iterator it_s) {
	int n;

	if (!Stations.empty()) {
		cout << "Which station would you like do delete? Enter its ID \n";
		cin >> n;
		it_s = Stations.find(n);
		while (it_s == Stations.end()) {
			cout << "Station with ID " << n << " net. Vvedite snova.\n";
			cin >> n;
			it_s = Stations.find(n);
		}
		Stations.erase(it_s);
	}
	else cout << "There are no stations.\n";
}
