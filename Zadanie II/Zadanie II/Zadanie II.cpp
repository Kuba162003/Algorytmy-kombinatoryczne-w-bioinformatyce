#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
const int MAX = 30;
int graf1[MAX][MAX];
int krawedzie1[MAX] = { 0 };
int wierzcholki1 = 0;
int graf2[MAX*2][MAX*2];
int krawedzie2[MAX] = { 0 };
int wierzcholki2 = 0;
void Wczytaj();
void Wypisz();
bool Nie_1_graf();
bool Nie_sprzezony();
void Przeksztalc();
bool Liniowy();


int main(){
    Wczytaj();

    if (Nie_1_graf()) {
        cout << "Graf nie jest 1-grafem, wiec nie moze byc grafem sprzezonym";
        return 0;
    }
    if (Nie_sprzezony()) {
        cout << "Graf nie jest sprzezony";
        return 0;
    }
    Przeksztalc();
    Wypisz();
    if (Liniowy())
        cout << "Graf jest sprzezony i liniowy";
    if (!Liniowy())
        cout << "Graf jest sprzezony i nie jest liniowy";
    
    return 1;
}

void Wczytaj() {
    fstream plik1;
    plik1.open("graf0.txt", ios::in);
    if (plik1.good() == false) {
        cout << "Nie ma takiego pliku";
        exit(0);
    }

    int i = 1;
    int j = 0;
    string linia;
    int wierzcholek;
    string pomin;
    while (!plik1.eof()) {
        getline(plik1, linia);
        stringstream strumien(linia);
        strumien >> pomin;
        strumien >> pomin;
        j = 0;
        while (strumien >> wierzcholek) {
            graf1[i][j] = wierzcholek;
            krawedzie1[i]++;
            j++;
        }
        wierzcholki1++;
        i++;
    }
    plik1.close();
}

void Wypisz() {
    fstream plik2;
    plik2.open("wynik.txt", ios::out);
    if (plik2.good() == false) {
        cout << "Nie ma pliku wynikowego";
        exit(0);
    }

    for (int j = 1; j <= wierzcholki2; j++) {
        plik2 << j << " : ";
        for (int k = 0; k < krawedzie2[j]; k++) {
            plik2 << graf2[j][k] << " ";
        }
        plik2 << endl;
    }
    plik2.close();
}

bool Nie_1_graf() {
    int k = 0;
    for (int i = 1; i <= wierzcholki1; i++) {
        for (int j = 0; j < krawedzie1[i]; j++) {
            k = j + 1;
            while(k < krawedzie1[i]) {
                if (graf1[i][j] == graf1[i][k])
                    return true;
                k++;
            }
        }
    }
    return false;
}

