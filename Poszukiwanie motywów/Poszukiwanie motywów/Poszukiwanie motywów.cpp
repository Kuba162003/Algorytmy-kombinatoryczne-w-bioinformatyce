#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include<algorithm>
using namespace std;

struct Sequence {
	vector<char> fasta;
	vector<int> indexes;
	vector<int> qual;
	int length;

};	
Sequence sequences[5];

struct Vertices {
	vector<char> seq;
	int sequence_number;
	int place;
	vector<Vertices> edges;
};
vector<Vertices> graph;
vector<Vertices> clicks;

void Load();
void Remove();
void Create_graph();
void Create_edges();
void Find_clicks();
void Display();

int main(){
	Load();
	Remove();
	Create_graph();
	Create_edges();
	Find_clicks();
	Display();
	return 0;
}

void Load() {
	fstream plik_fasta;
	plik_fasta.open("sequence3.fasta", ios::in);
	if (plik_fasta.good() == false) {
		cout << "Nie ma pliku fasta";
		exit(0);
	}

	
	string skip;
	for (int i = 0; i < 5; i++) {
		int place = 1;
		getline(plik_fasta, skip);
		char nucleotide = 'X';
		sequences[i].length = 0;
		while (plik_fasta >> nucleotide && nucleotide != '>') {
			sequences[i].fasta.push_back(nucleotide);
			sequences[i].indexes.push_back(place);
			place++;
			sequences[i].length++;
		}
	}
	plik_fasta.close();

	fstream plik_qual;
	plik_qual.open("quality3.qual", ios::in);
	if (plik_qual.good() == false) {
		cout << "Nie ma pliku qual";
		exit(0);
	}

	string line;
	int index = -1;

	while (std::getline(plik_qual, line)) {
		if (!line.empty() && line[0] == '>') {
			index++;
			continue;
		}

		if (index >= 0) {
			istringstream stream(line);
			int rate;
			while (stream >> rate) {
				sequences[index].qual.push_back(rate);
			}
		}
	}

	plik_qual.close();

}

void Remove() {
	int threshold;
	cout << "Podaj prog: ";
	cin >> threshold;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < sequences[i].length; j++) {
			if (sequences[i].qual[j] < threshold) {
				sequences[i].fasta.erase(sequences[i].fasta.begin() + j);
				sequences[i].indexes.erase(sequences[i].indexes.begin() + j);
				sequences[i].qual.erase(sequences[i].qual.begin() + j);
				sequences[i].length--;
				j--;
			}
		}
	}
}

void Create_graph() {
	int length;
	cout << "Podaj dlugosc podciagow w grafie: ";
	cin >> length;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < sequences[i].length - length + 1; j++) {
			Vertices vertic;
			for (int k = 0; k < length; k++) {
				vertic.seq.push_back(sequences[i].fasta[j + k]);
			}
			vertic.sequence_number = i;
			vertic.place = sequences[i].indexes[j];
			graph.push_back(vertic);
		}
	}
}

void Create_edges() {
	for (int i = 0; i < graph.size() - 1; i++) {
		for (int j = i + 1; j < graph.size(); j++) {
			if (graph[i].place >= graph[j].place) {
				if (graph[i].seq == graph[j].seq && graph[i].place - graph[j].place <= 10 * graph[i].seq.size() && graph[i].sequence_number != graph[j].sequence_number) {
					graph[i].edges.push_back(graph[j]);
					graph[j].edges.push_back(graph[i]);
				}
			}
			else {
				if (graph[i].seq == graph[j].seq && graph[j].place - graph[i].place <= 10 * graph[i].seq.size() && graph[i].sequence_number != graph[j].sequence_number) {
					graph[i].edges.push_back(graph[j]);
					graph[j].edges.push_back(graph[i]);
				}
			}
		}
	}
}

void Find_clicks() {
	sort(graph.begin(), graph.end(), [](const Vertices& v1, const Vertices& v2) {
		return v1.edges.size() > v2.edges.size();
	});

	clicks.push_back(graph[0]);
	for (int i = 1; i < graph.size(); i++) {
		int con = 0;
		vector<int> connected;
		for (int j = 0; j < clicks.size(); j++) {
			for (int k = 0; k < graph[i].edges.size(); k++) {
				if (clicks[j].seq == graph[i].edges[k].seq && clicks[j].sequence_number == graph[i].edges[k].sequence_number && clicks[j].place == graph[i].edges[k].place)
					con = 1;
			}
			if(con == 1)
				connected.push_back(1);
			else
				connected.push_back(0);
		}
		int add = 1;
		for (int k = 0; k < connected.size(); k++) {
			if (connected[k] == 0)
				add = 0;
		}
		if (add == 1)
			clicks.push_back(graph[i]);
	}
}

void Display() {
	int used[5] = { 0 };
	for (int i = 0; i < clicks.size(); i++) {
		if (used[clicks[i].sequence_number] == 0) {
			cout << clicks[i].sequence_number + 1 << ", " << clicks[i].place << endl;
			used[clicks[i].sequence_number] = 1;
		}
	}
	cout << "sekwencja: ";
	for (char element : clicks[0].seq) {
		std::cout << element;
	}
}