#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "NrTelefon.h"
using namespace std;

class Persoana;
class NrTelefon;

class Email {
    string numeUtiliz = "popescu";
    char separatorInitial = '.';
    string prenumeUtiliz = "ioana";
    static char caracterSpecial; // @
    string identificatorPlatforma = "yahoo";
    static char separatorFinal; // '.'
    char* identifTara = nullptr;

public:
    Email();
    Email(string nume, string prenume, char _separatorInitial, string _identificatorPlatforma, const char* _identifTara = "");
    Email& operator= (const Email& e);
    Email(const Email& src);
    bool operator==(const Email& e);
    friend ostream& operator<< (ostream& out, Email& e);
    friend ofstream& operator<< (ofstream& out, Email& e);
    void afisBinar(ofstream& out);
    void citireBinar(ifstream& in);
    friend ifstream& operator>> (ifstream& in, Email& e);
    friend istream& operator>> (istream& in, Email& e);
    bool operator< (Email& e);
    static char getCaracterSpecial();
    string getIdentificatorPlatforma();
    char* getIdentificatorTara();
    void setIdentifTara(string s);
    string& getNumeUtiliz();
    string& getPrenumeUtilizator();
    ~Email();
    friend void setNume(Email& e, Persoana& p);
    friend void setPrenume(Email& e, Persoana& p);
    friend void setIdentifTara(NrTelefon& t, Email& e);
};