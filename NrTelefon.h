#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

enum PrefixTara { Romania = 40, Suedia = 46, Germania = 49, Grecia = 30, Austria = 43 };

class AgendaTelefonica;


class NrTelefon {
    static char semn;
    PrefixTara codTara = Grecia;
    string restNumar = "";

public:
    NrTelefon();
    NrTelefon(PrefixTara _codTara, string _restNumar);
    void setRestNumar(string _restNr);
    PrefixTara& getCodTara();
    void setCodTara(PrefixTara p);
    bool operator== (const NrTelefon& t);
    friend ostream& operator<< (ostream& out, const NrTelefon t);
    friend ofstream& operator<< (ofstream& out, const NrTelefon t);
    void afisBinar(ofstream& out);
    void citireBinar(ifstream& in);
    friend ifstream& operator>> (ifstream& in, NrTelefon& t);
    friend istream& operator>> (istream& in, NrTelefon& t);
    friend string getRestNumar(NrTelefon t, AgendaTelefonica& a);
};
