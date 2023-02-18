#include "AgendaTelefonica.h"
#include "Persoana.h"
#include "Email.h"
#include "NrTelefon.h"

Persoana AgendaTelefonica::errPoint = Persoana("Nu exista persoana!");

AgendaTelefonica::AgendaTelefonica() {
    contacte = nullptr;
    dimAgenda = 0;
}

AgendaTelefonica::AgendaTelefonica(Persoana* _contacte, int _dimAgenda) : dimAgenda(_dimAgenda) {
    if (contacte != nullptr)
        delete[] contacte;
    contacte = nullptr;

    if (dimAgenda > 0 && _contacte != nullptr) {
        contacte = new Persoana[dimAgenda];
        for (int i = 0; i < dimAgenda; i++)
            contacte[i] = _contacte[i];
    }
}

AgendaTelefonica::AgendaTelefonica(AgendaTelefonica& ag) {
    dimAgenda = ag.dimAgenda;
    if (contacte != nullptr)
        delete[] contacte;
    contacte = nullptr;

    if (dimAgenda > 0 && ag.contacte != nullptr) {
        contacte = new Persoana[dimAgenda];
        for (int i = 0; i < dimAgenda; i++)
            contacte[i] = ag.contacte[i];
    }
}

AgendaTelefonica& AgendaTelefonica::operator=(const AgendaTelefonica& src) {
    if (this != &src) {
        dimAgenda = src.dimAgenda;
        if (contacte != nullptr)
            delete[] contacte;
        contacte = nullptr;

        if (dimAgenda > 0 && src.contacte != nullptr) {
            contacte = new Persoana[dimAgenda];
            for (int i = 0; i < dimAgenda; i++)
                contacte[i] = src.contacte[i];
        }
    }
    return *this;
}

ostream& operator<< (ostream& out, AgendaTelefonica& a) {
    out << "In agenda sunt " << a.dimAgenda << " persoane:\n";
    if (a.dimAgenda > 0)
        for (int i = 0; i < a.dimAgenda; i++)
            out << '\t' << a.contacte[i];
    return out;
}

ofstream& operator<< (ofstream& out, AgendaTelefonica& a) {
    out << "In agenda sunt " << a.dimAgenda << " persoane:\n";
    if (a.dimAgenda > 0)
        for (int i = 0; i < a.dimAgenda; i++)
            out << '\t' << a.contacte[i];
    return out;
}

Persoana& AgendaTelefonica::operator[](int idx) {
    if (idx >= 0 && idx < dimAgenda)
    {
        return contacte[idx];
    }
    else
        throw "Nu exista persoana cautata in agenda!";
}

void AgendaTelefonica::adaugaInAgenda(Persoana& pNoua) {
    dimAgenda++;
    Persoana* contacteVechi = contacte;

    contacte = new Persoana[dimAgenda];
    for (int i = 0; i < dimAgenda - 1; i++)
        contacte[i] = contacteVechi[i];
    contacte[dimAgenda - 1] = pNoua;

    if (contacteVechi != nullptr) {
        delete[] contacteVechi;
        contacteVechi = nullptr;
    }
}

void AgendaTelefonica::stergeDinAgenda() {
    string _nume, _prenume;
    cout << "Dati numele persoanei pe care vreti sa o stergeti: ";
    cin >> _nume;
    cout << "Dati prenumele persoanei pe care vreti sa o stergeti: ";
    cin >> _prenume;

    // _nume si _prenume sa inceapa cu majuscula (inseram initiala pe poz 0, o data)
    string _numeMajuscula = _nume.substr(1, _nume.length()).insert(0, 1, toupper(_nume[0]));
    string _prenumeMajuscula = _prenume.substr(1, _prenume.length()).insert(0, 1, toupper(_prenume[0]));
    if (dimAgenda > 0) {
        Persoana* contacteVechi = new Persoana[dimAgenda];
        for (int i = 0; i < dimAgenda; i++)
            contacteVechi[i] = contacte[i];

        int idxCautat = -1;
        for (int i = 0; i < dimAgenda; i++)
            if (((string)contacteVechi[i] == _nume && strcmp(contacteVechi[i].getPrenume(), _prenume.c_str()) == 0)
                || ((string)contacteVechi[i] == _numeMajuscula &&
                    strcmp(contacteVechi[i].getPrenume(), _prenumeMajuscula.c_str()) == 0))
            {
                idxCautat = i; cout << "S-a realizat stergerea!\n";
            }
        if (idxCautat == -1) {
            throw "Persoana cautata nu exista in agenda!";
        }
        else if (idxCautat != -1) {
            dimAgenda--;
            delete[] contacte;
            contacte = new Persoana[dimAgenda];

            for (int i = 0; i < dimAgenda + 1; i++)
                if (i <= idxCautat)
                    contacte[i] = contacteVechi[i];
                else if (i > idxCautat)
                    contacte[i - 1] = contacteVechi[i];
        }

        if (contacteVechi != nullptr) {
            delete[] contacteVechi;
            contacteVechi = nullptr;
        }
    }
    else
        cout << "\nNu exista niciun nr de telefon in agenda!";
}

