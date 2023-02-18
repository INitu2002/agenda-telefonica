#include "NrTelefon.h"

NrTelefon::NrTelefon() {}
NrTelefon::NrTelefon(PrefixTara _codTara, string _restNumar) : restNumar(_restNumar){
    codTara = _codTara;
}

void NrTelefon::setRestNumar(string _restNr) {
    if (_restNr.length() == 9)
        restNumar = _restNr;
}

PrefixTara& NrTelefon::getCodTara() {
    return codTara;
}

void NrTelefon::setCodTara(PrefixTara p) {
    codTara = p;
}

bool NrTelefon::operator== (const NrTelefon& t) {
    if (codTara == t.codTara && restNumar == t.restNumar)
        return true;
    else
        return false;
}

void NrTelefon::afisBinar(ofstream& out) {
    out.write((char*)&this->semn, sizeof(this->semn));
    out.write((char*)&this->codTara, sizeof(this->codTara));
    int lungime = restNumar.length();
    out.write((char*)&lungime, sizeof(lungime));
    out.write(this->restNumar.c_str(), lungime);
}

void NrTelefon::citireBinar(ifstream& in) {
    char semn1;
    in.read((char*)&semn1, sizeof(semn1));
    PrefixTara cod;
    in.read((char*)&cod, sizeof(cod));
    switch (cod) {
    case 30: codTara = Grecia; break;
    case 40: codTara = Romania; break;
    case 49: codTara = Germania; break;
    case 46: codTara = Suedia; break;
    case 43: codTara = Austria; break;
    }
    int lungime = 0;
    in.read((char*)&lungime, sizeof(lungime));
    restNumar.resize(lungime);
    in.read((char*)restNumar.c_str(), lungime);
}

ostream& operator<< (ostream& out, const NrTelefon t) {
    out << t.semn << t.codTara << t.restNumar;
    return out;
}

ofstream& operator<< (ofstream& out, const NrTelefon t) {
    out << t.semn << t.codTara << t.restNumar;
    return out;
}

ifstream& operator>> (ifstream& in, NrTelefon& t) {
    int prefix;
    in >> prefix;
    switch (prefix) {
    case 40: {t.codTara = Romania; break; }
    case 46: {t.codTara = Suedia; break; }
    case 49: {t.codTara = Germania; break; }
    case 30: {t.codTara = Grecia; break; }
    case 43: {t.codTara = Austria; break; }
    }
    in >> t.restNumar;
    return in;
}

istream& operator>> (istream& in, NrTelefon& t) {
    string nrT;
    in >> nrT;
    if (nrT.length() == 9) {
        t.restNumar = nrT.substr(0, nrT.length());
        return in;
    }
    else {
        cout << "\nNr introdus gresit!";
    }
}

string getRestNumar(NrTelefon t, AgendaTelefonica& a) {
    return t.restNumar;
}

char NrTelefon::semn = '+';