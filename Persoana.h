#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Email.h"
#include "NrTelefon.h"
using namespace std;

class Persoana {
    string nume = "";
    char* prenume = nullptr;
    int cateTel = 0;
    NrTelefon* tel = nullptr;
    Email email;

public:
    Persoana();
    Persoana(string _nume);
    Persoana(string _nume, const char* _prenume, int _cateTel, NrTelefon* _tel, Email& _email);
    Persoana(const Persoana& p);
    Persoana& operator= (const Persoana& src);
    friend ostream& operator<< (ostream& out, Persoana& p);
    friend ofstream& operator<< (ofstream& out, Persoana& p);
    friend ifstream& operator>> (ifstream& in, Persoana& p);
    // prefixul din nr de telefon este preluat din identificatorul de tara al email-ului
    friend istream& operator>> (istream& in, Persoana& p);
    // comparare persoane dupa nume
    bool operator>(Persoana& p);
    // verif daca 2 persoane sunt identice
    bool operator==(const Persoana& p);
    bool operator!=(const Persoana& p);
    operator string();
    char* getPrenume();
    operator NrTelefon&();
    operator Email();
    int& getCateTel();
    void salveazaInFisCSV(ofstream& out);
    friend ifstream& operator>> (Persoana& p, ifstream& in);
    void afisareFisierBinar(ofstream& out);
    void citireFisierBinar(ifstream& in);
    ~Persoana();
private:
    friend void setNume(Email& e, Persoana& p);
    friend void setPrenume(Email& e, Persoana& p);
};