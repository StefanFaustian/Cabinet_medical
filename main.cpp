// Cabinetul medical Mercy este alcatuit din urmatoarele entitati:
// Pacientii - sunt cei care vin la cabinet pentru a beneficia de servicii medicale
// Medicii - sunt cei care efectueaza serviciile medicale
// Programarile - sunt generate de pacienti pentru medici
// Consultatiile - reprezinta scopul programarilor si sunt realizate de medici pentru pacienti
// Retetele - sunt generate dupa o consultatie

#include <iostream>
#include <cstring>

//--- Functii de prelucrare a sirurilor de caractere ---//
char* trim(const char* str) {
    int i = 0;
    while (str[i] == ' ')
        i++;
    int n = strlen(str);
    while (n >= 0 && str[n-1] == ' ')
        n--;

    char* rez = new char[n + 2];
    strncpy(rez,str+i,n+1);
    rez[n-i] = '\0';
    return rez;
}
//-------------------------------------------------------//

class Data {
    int zi, luna, an;
public:
    Data(const int zi=26, const int luna=3, const int an=2026) : zi(zi), luna(luna), an(an) {}
    Data(const Data& nou) : zi(nou.zi), luna(nou.luna), an(nou.an) {}
    Data(const char* data) {
        sscanf(data,"%d.%d.%d",&zi,&luna,&an);
    }

    Data& operator=(const Data& nou) {
        if (this != &nou) {
            zi = nou.zi;
            luna = nou.luna;
            an = nou.an;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Data& d);
};

std::ostream& operator<<(std::ostream& out, const Data& d) {
    if (d.zi < 10) out<<'0';
    out<<d.zi<<'.';
    if (d.luna < 10) out<<'0';
    out<<d.luna<<'.';
    out<<d.an;
    return out;
}

class Ora {
    int ora, minut;
public:
    Ora(const int ora = 8, const int minut = 0) : ora(ora), minut(minut) {}
    Ora(const Ora& nou) : ora(nou.ora), minut(nou.minut) {}

    Ora(const char* timp) {
        sscanf(timp, "%d:%d", &ora, &minut);
    }

    Ora& operator=(const Ora& nou) {
        if (this != &nou) {
            ora = nou.ora;
            minut = nou.minut;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Ora& o);
};

std::ostream& operator<<(std::ostream& out, const Ora& o) {
    if (o.ora < 10) out << '0';
    out << o.ora << ":";

    if (o.minut < 10) out << '0';
    out << o.minut;

    return out;
}

class Pacient {
    int varsta;
    char* nume;
    char* telefon;
    bool asigurat;

public:
    Pacient() : varsta(0), asigurat(false) {     // constructor fara parametri
        nume = new char[strlen("Necompletat") + 1];
        strcpy(nume, "Necompletat");
        telefon = new char[strlen("Necompletat") + 1];
        strcpy(telefon,"Necompletat");
    }

    Pacient(const char* nume, int varsta, const char* telefon, const char* asiguratStatus) : varsta(varsta) {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->telefon = new char[strlen(telefon) + 1];
        strcpy(this->telefon, telefon);

        char* temp = trim(asiguratStatus);    // sir de caractere auxiliar
        for (int i = 0; i<strlen(temp); i++)
            temp[i] = tolower(temp[i]);
        if (strcmp(temp,"asigurat") == 0)
            this->asigurat = true;
        else
            this->asigurat = false;
        delete[] temp;
    }

    Pacient(const Pacient& nou) : varsta(nou.varsta), asigurat(nou.asigurat) {
        nume = new char[strlen(nou.nume) + 1];
        strcpy(nume, nou.nume);
        telefon = new char[strlen(nou.telefon) + 1];
        strcpy(telefon, nou.telefon);
    }

    // Getters
    const char* getNume() const {
        return nume;
    }

    const char* getTelefon() const {
        return telefon;
    }

    bool getAsigurat() const {
        return asigurat;
    }

    int getVarsta() const {
        return varsta;
    }

    // Setters
    void setNume(const char* numeNou) {
        delete[] nume;
        nume = new char[strlen(numeNou) + 1];
        strcpy(nume, numeNou);
    }

    void setTelefon(const char* telefonNou) {
        delete[] telefon;
        telefon = new char[strlen(telefonNou) + 1];
        strcpy(telefon, telefonNou);
    }

    void setAsigurat(const bool asiguratNou) {
        asigurat = asiguratNou;
    }

    void setVarsta(const int varstaNoua) {
        varsta = varstaNoua;
    }

