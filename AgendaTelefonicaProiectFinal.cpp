#include <iostream>
#include "NrTelefon.h"
#include "Email.h"
#include "Persoana.h"
#include "AgendaTelefonica.h"
using namespace std;

void meniu(AgendaTelefonica a) {
    cout << "Doriti sa faceti vreo operatiune/interogare in agenda? (y/n): ";
    char rasp = 'y';
    cin.get(rasp);
    while (rasp == 'y' || rasp == 'Y') {
        cout << "\nMENIU - Optiuni:\n";
        cout << "1. Afisare agenda\n";
        cout << "2. Stergere persoane dupa nume + prenume\n";
        cout << "3. Afisare persoane dintr-o anumita tara\n";
        cout << "4. Afisare persoane cu anumit subsir in nume\n";
        cout << "5. Stergere persoane cu anumit subsir in numarul de telefon\n";
        cout << "6. Sortare alfabetica agenda\n";
        cout << "7. Adaugare o persoana noua\n";
        cout << "8. Adaugare mai multe persoane noi in agenda\n";
        cout << "9. Cautare persoana dupa index\n";

        int optiune;
        cout << "\nCe functionalitate doriti sa apelati? Dati numarul acesteia: ";
        cin >> optiune;

        if (optiune == 1) {
            cout << endl << a;
        }
        else if (optiune == 2) {
            try {
                a.stergeDinAgenda();
                cout << endl << a;
            }
            catch (const char* msg)
            {
                cerr << msg << endl;
            }
        }
        else if (optiune == 3) {
            a.afisarePersDinTara();
        }
        else if (optiune == 4) {
            a.cautareSubsirNumePrenume();
        }
        else if (optiune == 5) {
            a.stergeDinAgendaDupaTel();
            ofstream f("agendaDupaStergereTel");
            f << a;
        }
        else if (optiune == 6) {
            a.sortAgenda();
            ofstream f1("agendaSortata.txt");
            f1 << a;
            cout << endl << a;
        }
        else if (optiune == 7) {
            a++;
            cout << endl << a;
        }
        else if (optiune == 8) {
            int n;
            cout << "\nCate persoane doriti sa adaugati?: ";
            cin >> n;
            a + n;
            cout << endl << a;
        }
        else if (optiune == 9) {
            int index;
            cout << "\A cata persoana este cea cautata?: ";
            cin >> index;
            try {
                cout << "\nA " << index << "- a persoana din agenda este: " << endl;
                cout << '\t' << a[index - 1];
            }
            catch (const char* msg)
            {
                cerr << msg << endl;
            }
        }
        cout << "\nDoriti sa mai faceti vreo operatiune/interogare in agenda? (y/n): ";
        cin >> rasp;
    }
}

int main()
{
    ifstream f1("fisierIntrarePers.txt");
    int nrPers;
    f1 >> nrPers;
    Persoana* p = new Persoana[nrPers];
    for (int i = 0; i < nrPers; i++)
        f1 >> p[i];
    AgendaTelefonica a(p, nrPers);

    f1.close();
    meniu(a);
}
