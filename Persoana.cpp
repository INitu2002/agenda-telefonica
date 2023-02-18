#include "Persoana.h"
#include "Email.h"
#include "NrTelefon.h"

Persoana::Persoana() {}

Persoana::Persoana(string _nume) {
	nume = _nume;
}

Persoana::Persoana(string _nume, const char* _prenume, int _cateTel, NrTelefon* _tel, Email& _email) {
    nume = _nume;
    if (prenume != nullptr) {
        delete[] prenume;
        prenume = nullptr;
    }
    if (_prenume != nullptr) {
        prenume = new char[strlen(_prenume) + 1];
        strcpy(prenume, _prenume);
    }

    cateTel = _cateTel;
    if (_tel != nullptr) {
        tel = new NrTelefon[cateTel];
        for (int i = 0; i < cateTel; i++)
            tel[i] = _tel[i];
    }

    email = _email;

    setNume(email, *this);
    if (prenume != nullptr)
        setPrenume(email, *this);
}

Persoana::Persoana(const Persoana& p) {
    nume = p.nume;
    if (prenume != nullptr) {
        delete[] prenume;
        prenume = nullptr;
    }

    if (p.prenume != nullptr) {
        prenume = new char[strlen(p.prenume) + 1];
        strcpy(prenume, p.prenume);
    }
    cateTel = p.cateTel;
    if (p.tel != nullptr) {
        tel = new NrTelefon[cateTel];
        for (int i = 0; i < cateTel; i++)
            tel[i] = p.tel[i];
    }

    email = p.email;
}

Persoana& Persoana::operator= (const Persoana& src) {
    if (this != &src) {
        nume = src.nume;
        if (prenume != nullptr) {
            delete[] prenume;
            prenume = nullptr;
        }

        if (src.prenume != nullptr) {
            prenume = new char[strlen(src.prenume) + 1];
            strcpy(prenume, src.prenume);
        }
        cateTel = src.cateTel;
        if (src.tel != nullptr) {
            tel = new NrTelefon[cateTel];
            for (int i = 0; i < cateTel; i++)
                tel[i] = src.tel[i];
        }

        email = src.email;
    }
    return *this;
}

ostream& operator<< (ostream& out, Persoana& p) {
    out << p.nume << "\t" << p.prenume << "\t";
    out << p.email << '\t';
    if (p.cateTel > 0)
        for (int i = 0; i < p.cateTel; i++)
            out << p.tel[i] << '\t';
    out << endl;
    return out;
}

ofstream& operator<< (ofstream& out, Persoana& p) {
    out << p.nume << "\t" << p.prenume << "\t";
    out << p.email << '\t';
    if (p.cateTel > 0)
        for (int i = 0; i < p.cateTel; i++)
            out << p.tel[i] << '\t';
    out << endl;
    return out;
}

ifstream& operator>> (ifstream& in, Persoana& p) {
    in >> p.nume;
    string s;
    in >> s;
    p.prenume = new char[s.length() + 1];
    strcpy(p.prenume, s.c_str());
    setNume(p.email, p);
    setPrenume(p.email, p);
    in >> p.cateTel;
    p.tel = new NrTelefon[p.cateTel];
    for (int i = 0; i < p.cateTel; i++)
        in >> p.tel[i];
    in >> p.email;

    setIdentifTara(p.tel[0], p.email);
    return in;
}

istream& operator>> (istream& in, Persoana& p) {
    in >> p.email;
    cout << "Numarul de numere de telefon: ";
    in >> p.cateTel;
    p.tel = new NrTelefon[p.cateTel];
    string tara;
    tara = p.email.getIdentificatorTara();

    for (int i = 0; i < p.cateTel; i++) {
        if (tara == "ro")
            p.tel[i].getCodTara() = Romania;
        else if (tara == "el")
            p.tel[i].getCodTara() = Grecia;
        else if (tara == "at")
            p.tel[i].getCodTara() = Austria;
        else if (tara == "de")
            p.tel[i].getCodTara() = Germania;
        else if (tara == "se")
            p.tel[i].getCodTara() = Suedia;
        cout << "Dati nr de telefon (" << i + 1 << ") format din 9 cifre: ";
        in >> p.tel[i];
    }
    p.nume = ((Email)p).getNumeUtiliz();
    p.nume[0] = toupper(p.nume[0]);

    if (p.prenume != nullptr)
        delete[] p.prenume;
    p.prenume = new char[((Email)p).getPrenumeUtilizator().length() + 1];
    strcpy(p.prenume, ((Email)p).getPrenumeUtilizator().c_str());
    p.prenume[0] = toupper(p.prenume[0]);

    return in;
}