bool Nie_sprzezony() {
    for (int i = 1; i <= wierzcholki1; i++) {
        for (int j = 1; j <= wierzcholki1; j++) {
            int sprawdz[MAX] = { 0 };
            for (int k = 0; k < krawedzie1[i]; k++) {
                for (int l = 0; l < krawedzie1[j]; l++) {
                    if (graf1[i][k] == graf1[j][l]) {
                        sprawdz[k] = 1;
                    }
                }
            }
            if (krawedzie1[i] == krawedzie1[j]) {
                for (int m = 0; m < krawedzie1[i]; m++) {
                    if (sprawdz[m] == 1) {
                        for (int n = 0; n < krawedzie1[i]; n++) {
                            if (sprawdz[n] == 0)
                                return true;
                        }
                    }
                }
            }
            else {
                for (int m = 0; m < krawedzie1[i]; m++) {
                    if (sprawdz[m] == 1) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Przeksztalc() {
    int lista_lukow[MAX][2] = { 0 };
    int luk = 1;
    int w = 1;
    for (int i = 1; i <= wierzcholki1; i++) {
        lista_lukow[luk][0] = w++;
        lista_lukow[luk][1] = w++;
        luk++;
    }
    wierzcholki2 = lista_lukow[luk - 1][1];
    //ten for tworzy początkową liste łuków w takiej postaci 
    /*
    1 2
    3 4
    5 6
    i tak dalej tyle łuków ile jest wierzchołków w grafie, nie
    */
    
    //ten for ogólnie łączy łuki które symbolizują te wierzchołki które są połączone w grafie
    //np jak mamy w grafie łuk z 2 do 3 (np. 2 : 3 5 6) to robimy tak
    /*
    (1) 1 2
    (2) 3 4
    (3) 5 6
    zmieniamy na
    (1) 1 2
    (2) 3 5
    (3) 5 6

    i tak samo by trzeba było zrobić sla 5 i 6
    */
    for (int i = 1; i <= wierzcholki1; i++) {
        for (int j = 0; j < krawedzie1[i]; j++) { // te dwa fory przechodzą po wszystkich krawędzich
            int tmp = lista_lukow[i][1]; // zmienna tymczasowa zapisuje jaka cyfra została usunięta (tutaj 4)
            int tmp1 = lista_lukow[graf1[i][j]][0]; // zmienna tymczasowa zapisje na jaką cyfrę zostało zmieniene (tutaj 5)
            lista_lukow[i][1] = tmp1; // zmieniamy cyfry żeby łuki były połączone (tutaj zmieniamy 4 na 5)
            for (int k = 1; k < luk; k++) { // w tym for zmieniamy każde wystąpienie usuniętej cyfry na nową wszędzie gdze ona występuje w liście łuków
                if (lista_lukow[k][0] == tmp)
                    lista_lukow[k][0] = tmp1;
                if (lista_lukow[k][1] == tmp)
                    lista_lukow[k][1] = tmp1;
            }
        }
    }
    
    for (int i = 1; i < luk; i++) {
        int wierzcholek = lista_lukow[i][0];
        graf2[wierzcholek][krawedzie2[wierzcholek]] = lista_lukow[i][1];
        krawedzie2[wierzcholek]++;
    }
    // ten for zamienia litę łuków na graf wynikowy (graf2) w postaci listy następników
    
    // a pozostała część odpowiada za usunięcie wierzchołków izolowanych i jest pojebana, ona mi to kazała zrobić bo nie chciała izolowanych
    int nie_izolowany[MAX * 2] = { 0 };
    for (int i = 1; i <= wierzcholki2; i++) {
        if (krawedzie2[i] == 0) {
            for (int j = 1; j <= wierzcholki2; j++) {
                for (int k = 0; k < krawedzie2[j]; k++) {
                    if (graf2[j][k] == i) {
                        nie_izolowany[i] = 1;
                    }
                }
            }
        }
        else {
            nie_izolowany[i] = 1;
        }
    }
    
    for (int i = 1; i <= wierzcholki2; i++) {
        if (nie_izolowany[i] == 0) {
            for (int j = i + 1; j <= wierzcholki2; j++) {
                for (int k = 0; k < krawedzie2[j]; k++) {
                    graf2[j - 1][k] = graf2[j][k];
                }
                krawedzie2[j - 1] = krawedzie2[j];
                krawedzie2[j] = 0;
                for (int l = 1; l <= wierzcholki2; l++) {
                    for (int m = 0; m < krawedzie2[l]; m++) {
                        if (graf2[l][m] == j)
                            graf2[l][m] = j - 1;
                    }
                }
            }
            for (int k = 1; k < MAX * 2 - 1; k++) {
                nie_izolowany[k] = nie_izolowany[k + 1];
            }
            wierzcholki2--;
            i--;
        }
    }
}

bool Liniowy() {
    int k = 0;
    for (int i = 1; i <= wierzcholki2; i++) {
        for (int j = 0; j < krawedzie2[i]; j++) {
            k = j + 1;
            while (k < krawedzie2[i]) {
                if (graf2[i][j] == graf2[i][k])
                    return false;
                k++;
            }
        }
    }
    return true;
}