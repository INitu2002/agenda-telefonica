#include "Email.h"
#include "NrTelefon.h"

char Email::caracterSpecial = '@';
char Email::separatorFinal = '.';

Email::Email() {}

Email::Email(string nume, string prenume, char _separatorInitial, string _identificatorPlatforma, const char* _identifTara)
    :numeUtiliz(nume), prenumeUtiliz(prenume) {
    separatorInitial = _separatorInitial;
    identificatorPlatforma = _identificatorPlatforma;

    if (identifTara != nullptr) {
        delete[] identifTara;
        identifTara = nullptr;
    }

    if (_identifTara != nullptr) {
        identifTara = new char[strlen(_identifTara) + 1];
        strcpy(identifTara, _identifTara);
    }
}

Email& Email::operator= (const Email& e) {
    numeUtiliz = e.numeUtiliz;
    prenumeUtiliz = e.prenumeUtiliz;
    separatorInitial = e.separatorInitial;
    identificatorPlatforma = e.identificatorPlatforma;

    if (identifTara != nullptr) {
        delete[] identifTara;
        identifTara = nullptr;
    }

    if (e.identifTara != nullptr) {
        identifTara = new char[strlen(e.identifTara) + 1];
        strcpy(identifTara, e.identifTara);
    }
    return *this;
}

Email::Email(const Email& src) {
    numeUtiliz = src.numeUtiliz;
    separatorInitial = src.separatorInitial;
    prenumeUtiliz = src.prenumeUtiliz;
    identificatorPlatforma = src.identificatorPlatforma;

    if (identifTara != nullptr) {
        delete[] identifTara;
        identifTara = nullptr;
    }

    if (src.identifTara != nullptr) {
        identifTara = new char[strlen(src.identifTara) + 1];
        strcpy(identifTara, src.identifTara);
    }
}

bool Email::operator==(const Email& e) {
    if (numeUtiliz == e.numeUtiliz && separatorInitial == e.separatorInitial
        && prenumeUtiliz == e.prenumeUtiliz && identificatorPlatforma == e.identificatorPlatforma
        && strcmp(identifTara, e.identifTara) == 0)
        return true;
    else return false;
}

ostream& operator<< (ostream& out, Email& e) {
    out << e.numeUtiliz << e.separatorInitial << e.prenumeUtiliz << e.caracterSpecial << e.identificatorPlatforma <<
        e.separatorFinal << e.identifTara;
    return out;
}

ofstream& operator<< (ofstream& out, Email& e) {
    out << e.numeUtiliz << e.separatorInitial << e.prenumeUtiliz << e.caracterSpecial << e.identificatorPlatforma <<
        e.separatorFinal << e.identifTara;
    return out;
}

void Email::afisBinar(ofstream& out) {
    int lungime = this->numeUtiliz.length();
    out.write((char*)&lungime, sizeof(lungime));
    out.write(this->numeUtiliz.c_str(), lungime);
    out.write((char*)&this->separatorInitial, sizeof(char));
    lungime = this->prenumeUtiliz.length();
    out.write((char*)&lungime, sizeof(lungime));
    out.write(this->prenumeUtiliz.c_str(), lungime);
    out.write((char*)&this->caracterSpecial, sizeof(char));
    lungime = this->identificatorPlatforma.length();
    out.write((char*)&lungime, sizeof(lungime));
    out.write(this->identificatorPlatforma.c_str(), lungime);
    out.write((char*)&this->separatorFinal, sizeof(char));
    lungime = ((string)identifTara).length();
    out.write((char*)&lungime, sizeof(lungime));
    out.write(this->identifTara, lungime);
}

void Email::citireBinar(ifstream& in) {
    int lungime = 0;
    in.read((char*)&lungime, sizeof(lungime));
    numeUtiliz.resize(lungime);
    in.read((char*)numeUtiliz.c_str(), lungime);
    in.read((char*)&separatorInitial, sizeof(separatorInitial));
    lungime = 0;
    in.read((char*)&lungime, sizeof(lungime));
    prenumeUtiliz.resize(lungime);
    in.read((char*)prenumeUtiliz.c_str(), lungime);
    in.read((char*)&caracterSpecial, sizeof(caracterSpecial));
    lungime = 0;
    in.read((char*)&lungime, sizeof(lungime));
    identificatorPlatforma.resize(lungime);
    in.read((char*)identificatorPlatforma.c_str(), lungime);
    in.read((char*)&separatorFinal, sizeof(separatorFinal));
    lungime = 0;
    in.read((char*)&lungime, sizeof(lungime));
    if (identifTara != nullptr)
        delete[] identifTara;
    identifTara = new char[lungime];
    in.read(identifTara, lungime);
}

ifstream& operator>> (ifstream& in, Email& e) {
    char c;
    in >> c;
    e.separatorInitial = c;

    if (e.identifTara != nullptr)
        delete[] e.identifTara;
    e.identifTara = nullptr;

    in >> e.identificatorPlatforma;
    return in;
}

istream& operator>> (istream& in, Email& e) {
    cout << "\nDati email-ul noii persoane: ";
    string em;
    in >> em;
    char* em1 = new char[em.length() + 1]; // string to char*
    strcpy(em1, em.c_str());

    e.numeUtiliz = strtok(em1, ".");
    delete[] em1;
    em1 = new char[em.length() - e.numeUtiliz.length() + 1]; // realocam vectorul de char
    em = em.substr(e.numeUtiliz.length() + 1, em.length()); // de la separator incolo
    strcpy(em1, em.c_str());
    e.prenumeUtiliz = strtok(em1, "@");

    delete[] em1;
    em1 = new char[em.length() - e.prenumeUtiliz.length() + 1];
    em = em.substr(e.prenumeUtiliz.length() + 1, em.length());
    strcpy(em1, em.c_str());
    e.identificatorPlatforma = strtok(em1, ".");

    delete[] em1;
    em1 = new char[em.length() - e.identificatorPlatforma.length() + 1];
    em = em.substr(e.identificatorPlatforma.length() + 1, em.length());
    strcpy(em1, em.c_str());
    e.identifTara = new char[3];
    e.identifTara = strtok(em1, "\0");

    return in;
}

bool Email::operator< (Email& e) {
    if (this->identificatorPlatforma < e.identificatorPlatforma)
        return true;
    else if (this->identificatorPlatforma == e.identificatorPlatforma)
        if (this->identifTara < e.identifTara)
            return true;
        else return false;
    else return false;
}

char Email::getCaracterSpecial() {
    return caracterSpecial;
}

string Email::getIdentificatorPlatforma() {
    return identificatorPlatforma;
}

char* Email::getIdentificatorTara() {
    return identifTara;
}

void Email::setIdentifTara(string s) {
    identifTara = new char[s.length() + 1];
    strcpy(identifTara, s.c_str());
}

string& Email::getNumeUtiliz() {
    return numeUtiliz;
}

string& Email::getPrenumeUtilizator() {
    return prenumeUtiliz;
}

Email::~Email() {
    if (identifTara != nullptr)
        delete[] identifTara;
    identifTara = nullptr;
}

void setIdentifTara(NrTelefon& t, Email& e) {
    e.identifTara = new char[3];
    switch (t.getCodTara()) {
    case Romania: {strcpy(e.identifTara, "ro"); break; }
    case Grecia: {strcpy(e.identifTara, "el"); break; }
    case Germania: {strcpy(e.identifTara, "de"); break; }
    case Suedia: {strcpy(e.identifTara, "se"); break; }
    case Austria: {strcpy(e.identifTara, "at"); break; }
    }
}