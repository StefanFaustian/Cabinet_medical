// Cabinetul medical Mercy este alcatuit din urmatoarele entitati:
// Pacientii - sunt cei care vin la cabinet pentru a beneficia de servicii medicale
// Medicii - sunt cei care efectueaza serviciile medicale
// Programarile - sunt generate de pacienti pentru medici
// Consultatiile - reprezinta scopul programarilor si sunt realizate de medici pentru pacienti
// Retetele - sunt generate dupa o consultatie

#include <iostream>
#include <cstring>

class Pacient {
    char* nume;
    char* telefon;
    int varsta;
    bool asigurat;
public:
    Pacient(const char* nume, int varsta, const char* telefon, const bool asigurat) {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->varsta = varsta;
        this->telefon = new char[strlen(telefon) + 1];
        strcpy(this->telefon, telefon);
        this->asigurat = asigurat;
    }

    Pacient(const Pacient& nou) {
        this->nume = new char[strlen(nou.nume) + 1];
        strcpy(this->nume, nou.nume);
        this->varsta = nou.varsta;
        this->telefon = new char[strlen(nou.telefon) + 1];
        strcpy(this->telefon, nou.telefon);
        this->asigurat = nou.asigurat;
    }

    // Getters
    char* getNume() const {
        char* numeReturnat = new char[strlen(nume) + 1];
        strcpy(numeReturnat, nume);
        return numeReturnat;
    }

    char* getTelefon() const {
        char* telefonReturnat = new char[strlen(telefon) + 1];
        strcpy(telefonReturnat, telefon);
        return telefon;
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

    void setTelefon(char* telefon) {
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

    ~Pacient() {
        std::cout << "~Pacient() " << nume << " " << varsta << " " << telefon << " " << asigurat << '\n';
        delete[] nume;
        delete[] telefon;
    }
};

class Medic {
    char* nume;
    char* specializare;
public:
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

    ~Medic() {
        std::cout << "~Medic() " << nume << " " << specializare << '\n';
        delete[] nume;
        delete[] specializare;
    }
};

class Reteta {
    int idReteta;
    char* tratament;
};

class Programare {
    //Pacient pacient;
    //Medic medic;
    char* data;
    char* ora;
public:
    Programare(const char* data, const char* ora) {
        //this->pacient(pacient);
        //this->medic(pacient);

        this->data = new char[strlen(data) + 1];
        strcpy(this->data, data);

        this->ora = new char[strlen(ora) + 1];
        strcpy(this->ora, ora);
    }
};

class Consultatie {
    //Pacient pacient;
    //Medic medic;
    char* diagnostic;
    float tarif;
};


int main()
{
    Pacient n("Ionel",20,"0719383",true);
    std::cout << n.getNume() << " " << n.getVarsta() << " " << n.getTelefon() << " " << n.getAsigurat() << '\n';
    n.setVarsta(21);
    std::cout << n.getNume() << " " << n.getVarsta() << " " << n.getTelefon() << " " << n.getAsigurat() << '\n';
    Medic DR("Conachiu", "Ortopedie");
    std::cout << DR.getNume() << " " << DR.getSpecializare() << '\n';
    Medic dr(DR);
    std::cout << dr.getNume() << " " << dr.getSpecializare() << '\n';


    return 0;
}