// Cabinetul medical Mercy este alcatuit din urmatoarele entitati:
// Pacientii - sunt cei care vin la cabinet pentru a beneficia de servicii medicale care sunt oferite doar pe baza de programare
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

    bool esteBisect(const int an) const {
        return (an % 4 == 0 && an % 100 != 0) || (an % 400 == 0);
    }

    int zileLuna(const int luna, const int an) const {
        switch (luna) {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            if (esteBisect(an)) return 29;
            return 28;
        default:
            return 0;
        }
    }
    bool esteValida(const int z, const int l, const int a) const {
        if (a < 2026 || a > 2100)
            return false;
        if (l < 1 || l > 12)
            return false;
        if (z < 1 || z > zileLuna(l, a))
            return false;
        return true;
    }
public:
    Data(const int zi=26, const int luna=3, const int an=2026) {
        if (esteValida(zi, luna, an)) {
            this->zi = zi;
            this->luna = luna;
            this->an = an;
        } else {
            std::cout << "Data invalida (" << zi << "." << luna << "." << an << ")! Se seteaza implicit 26.03.2026.\n";
            this->zi = 26;
            this->luna = 3;
            this->an = 2026;
        }
    }
    Data(const Data& nou) : zi(nou.zi), luna(nou.luna), an(nou.an) {}
    Data(const char* data) {
        int z, l, a;
        sscanf(data, "%d.%d.%d", &z, &l, &a);
        if (esteValida(z, l, a)) {
            zi = z;
            luna = l;
            an = a;
        } else {
            std::cout << "Data invalida (" << data << ")! Se seteaza implicit 26.03.2026.\n";
            zi = 26;
            luna = 3;
            an = 2026;
        }
    }

    Data& operator=(const Data& nou) {
        if (this != &nou) {
            zi = nou.zi;
            luna = nou.luna;
            an = nou.an;
        }
        return *this;
    }

    bool operator==(const Data& nou) const {
        return zi == nou.zi && luna == nou.luna && an == nou.an;
    }

    bool operator<(const Data& nou) const {
        if (an != nou.an) return an < nou.an;
        if (luna != nou.luna) return luna < nou.luna;
        return zi < nou.zi;
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

    bool esteValida(const int o, const int m) const {
        return o >= 0 && o <= 23 && m >= 0 && m <= 59;
    }
public:
    Ora(const int ora = 8, const int minut = 0) {
        if (esteValida(ora, minut)) {
            this->ora = ora;
            this->minut = minut;
        } else {
            std::cout << "Ora invalida ("<<ora<<':'<<minut<<")! Se seteaza 08:00 implicit.\n";
            this->ora = 8;
            this->minut = 0;
        }
    }
    Ora(const Ora& nou) : ora(nou.ora), minut(nou.minut) {}

    Ora(const char* timp) {
        int o, m;
        sscanf(timp, "%d:%d", &o, &m);
        if (esteValida(o, m)) {
            ora = o;
            minut = m;
        } else {
            std::cout << "Ora invalida (" << timp << ")! Se seteaza 08:00 implicit.\n";
            ora = 8;
            minut = 0;
        }
    }

    Ora& operator=(const Ora& nou) {
        if (this != &nou) {
            ora = nou.ora;
            minut = nou.minut;
        }
        return *this;
    }

    bool operator<=(const Ora& nou) const {
        if (ora < nou.ora) return true;
        if (ora == nou.ora && minut <= nou.minut) return true;
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const Ora& o);
    bool respectaProgramCabinet(const Ora& start, const Ora& final) const;
    int diferentaOre(const Ora& nou) const;
};

std::ostream& operator<<(std::ostream& out, const Ora& o) {
    if (o.ora < 10) out << '0';
    out << o.ora << ":";

    if (o.minut < 10) out << '0';
    out << o.minut;

    return out;
}

bool Ora::respectaProgramCabinet(const Ora& start, const Ora& final) const {
    if (start <= *this && *this <= final) return true;
    return false;
}

int Ora::diferentaOre(const Ora& nou) const { return abs((ora*60+minut)-(nou.ora*60+nou.minut)); }

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

    float calculeazaReducere(float tarifInitial) const;
};

std::ostream& operator<<(std::ostream& out, const Pacient& P) {
    out<<P.nume<<", "<<P.varsta<<" ani, "<<P.telefon<<", "<<(P.asigurat ? "Asigurat" : "Neasigurat")<<'\n';
    return out;
}