    Pacient& operator=(const Pacient& nou) {
        if (this != &nou) {
            delete[] nume;
            delete[] telefon;
            nume = new char[strlen(nou.nume) + 1];
            strcpy(nume, nou.nume);

            telefon = new char[strlen(nou.telefon) + 1];
            strcpy(telefon, nou.telefon);

            varsta = nou.varsta;
            asigurat = nou.asigurat;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Pacient& P);

    ~Pacient() {
        delete[] nume;
        delete[] telefon;
    }
};

std::ostream& operator<<(std::ostream& out, const Pacient& P) {
    out<<"Pacient: "<<P.nume<<", "<<P.varsta<<" ani, "<<P.telefon<<", "<<(P.asigurat ? "Asigurat" : "Neasigurat")<<'\n';
    return out;
}

class Medic {
    char* nume;
    char* specializare;

public:
    Medic() {
        nume = new char[strlen("Necompletat") + 1];
        strcpy(nume, "Necompletat");
        specializare = new char[strlen("Necompletat") + 1];
        strcpy(specializare,"Necompletat");
    }

    Medic(const char* nume, const char* specializare) {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->specializare = new char[strlen(specializare) + 1];
        strcpy(this->specializare, specializare);
    }

    Medic(const Medic& nou) {
        this->nume = new char[strlen(nou.nume) + 1];
        strcpy(nume, nou.nume);
        this->specializare = new char[strlen(nou.specializare) + 1];
        strcpy(specializare, nou.specializare);
    }

    // Getters

    const char* getNume() const {
        return nume;
    }

    const char* getSpecializare() const {
        return specializare;
    }

    // Setters

    void setNume(const char* numeNou) {
        delete[] nume;
        nume = new char[strlen(numeNou) + 1];
        strcpy(nume, numeNou);
    }

    void setSpecializare(const char* specializareNoua) {
        delete[] specializare;
        specializare = new char[strlen(specializareNoua) + 1];
        strcpy(specializare, specializareNoua);
    }

    Medic& operator=(const Medic& nou) {
        if (this != &nou) {
            delete[] nume;
            delete[] specializare;
            nume = new char[strlen(nou.nume) + 1];
            strcpy(nume, nou.nume);
            specializare = new char[strlen(nou.specializare) + 1];
            strcpy(specializare, nou.specializare);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Medic& M);

    ~Medic() {
        delete[] nume;
        delete[] specializare;
    }
};

std::ostream& operator<<(std::ostream& out, const Medic& M) {
    out<<"Medic: "<<M.nume<<", "<<M.specializare<<'\n';
    return out;
}

class Reteta {
    const int idReteta;
    Medic medic;
    Pacient pacient;
    int durata;
    char* tratament;
    Data dataEmitere;
    static int contorId;
public:
    Reteta() : idReteta(++contorId), durata(0) {
        tratament = new char[strlen("Necompletat") + 1];
        strcpy(tratament, "Necompletat");
    }

    Reteta(const Medic& medic, const Pacient& pacient, const char* tratament, const int durata, const Data& dataEmitere) : idReteta(++contorId), medic(medic), pacient(pacient), durata(durata), dataEmitere(dataEmitere) {
        this->tratament = new char[strlen(tratament) + 1];
        strcpy(this->tratament, tratament);
    }

    Reteta(const Reteta& nou) : idReteta(++contorId), medic(nou.medic), pacient(nou.pacient), durata(nou.durata), dataEmitere(nou.dataEmitere) {
        tratament = new char[strlen(nou.tratament) + 1];
        strcpy(tratament, nou.tratament);
    }

    Reteta& operator=(const Reteta& R) {
        if (this != &R) {
            medic = R.medic;
            pacient = R.pacient;
            durata = R.durata;
            dataEmitere = R.dataEmitere;

            delete[] tratament;
            tratament = new char[strlen(R.tratament) + 1];
            strcpy(tratament, R.tratament);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Reteta& R);

    ~Reteta() {
        delete[] tratament;
    }
};

std::ostream& operator<<(std::ostream& out, const Reteta& R) {
    out<<"------------------------------------\n";
    out<<"Reteta #"<<R.idReteta<<'\n';
    out<<R.pacient;
    out<<R.medic;
    out<<"Tratament: "<<R.tratament<<'\n';
    out<<"Durata: "<<R.durata<<" zile\n";
    out<<"Data prescriere: "<<R.dataEmitere<<'\n';
    out<<"------------------------------------\n";
    return out;
}

int Reteta::contorId = 0;

class Programare
{
    Pacient pacient;
    Medic medic;
    Data dataProgramarii;
    Ora oraProgramarii;
public:
    Programare() {}

    Programare(const Pacient& pacient, const Medic& medic, const Data& dataProgramarii, const Ora& oraProgramarii)
    : pacient(pacient), medic(medic), dataProgramarii(dataProgramarii), oraProgramarii(oraProgramarii) {}

    Programare(const Programare& noua)
    : pacient(noua.pacient), medic(noua.medic), dataProgramarii(noua.dataProgramarii), oraProgramarii(noua.oraProgramarii){}

    Programare& operator=(const Programare& noua) {
        if (this != &noua) {
            pacient = noua.pacient;
            medic = noua.medic;
            dataProgramarii = noua.dataProgramarii;
            oraProgramarii = noua.oraProgramarii;
        }
        return *this;
    }

    const Pacient& getPacient() const { return pacient; }
    const Medic& getMedic() const { return medic; }
    const Data& getData() const { return dataProgramarii; }
    const Ora& getOra() const { return oraProgramarii; }