void AgendaTelefonica::stergeDinAgendaDupaTel() {
    string tel;
    cout << "Dati intreg numarul de telefon sau un subsir din el: ";
    cin >> tel;
    if (tel.length() == 12) {
        string _restNr = tel.substr(3, 9);
        int prefix = stoi(tel.substr(1, 2)); // string to int
        if (dimAgenda > 0) {
            dimAgenda--;

            Persoana* contacteVechi = contacte;
            contacte = new Persoana[dimAgenda];

            int idxCautat;
            for (int i = 0; i < dimAgenda + 1; i++)
                if (((NrTelefon)contacteVechi[i]).getCodTara() == prefix && _restNr ==
                    getRestNumar((NrTelefon)contacteVechi[i], *this))
                {
                    idxCautat = i; break;
                }
            for (int i = 0; i < dimAgenda + 1; i++)
                if (i < idxCautat)
                    contacte[i] = contacteVechi[i];
                else if (i > idxCautat)
                    contacte[i - 1] = contacteVechi[i];

            if (contacteVechi != nullptr) {
                delete[] contacteVechi;
                contacteVechi = nullptr;
            }
        }
        else
            cout << "\nNu exista niciun nr de telefon in agenda!";
    }
    else
        stergerePersCuAnumeSubsirTel(tel);
}

void AgendaTelefonica::cautareSubsirNumePrenume() {
    string s;
    cout << "\nDati subsirul de cautat in nume si prenume: ";
    cin >> s;
    int cnt = 0;
    if (dimAgenda > 0) {
        for (int i = 0; i < dimAgenda; i++) {
            if (strstr(((string)contacte[i]).c_str(), s.c_str()) || strstr(contacte[i].getPrenume(), s.c_str())) {
                cnt++;
                cout << '\t' << contacte[i];
            }
        }
        if (cnt == 0)
            cout << "Nu exista nicio persoana cu (pre)nume care contine '" << s << "'!\n";
    }
    else
        cout << "\nNu exista niciun nr de telefon in agenda!";
}

// cautam subsir in nume + prenume -> vector de persoane
Persoana* AgendaTelefonica::cautareSubsirNume(string s, int& cnt) {
    cnt = 0;
    Persoana* persCuSubsir = nullptr;
    if (dimAgenda > 0) {
        for (int i = 0; i < dimAgenda; i++)
            if (strstr(((string)contacte[i]).c_str(), s.c_str()) || strstr(contacte[i].getPrenume(), s.c_str()))
                cnt++;
        if (cnt == 0)
            cout << "Nu exista nicio persoana cu (pre)nume care contine '" << s << "'!\n";
        else
            persCuSubsir = new Persoana[cnt];
        int j = 0;
        while (j < cnt) {
            for (int i = 0; i < dimAgenda; i++)
                if (strstr(((string)contacte[i]).c_str(), s.c_str()) || strstr(contacte[i].getPrenume(), s.c_str()))
                    persCuSubsir[j++] = contacte[i];
        }
        return persCuSubsir;
    }
    else {
        cout << "\nNu exista niciun nr de telefon in agenda!";
        return nullptr;
    }
}

