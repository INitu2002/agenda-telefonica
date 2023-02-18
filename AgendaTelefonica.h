#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Email.h"
#include "NrTelefon.h"
#include "Persoana.h"
using namespace std;

class AgendaTelefonica {
    Persoana* contacte = nullptr;
    int dimAgenda = 0;

public:
    static Persoana errPoint;

    AgendaTelefonica();
    AgendaTelefonica(Persoana* _contacte, int _dimAgenda);
    AgendaTelefonica(AgendaTelefonica& ag);
    AgendaTelefonica& operator=(const AgendaTelefonica& src);
    friend ostream& operator<< (ostream& out, AgendaTelefonica& a);
    friend ofstream& operator<< (ofstream& out, AgendaTelefonica& a);
    // op. indexare
    Persoana& operator[](int idx);
    void adaugaInAgenda(Persoana& pNoua);
    // stergere dupa nume + prenume
    void stergeDinAgenda();
    // stergere dupa un nr de telefon sau subsir din el
    // +30589478567
    void stergeDinAgendaDupaTel();
    // cautam subsir in nume + prenume
    void cautareSubsirNumePrenume();
    // cautam subsir in nume + prenume -> vector de persoane
    Persoana* cautareSubsirNume(string s, int& cnt);
    // cautam subsir in nrTel
    int* subsirTel(int& cnt, string s);
    // afisare dupa vector de indecsi gasit pt stergere
    void afisarePersSterseDupaTel(string s);
    // stergere dupa subsir telefon
    void stergerePersCuAnumeSubsirTel(string s);
    // sortare agenda dupa nume + prenume, iar daca sunt identice => dupa email
    void sortAgenda();
    operator Persoana*();
    // adaugare 1 persoana noua in agenda
    Persoana* operator++(int);
    // inserare n persoane noi in agenda
    Persoana* operator+ (int n);
    // afisare contacte dintr-o anumita tara (dupa prefix din numar de telefon)
    void afisarePersDinTara();
    void afisBinar(ofstream& out);
    void citireFisierBinar(ifstream& in);
    int maxNrTel();
    ~AgendaTelefonica();
};