bool Persoana::operator>(Persoana& p) {
    if (strcmp(nume.c_str(), (p.nume).c_str()) < 0)
        return false;
    else if (strcmp(nume.c_str(), p.nume.c_str()) == 0 && strcmp(prenume, p.prenume) < 1)
        return false;
    return true;
}

bool Persoana::operator==(const Persoana& p) {
    if (this->nume == p.nume && strcmp(prenume, p.prenume) == 0
        && tel == p.tel && email == p.email)
        return true;
    else return false;
}

bool Persoana::operator!=(const Persoana& p) {
    if (*this == p)
        return false;
    else return true;
}

Persoana::operator string() {
    return nume;
}

char* Persoana::getPrenume() {
    return prenume;
}

Persoana::operator NrTelefon&() {
    return tel[0];
}

Persoana::operator Email() {
    return email;
}

int& Persoana::getCateTel() {
    return cateTel;
}

void Persoana::salveazaInFisCSV(ofstream& out) {
    out << this->nume << ";";
    out << this->prenume << ";";
    out << this->email << ";";
    for (int i = 0; i < this->cateTel; i++)
        out << this->tel[i] << ";";
    out << endl;
}

ifstream& operator>> (Persoana& p, ifstream& in) {
    string line, word[5], temp;
    getline(in, line); // am citit toata linia
    stringstream s(line); // pt a imparti linia
    for (int i = 0; i < 5; i++)
        getline(s, word[i], ';');
    p.nume = word[0];
    p.prenume = new char[word[1].length() + 1];
    strcpy(p.prenume, word[1].c_str());
    p.email.getNumeUtiliz() = word[2].substr(0, word[0].length());
    p.email.getPrenumeUtilizator() = word[2].substr(p.nume.length() + 1, ((string)p.prenume).length());
    p.email.getIdentificatorPlatforma() = word[2].substr(p.nume.length() + 1 + ((string)p.prenume).length() + 1, 5);
    p.email.setIdentifTara(word[2].substr(p.nume.length() + 1 + ((string)p.prenume).length() + 7, 2));
    p.getCateTel() = stoi(word[3]);
    (p.tel[0]).setRestNumar(word[4]);
    ((NrTelefon)p).getCodTara() = Germania;
    return in;
}

void Persoana::afisareFisierBinar(ofstream& out) {
    int lungime = this->nume.length();
    out.write((char*)&lungime, sizeof(lungime));
    out.write(this->nume.c_str(), lungime);
    lungime = ((string)prenume).length();
    out.write((char*)&lungime, sizeof(lungime));
    out.write(this->prenume, lungime);
    email.afisBinar(out);
    out.write((char*)&cateTel, sizeof(cateTel));
    for (int i = 0; i < cateTel; i++)
        tel[i].afisBinar(out);
}

void Persoana::citireFisierBinar(ifstream& in) {
    int lungime = 0;
    in.read((char*)&lungime, sizeof(lungime));
    nume.resize(lungime);
    in.read((char*)nume.c_str(), lungime);
    lungime = 0;
    in.read((char*)&lungime, sizeof(lungime));
    if (prenume != nullptr)
        delete[] prenume;
    prenume = new char[lungime];
    in.read(prenume, lungime);
    email.citireBinar(in);
    in.read((char*)&cateTel, sizeof(cateTel));
    for (int i = 0; i < cateTel; i++)
        tel[i].citireBinar(in);
}

Persoana::~Persoana() {
    if (prenume != nullptr)
        delete[] prenume;
    prenume = nullptr;
    if (tel != nullptr)
        delete[] tel;
    tel = nullptr;
}

void setNume(Email& e, Persoana& p)
{
    int size = p.nume.size();
    e.numeUtiliz = (char)(p.nume[0] + 32) + p.nume.substr(1, size - 1);
}

void setPrenume(Email& e, Persoana& p)
{
    int size = strlen(p.prenume);
    string s(p.prenume);
    e.prenumeUtiliz = (char)(p.prenume[0] + 32) + s.substr(1, size - 1);
}