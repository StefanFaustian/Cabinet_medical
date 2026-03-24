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
    int n = strlen(str) - 1;
    while (n >= 0 && str[n] == ' ')
        n--;

    char* rez = new char[n + 2];
    strncpy(rez,str+i,n+1);
    rez[n] = '\0';
    return rez;
}
//-------------------------------------------------------//

class Data {
    int zi, luna, an;
public:
    Data(const int zi=1, const int luna=1, const int an=1) : zi(zi), luna(luna), an(an) {}
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
    }

    Pacient(const Pacient& nou) : varsta(nou.varsta), asigurat(nou.asigurat) {
        nume = new char[strlen(nou.nume) + 1];
        strcpy(nume, nou.nume);
        telefon = new char[strlen(nou.telefon) + 1];
        strcpy(telefon, nou.telefon);
    }

    // Getters
    const char* getNume() const {
        char* numeReturnat = new char[strlen(nume) + 1];
        strcpy(numeReturnat, nume);
        return numeReturnat;
    }

    const char* getTelefon() const {
        char* telefonReturnat = new char[strlen(telefon) + 1];
        strcpy(telefonReturnat, telefon);
        return telefonReturnat;
    }

    bool getAsigurat() const {
        return asigurat;
    }

    int getVarsta() const {
        return varsta;
    }

    // Setters
    void setNume(char* nume) {
        delete[] this->nume;
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
    }

    void setTelefon(const char* telefon) {
        delete[] this->telefon;
        this->telefon = new char[strlen(telefon) + 1];
        strcpy(this->telefon, telefon);
    }

    void setAsigurat(bool asigurat) {
        this->asigurat = asigurat;
    }

    void setVarsta(int varsta) {
        this->varsta = varsta;
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
        std::cout << "~Pacient() " << nume << " " << varsta << " " << telefon << " " << asigurat << '\n';
        delete[] nume;
        delete[] telefon;
    }
};

std::ostream& operator<<(std::ostream& out, const Pacient& P) {
    out<<"Pacient: "<<P.nume<<", "<<P.varsta<<", "<<P.telefon<<", "<<(P.asigurat ? "Asigurat" : "Neasigurat")<<'\n';
    return out;
}

class Medic {
    char* nume;
    char* specializare;

public:
    Medic() {
        nume = new char(strlen("Necompletat") + 1);
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

    char* getNume() const {
        char* numeReturnat = new char[strlen(nume) + 1];
        strcpy(numeReturnat, nume);
        return numeReturnat;
    }

    char* getSpecializare() const {
        char* specializareReturnata = new char[strlen(specializare) + 1];
        strcpy(specializareReturnata, specializare);
        return specializareReturnata;
    }

    // Setters

    void setNume(char* nume) {
        delete[] this->nume;
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
    }

    void setSpecializare(char* specializare) {
        delete[] this->specializare;
        this->specializare = new char[strlen(specializare) + 1];
        strcpy(this->specializare, specializare);
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
        std::cout << "~Medic() " << nume << " " << specializare << '\n';
        delete[] nume;
        delete[] specializare;
    }
};

std::ostream& operator<<(std::ostream& out, const Medic& M) {
    out<<"Medic: "<<M.nume<<", "<<M.specializare<<'\n';
    return out;
}

class Reteta {
    Medic medic;
    Pacient pacient;
    const int idReteta;
    int durata;
    char* tratament;
    Data dataEmitere;
    static int contorId;
public:
    Reteta() : durata(0), idReteta(++contorId) {
        tratament = new char[strlen("Necompletat") + 1];
        strcpy(tratament, "Necompletat");
    }

    ~Reteta() {
        delete[] tratament;
    }
};

int Reteta::contorId = 0;

// class Programare
// {
//     Pacient pacient;
//     Medic medic;
//     Data dataProgramarii;
//     char* ora;
//
// public:
//     Programare() {}
//
//     Programare(const char* data, const char* ora, Pacient& pacient, Medic& medic) : pacient(pacient), medic(medic) {
//         this->data = new char[strlen(data) + 1];
//         strcpy(this->data, data);
//
//         this->ora = new char[strlen(ora) + 1];
//         strcpy(this->ora, ora);
//     }
//
//     Programare(const Programare& noua) {
//     }
// };



class Consultatie
{
    Pacient pacient;
    Medic medic;
    char* data;
    char* diagnostic;
    float tarif;
};


int main() {
    Pacient n("Ionel", 20, "0719383", "asigurat");
    std::cout << n.getNume() << " " << n.getVarsta() << " " << n.getTelefon() << " " << n.getAsigurat() << '\n';
    // n.setVarsta(21);
    // std::cout << n.getNume() << " " << n.getVarsta() << " " << n.getTelefon() << " " << n.getAsigurat() << '\n';
    // Medic DR("Conachiu", "Ortopedie");
    // std::cout << DR.getNume() << " " << DR.getSpecializare() << '\n';
    // Medic dr(DR);
    // std::cout << dr.getNume() << " " << dr.getSpecializare() << '\n';
    Pacient X("Petrica", 30, "07222222", "neasigurat");
    // n = X;
    // std::cout << n.getNume() << " " << n.getVarsta() << " " << n.getTelefon() << " " << n.getAsigurat() << '\n';
    // std::cout<<X;
    Pacient Y = n = X;
    std::cout<<Y<<X<<n;
    Medic* medici = new Medic[10];
    char nume[100], specializare[100];
    // for (int i=0; i<3; i++) {
    //     std::cout<<"Medic "<<i+1<<":\nNume: "; std::cin.getline(nume,100);
    //     std::cout<<"Specializare: "; std::cin.getline(specializare,100);
    //     medici[i] = Medic(nume,specializare);
    // }

    Data d1("12.05.2026");
    Data d2("16.05.2026");
    std::cout<<d1<<'\n'<<d2<<'\n';
    d1 = d2;
    std::cout<<d2<<'\n';

    for (int i=0; i<3; i++) {
        std::cout<<medici[i];
    }


    return 0;
}