int* AgendaTelefonica::subsirTel(int& cnt, string s) {
    cnt = 0;
    int* persCuSubsir = nullptr; // vector de indecsi ai pers cu subsir in nr de tel
    if (dimAgenda > 0) {
        for (int i = 0; i < dimAgenda; i++)
        {
            // construiesc un string din codTara (care este de tipul PrefixTara) si restNumar (de tip string)
            // si verif daca in acest string nou creat exista string-ul cautat
            int prefix;
            switch (((NrTelefon)contacte[i]).getCodTara()) {
            case Romania: {prefix = 40; break; }
            case Grecia: {prefix = 30; break; }
            case Germania: {prefix = 49; break; }
            case Suedia: {prefix = 46; break; }
            case Austria: {prefix = 43; break; }
            }
            string tel = to_string(prefix) + getRestNumar((NrTelefon)contacte[i], *this);
            if (strstr(tel.c_str(), s.c_str()))
            {
                cnt++;
                //cout << '\t' << contacte[i];
            }
        }
        if (cnt == 0)
            cout << "Nu exista nicio persoana cu numar de telefon care contine '" << s << "'!\n";
        else {
            persCuSubsir = new int[cnt];
            int j = 0;
            while (j < cnt)
                for (int i = 0; i < dimAgenda; i++) {
                    int prefix;
                    switch (((NrTelefon)contacte[i]).getCodTara()) {
                    case Romania: {prefix = 40; break; }
                    case Grecia: {prefix = 30; break; }
                    case Germania: {prefix = 49; break; }
                    case Suedia: {prefix = 46; break; }
                    case Austria: {prefix = 43; break; }
                    }
                    string tel = to_string(prefix) + getRestNumar((NrTelefon)contacte[i], *this);
                    if (strstr(tel.c_str(), s.c_str()))
                        persCuSubsir[j++] = i;
                }
            return persCuSubsir;
            afisarePersSterseDupaTel(s);
        }
    }
    else
        cout << "\nNu exista niciun nr de telefon in agenda!";
}

void AgendaTelefonica::afisarePersSterseDupaTel(string s) { // s = subsir cautat in tel
    Persoana* contacteVechi = new Persoana[dimAgenda];
    for (int i = 0; i < dimAgenda; i++)
        contacteVechi[i] = contacte[i];

    int cnt;
    int* v = subsirTel(cnt, s); // vector de indecsi ai persoanelor cu subsirul cautat
    if (cnt == 0)
        cout << "\nNu avem ce sterge! Nu s-a gasit subsirul in niciun telefon!\n";
    else if (cnt == 1)
        cout << "\Persoana stearsa este:\n";
    else
        cout << "\nPersoanele sterse sunt:\n";
    for (int i = 0; i < dimAgenda; i++)
        for (int j = 0; j < cnt; j++)
            if (i == v[j])
                cout << '\t' << contacteVechi[i];
}

void AgendaTelefonica::stergerePersCuAnumeSubsirTel(string s) {
    Persoana* contacteVechi = new Persoana[dimAgenda];
    for (int i = 0; i < dimAgenda; i++)
        contacteVechi[i] = contacte[i];

    int cnt; // cate pers au acel subsir
    int* p = subsirTel(cnt, s); // vector de indecsi

    afisarePersSterseDupaTel(s);

    dimAgenda -= cnt;
    for (int i = 0; i < dimAgenda + cnt; i++)
        for (int j = 0; j < cnt; j++)
        {
            if (i < p[j])
                contacte[i] = contacteVechi[i];
            else if (i > p[j])
                contacte[i - 1] = contacteVechi[i];
        }

    if (contacteVechi != nullptr)
        delete[] contacteVechi;
}