float Pacient::calculeazaReducere(float tarifInitial) const {
    float tarif = tarifInitial;
    if (asigurat) tarif = tarif * 0.5; // 50% reducere pentru pacientii asigurati
    if (varsta >= 65) tarif = tarif * 0.95; // 5% reducere pentru pensionari
    if (varsta < 18) tarif = tarif * 0.8; // 20% reducere pentru copii

    return tarif;
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
    bool operator==(const Medic& nou) const {
        return strcmp(nume, nou.nume) == 0 && strcmp(specializare, nou.specializare) == 0;
    }

    ~Medic() {
        delete[] nume;
        delete[] specializare;
    }
};

std::ostream& operator<<(std::ostream& out, const Medic& M) {
    out<<M.nume<<", "<<M.specializare;
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

    bool esteInViitor(const Data& dataAzi) const;
    bool conflictOrar(const Programare& alta, int durataMedieConsultatieMinute = 30) const;
};

bool Programare::conflictOrar(const Programare& alta, int durataMedieConsultatieMinute) const {
    if (!(medic == alta.medic))
        return false;
    if (!(dataProgramarii == alta.dataProgramarii))
        return false;
    if (oraProgramarii.diferentaOre(alta.oraProgramarii) >= durataMedieConsultatieMinute)
        return false;
    return true;
}

std::ostream& operator<<(std::ostream& out, const Programare& P) {
    out<<"Pacientul "<<P.pacient.getNume()<<" are programare pentru "<<P.medic.getSpecializare()
    <<" pe "<<P.dataProgramarii<<" la ora "<<P.oraProgramarii<<'.';
    return out;
}

bool Programare::esteInViitor(const Data& dataAzi) const {
    return dataAzi < dataProgramarii;
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

        // this->tarif = programare.getPacient().calculeazaReducere(tarif);

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

    Reteta generareReteta(int durataTratament);
    void aplicaReducere();
};

Reteta Consultatie::generareReteta(int durataTratament) {
    return Reteta(programare.getMedic(),
                  programare.getPacient(),
                  tratament,durataTratament,
                  programare.getData());
}

void Consultatie::aplicaReducere() { tarif = programare.getPacient().calculeazaReducere(tarif); }

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

void adaugaMedic(Medic*& medici, int& nrMedici, const Medic& medicNou) {
    Medic* temp = new Medic[nrMedici + 1];
    for (int i = 0; i < nrMedici; i++)
        temp[i] = medici[i];
    temp[nrMedici] = medicNou;
    delete[] medici;
    medici = temp;
    nrMedici++;
}

int main() {
    int nrMedici = 0;
    Medic* medici = nullptr;

    Data dataCurenta;
    Ora incepereProgram("8:00");
    Ora sfarsitProgram("16:00");

    adaugaMedic(medici,nrMedici,Medic("Dr. Ghimbav Tudor","Cardiologie"));
    adaugaMedic(medici,nrMedici,Medic("Dr. Nicolaescu Raluca","Diabotologie"));
    adaugaMedic(medici,nrMedici,Medic("Dr. Conachiu Dumitru","Ortopedie"));
    adaugaMedic(medici,nrMedici,Medic("Dr. Ulmeanu Iuliana","Psihiatrie"));

    for (int i=0; i<nrMedici; i++)
        std::cout<<medici[i]<<'\n';
    Pacient A("Ionescu Horia",18,"0739923187","asigurat");
    Pacient X("Florescu Maria",50,"0738713187","neasigurat");
    Pacient Z(A);
    std::cout<<Z;
    // Reteta reteta(Card,A,"Algocalmin, Ibuprofen",30, "24.03.2026");
    // Reteta reteta2(Card,X,"Imraldi",90, "24.03.2026");
    // std::cout<<reteta<<reteta2;
    Programare p(A,medici[1],"25.03.2026","12:30");
    Programare o(A,medici[2],"25.03.2026","13:00");
    // std::cout<<p.conflictOrar(o);
    // std::cout<<o.esteInViitor()
    Consultatie C(p,"Artrita","Sortis",250);
    std::cout<<C.generareReteta(30);
    std::cout<<C;
    C.aplicaReducere();
    std::cout<<C;
    // std::cout<<A.getNume();
    Ora t("16:00");
    std::cout<<t.respectaProgramCabinet(incepereProgram,sfarsitProgram);
    std::cout<<*medici;
    delete[] medici;
    // delete[] pacienti;
    // delete[] programari;
    // delete[] retete;
    // delete[] consultatii;
    return 0;
}
