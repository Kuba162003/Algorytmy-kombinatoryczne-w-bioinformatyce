#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<cmath>
using namespace std;

vector<int> Load();
int Silnia(int n);
int Cuts(int A);
int First_element();
void Search(int index, int max_index);
bool In_set(int number);
bool Correct();
int Check_used();
vector<int> set;
vector<int> map;
vector<bool> used;
bool end_program = false;

void Wyswietl_zbior(vector<int> zbior);
void Wyswietl_uzyte();

int main() {
	set = Load();
	sort(set.begin(), set.end());
	int length = set.back();
	int cuts = Cuts(set.size());
	if (cuts == -1) {
		cout << "Nie można skonstruować mapy";
		return 0;
	}
	for (int i = 0; i < set.size(); i++) {
		used.push_back(false);
	}
	int first = First_element();
	map.push_back(first);
	clock_t t = clock();
	Search(first, cuts + 1);
	if (end_program == false) {
		cout << "Nie znaleziono rozwiazania";
		return 0;
	}

	t = clock() - t;
	double time_of_algorithm = t;
	time_of_algorithm = time_of_algorithm / CLOCKS_PER_SEC;
	cout << endl << "Czas: " << time_of_algorithm;

	return 1;
}

vector<int> Load() {
	fstream plik;
	plik.open("instancja11b.txt", ios::in);
	if (plik.good() == false) {
		cout << "Nie ma pliku";
		exit(0);
	}

	vector<int> instance;
	int fragment;
	while (plik >> fragment) {
		instance.push_back(fragment);
	}

	plik.close();
	return instance;
}

int Silnia(int n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	else {
		return n * Silnia(n - 1);
	}
}

int Cuts(int A) {
	A = 8 * A;
	A = A + 1;
	A = sqrt(A);
	A = A - 3;
	A = A / 2;
	return A;
}

int First_element() {
	int first = set[set.size() - 1] - set[set.size() - 2];
	for (int i = 0; i < set.size(); i++) {
		if (set[i] == first) {
			used[i] = true;
			break;
		}
	}
	return first;
}

void Search(int index, int max_index) {
	if (map.size() == max_index) {
		if (Check_used() == 0) {
			return;
		}
		cout << "Wynik: ";
		for (int i = 0; i < map.size(); i++) {
			cout << map[i] << ", ";
		}
		end_program = true;
		return;
	}
	vector<bool> start_used;
	for (int i = 0; i < set.size(); i++) {
		if (used[i] == true)
			continue;
		map.push_back(set[i]);
		vector<bool> tmp_used = used;
		if (Correct()) {
			used[i] = true;
			Wyswietl_zbior(map);
			Search(set[i], max_index);
			if (end_program)
				return;
			used = tmp_used;
		}
		else {
			used = tmp_used;
			map.pop_back();
		}
	}
	used = start_used;
	map.pop_back();
	return;
}

bool In_set(int number) {
	for (int i = 0; i < set.size(); i++) {
		if (used[i] == true) {
			continue;
		}
		if (set[i] == number) {
			used[i] = true;
			return true;
		}
	}
	return false;
}

bool Correct() {
	vector<bool> in;
	for (int i = 0; i < map.size() - 1; i++) {
		in.push_back(false);
	}
	int tmp = map[map.size() - 1];
	for (int i = map.size() - 2; i >= 0; i--) {
		if (In_set(tmp + map[i])) {
			in[i] = true;
			tmp = tmp + map[i];
		}
	}

	for (int i = 0; i < in.size(); i++) {
		if (in[i] == false) {
			return false;
		}
	}
	return true;
}


void Wyswietl_zbior(vector<int> zbior) {
	for (int i = 0; i < zbior.size(); i++) {
		cout << zbior[i] << ", ";
	}
	cout << endl;
}

void Wyswietl_uzyte() {
	for (int i = 0; i < used.size(); i++) {
		cout << i << ": " << used[i] << endl;
	}
	cout << endl;
}

int Check_used() {
	for (int i = 0; i < used.size(); i++) {
		if (used[i] == false) {
			return 0;
		}
	}
	return 1;
}