void AgendaTelefonica::sortAgenda() {
    if (dimAgenda == 0)
        cout << "\nNu exista contacte in agenda! Nu avem ce sorta!\n";
    else
        for (int i = 0; i < dimAgenda - 1; i++)
            for (int j = i + 1; j < dimAgenda; j++)
                if (contacte[i] > contacte[j]) // testam doar nume + prenume
                {
                    Persoana temp = contacte[i];
                    contacte[i] = contacte[j];
                    contacte[j] = temp;
                }
                else if (contacte[i] == contacte[j])
                    if (((Email)contacte[i]).getIdentificatorPlatforma() > ((Email)contacte[j]).getIdentificatorPlatforma())
                    {
                        Persoana temp = contacte[i];
                        contacte[i] = contacte[j];
                        contacte[j] = temp;
                    }
                    else if (((Email)contacte[i]).getIdentificatorPlatforma() == ((Email)contacte[j]).getIdentificatorPlatforma()
                        && ((Email)contacte[i]).getIdentificatorTara() > ((Email)contacte[j]).getIdentificatorTara())
                    {
                        Persoana temp = contacte[i];
                        contacte[i] = contacte[j];
                        contacte[j] = temp;
                    }
}

AgendaTelefonica::operator Persoana*() {
    return contacte;
}

Persoana* AgendaTelefonica::operator++(int) {
    dimAgenda++;
    Persoana* contacteVechi = new Persoana[dimAgenda - 1];
    for (int i = 0; i < dimAgenda - 1; i++)
        contacteVechi[i] = contacte[i];

    delete[] contacte;

    contacte = new Persoana[dimAgenda];
    for (int i = 0; i < dimAgenda - 1; i++)
        contacte[i] = contacteVechi[i];

    Persoana p1;
    cin >> p1;
    contacte[dimAgenda - 1] = p1;

    if (contacteVechi != nullptr) {
        delete[] contacteVechi;
        contacteVechi = nullptr;
    }

    return contacte;
}

Persoana* AgendaTelefonica::operator+ (int n) {
    dimAgenda += n;
    Persoana* contacteVechi = new Persoana[dimAgenda - n];
    for (int i = 0; i < dimAgenda - n; i++)
        contacteVechi[i] = contacte[i];
    delete[] contacte;

    contacte = new Persoana[dimAgenda];
    for (int i = 0; i < dimAgenda - n; i++)
        contacte[i] = contacteVechi[i];

    // introducere/citire persoane noi (n)
    for (int i = 0; i < n; i++) {
        cout << "\nDati persoana " << i + 1 << " adaugata:";
        Persoana p;
        cin >> p;
        contacte[dimAgenda + i - 2] = p;
    }

    if (contacteVechi != nullptr) {
        delete[] contacteVechi;
        contacteVechi = nullptr;
    }

    return contacte;
}

void AgendaTelefonica::afisarePersDinTara() {
    string tara;
    cout << "\nDati tara dorita: ";
    cin >> tara;
    int cnt = 0;
    for (int i = 0; i < dimAgenda; i++) {
        int codT = 0;
        if (tara == "Romania" || tara == "romania")
            codT = 40;
        else if (tara == "Grecia" || tara == "grecia")
            codT = 30;
        else if (tara == "Austria" || tara == "austria")
            codT = 43;
        else if (tara == "Germania" || tara == "germania")
            codT = 49;
        else if (tara == "Suedia" || tara == "suedia")
            codT = 46;
        else {
            cout << "Nu exista tara cautata!\n"; cnt = 1000; break;
        }
        if (((NrTelefon)contacte[i]).getCodTara() == codT)
        {
            cout << '\t' << contacte[i];
            cnt++;
        }
    }
    if (cnt == 0)
        cout << "Nu exista nicio persoana din tara \"" << tara << "\" in agenda!\n";
}

void AgendaTelefonica::afisBinar(ofstream& out) {
    for (int i = 0; i < dimAgenda; i++)
        contacte[i].afisareFisierBinar(out);
}

void AgendaTelefonica::citireFisierBinar(ifstream& in) {
    for (int i = 0; i < dimAgenda; i++)
        contacte[i].citireFisierBinar(in);
}

int AgendaTelefonica::maxNrTel() {
    int maxim = contacte[0].getCateTel();
    for (int i = 1; i < dimAgenda; i++) {
        if (contacte[i].getCateTel() > maxim)
            maxim = contacte[i].getCateTel();
    }
    return maxim;
}

AgendaTelefonica::~AgendaTelefonica() {
    if (contacte != nullptr) {
        delete[] contacte;
        contacte = nullptr;
    }
}