    friend std::ostream& operator<<(std::ostream& out, const Programare& P);
};

std::ostream& operator<<(std::ostream& out, const Programare& P) {
    out<<"Pacientul "<<P.pacient.getNume()<<" are programare pentru "<<P.medic.getSpecializare()
    <<" pe "<<P.dataProgramarii<<" la ora "<<P.oraProgramarii<<'.';
    return out;
}


class Consultatie {
    Programare programare;
    char* diagnostic;
    char* tratament;
    float tarif;
public:
    Consultatie() : tarif(0) {
        diagnostic = new char[strlen("Necompletat") + 1];
        strcpy(diagnostic, "Necompletat");
        tratament = new char[strlen("Necompletat") + 1];
        strcpy(tratament,"Necompletat");
    }
    Consultatie(const Programare& programare, const char* diagnostic, const char* tratament, float tarif)
    : programare(programare), tarif(tarif) {
        this->diagnostic = new char[strlen(diagnostic) + 1];
        strcpy(this->diagnostic, diagnostic);

        this->tratament = new char[strlen(tratament) + 1];
        strcpy(this->tratament, tratament);
    }

    Consultatie(const Consultatie& c) : programare(c.programare), tarif(c.tarif) {
        diagnostic = new char[strlen(c.diagnostic) + 1];
        strcpy(diagnostic, c.diagnostic);

        tratament = new char[strlen(c.tratament) + 1];
        strcpy(tratament, c.tratament);
    }

    Consultatie& operator=(const Consultatie& c) {
        if (this != &c) {
            programare = c.programare;
            tarif = c.tarif;

            delete[] diagnostic;
            diagnostic = new char[strlen(c.diagnostic) + 1];
            strcpy(diagnostic, c.diagnostic);

            delete[] tratament;
            tratament = new char[strlen(c.tratament) + 1];
            strcpy(tratament, c.tratament);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Consultatie& C);

    ~Consultatie() {
        delete[] diagnostic;
        delete[] tratament;
    }
};

std::ostream& operator<<(std::ostream& out, const Consultatie& C) {
    out<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    out<<"Consultatie la sectia "<<C.programare.getMedic().getSpecializare()<<" realizata de medic "<<C.programare.getMedic().getNume()<<" pentru pacient "<<C.programare.getPacient().getNume()<<".\n";
    out<<"Diagnostic: "<<C.diagnostic<<'\n';
    out<<"Tratament: "<<C.tratament<<'\n';
    out<<"Tarif: "<<C.tarif<<" RON\n";
    out<<"Data: "<<C.programare.getData()<<", "<<C.programare.getOra()<<'\n';
    out<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    return out;
}

int main() {
    // Pacient n("Ionel", 20, "0719383", "asigurat");
    // std::cout << n.getNume() << " " << n.getVarsta() << " " << n.getTelefon() << " " << n.getAsigurat() << '\n';
    // n.setVarsta(21);
    // std::cout << n.getNume() << " " << n.getVarsta() << " " << n.getTelefon() << " " << n.getAsigurat() << '\n';
    // Medic DR("Conachiu", "Ortopedie");
    // std::cout << DR.getNume() << " " << DR.getSpecializare() << '\n';
    // Medic dr(DR);
    // std::cout << dr.getNume() << " " << dr.getSpecializare() << '\n';
    // Pacient X("Petrica", 30, "07222222", "neasigurat");
    // n = X;
    // std::cout << n.getNume() << " " << n.getVarsta() << " " << n.getTelefon() << " " << n.getAsigurat() << '\n';
    // std::cout<<X;
    // Pacient Y = n = X;
    // std::cout<<Y<<X<<n;
    // Medic* medici = new Medic[10];
    // char nume[100], specializare[100];
    // for (int i=0; i<3; i++) {
    //     std::cout<<"Medic "<<i+1<<":\nNume: "; std::cin.getline(nume,100);
    //     std::cout<<"Specializare: "; std::cin.getline(specializare,100);
    //     medici[i] = Medic(nume,specializare);
    // }

    // Data d1("12.05.2026");
    // Data d2("16.05.2026");
    // std::cout<<d1<<'\n'<<d2<<'\n';
    // d1 = d2;
    // std::cout<<d2<<'\n';

    // for (int i=0; i<3; i++) {
    //     std::cout<<medici[i];
    // }

    Medic Card("Popescu Ion","Medicina primara");
    Pacient A("Ionescu Horia",45,"0739923187","asigurat");
    Pacient X("Florescu Maria",50,"0738713187","neasigurat");
    Pacient Z(A);
    std::cout<<Z;
    // Reteta reteta(Card,A,"Algocalmin, Ibuprofen",30, "24.03.2026");
    // Reteta reteta2(Card,X,"Imraldi",90, "24.03.2026");
    // std::cout<<reteta<<reteta2;
    // Programare p(A,Card,"25.03.2026","12:30");
    // Consultatie C(p,"Artrita","Sortis",249.99);
    // std::cout<<C;
    // std::cout<<A.getNume();

    return 0;
}
