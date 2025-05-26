// ConsoleApplication1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include<fstream>
#include<vector>
#include<algorithm>
#include <iostream>
#include<string>
#include<sstream>
#include<random>
using namespace std;
void elements_sums(int idx, int sum, vector<int>& map_of_regions, vector<int>& vector_of_sums) {
    if (idx >= map_of_regions.size())
        return;
    sum += map_of_regions[idx++];
    vector_of_sums.push_back(sum);
    elements_sums(idx, sum, map_of_regions, vector_of_sums);
}
vector<int> add_sums(vector<int>& map_of_regions) {
    vector<int>vector_of_sums;
    for (int i = 0; i < map_of_regions.size(); i++) {
        elements_sums(i, 0, map_of_regions, vector_of_sums);
    }

    return vector_of_sums;
}

int main()
{
    random_device rd;
    mt19937 gen(rd());
    int tmp;
    string line;
    vector<int>map_of_regions;
    getline(cin, line);
    line = line;
    stringstream stream(line);
    while (stream >> tmp) {
        map_of_regions.push_back(tmp);
    }
    vector<int>vector_of_sums = add_sums(map_of_regions);
    sort(vector_of_sums.begin(), vector_of_sums.end());
    //reverse(vector_of_sums.begin(), vector_of_sums.end());
    //shuffle(vector_of_sums.begin(), vector_of_sums.end(), gen);

    for (auto& x : vector_of_sums) {
        cout << x << ' ';
    }
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln