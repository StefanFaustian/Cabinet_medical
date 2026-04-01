//Petcovici Alexandru - Stefan, grupa 132.2
// Cabinetul medical Mercy este alcatuit din urmatoarele entitati:
// Pacientii - sunt cei care vin la cabinet pentru a beneficia de servicii medicale care sunt oferite doar pe baza de programare
// Medicii - sunt cei care efectueaza serviciile medicale
// Programarile - sunt generate de pacienti pentru medici
// Consultatiile - reprezinta scopul programarilor si sunt realizate de medici pentru pacienti in baza unui tarif
// Retetele - sunt generate dupa o consultatie
// Clasele Data si Ora ajuta la lucrul cu reprele temporale
// La crearea obiectelor specifice unei clase, ele sunt inserate intr-un array alocat dinamic cu un nume sugestive (de exemplu, Medic* medici)

#include <iostream>
#include <cstring>

//--- Functie de prelucrare a sirurilor de caractere ---//
char* trim(const char* str) {
    int i = 0;
    while (str[i] == ' ')
        i++;
    int n = strlen(str);
    while (n > 0 && str[n-1] == ' ')
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
        if (z < 1 || z > zileLuna(l,a))
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

    const bool getAsigurat() const {
        return asigurat;
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

    ~Pacient() {
        delete[] nume;
        delete[] telefon;
    }

    friend std::ostream& operator<<(std::ostream& out, const Pacient& P);
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
    int idReteta;
    Medic medic;
    Pacient pacient;
    int durata;
    char* tratament;
    Data dataEmitere;
    static int contorId;
public:
    Reteta() : idReteta(0), durata(0) {
        tratament = new char[strlen("Necompletat") + 1];
        strcpy(tratament, "Necompletat");
    }

    Reteta(const Medic& medic, const Pacient& pacient, const char* tratament, const int durata, const Data& dataEmitere) : idReteta(++contorId), medic(medic), pacient(pacient), durata(durata), dataEmitere(dataEmitere) {
        this->tratament = new char[strlen(tratament) + 1];
        strcpy(this->tratament, tratament);
    }

    Reteta(const Reteta& nou) : idReteta(nou.idReteta), medic(nou.medic), pacient(nou.pacient), durata(nou.durata), dataEmitere(nou.dataEmitere) {
        tratament = new char[strlen(nou.tratament) + 1];
        strcpy(tratament, nou.tratament);
    }

    Reteta& operator=(const Reteta& R) {
        if (this != &R) {
            idReteta = R.idReteta;
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
    out<<"\nTratament: "<<R.tratament<<'\n';
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
    Programare() {} // constructor fara parametri, nu are nevoie de lista de initializare, entitatile se initializeaza automat

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

    bool esteInViitor(const Data& dataAzi) const; // util pentru ca o programare trebuie facuta in viitor
    bool conflictOrar(const Programare& alta, int durataMedieConsultatieMinute = 30) const;
};

bool Programare::conflictOrar(const Programare& alta, int durataMedieConsultatieMinute) const {
    if (!(medic == alta.medic)) // daca programarea se face in aceeasi zi, dar la alt medic, e ok!
        return false;
    if (!(dataProgramarii == alta.dataProgramarii)) // daca programarea se face la acelasi medic, dar in zile diferite, e ok!
        return false;
    if (oraProgramarii.diferentaOre(alta.oraProgramarii) >= durataMedieConsultatieMinute) // daca programarile nu se suprapun, e ok!
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

    // Getters
    const Data& getData() const {
        return programare.getData();
    }

    const float getTarif() const {
        return tarif;
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
    out<<"Consultatie la sectia "<<C.programare.getMedic().getSpecializare()<<" realizata de "<<C.programare.getMedic().getNume()<<" pentru pacient "<<C.programare.getPacient().getNume()<<".\n";
    out<<"Diagnostic: "<<C.diagnostic<<'\n';
    out<<"Tratament: "<<C.tratament<<'\n';
    out<<"Tarif: "<<C.tarif<<" RON\n";
    out<<"Data si ora: "<<C.programare.getData()<<", "<<C.programare.getOra()<<'\n';
    out<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    return out;
}

// Functii de adaugare in array-urile dinamice de entitati
void adaugaMedic(Medic*& medici, int& nrMedici, const Medic& medicNou) {
    Medic* temp = new Medic[nrMedici + 1];
    for (int i = 0; i < nrMedici; i++)
        temp[i] = medici[i];
    temp[nrMedici] = medicNou;
    delete[] medici;
    medici = temp;
    nrMedici++;
}

void adaugaPacient(Pacient*& pacienti, int& nrPacienti, const Pacient& p) {
    Pacient* temp = new Pacient[nrPacienti + 1];
    for (int i = 0; i < nrPacienti; i++)
        temp[i] = pacienti[i];
    temp[nrPacienti] = p;
    delete[] pacienti;
    pacienti = temp;
    nrPacienti++;
}

void adaugaProgramare(Programare*& programari, int& nrProgramari, const Programare& p, const Ora& start, const Ora& final) {
    if (!p.getOra().respectaProgramCabinet(start, final)) {
        std::cout << "Programare invalida - " <<p.getPacient().getNume() << ": Ora " << p.getOra()<< " este in afara programului cabinetului medical!\n";
        return;
    }

    Data azi;
    if (!p.esteInViitor(azi)) {
        std::cout << "Programare invalida - " <<p.getPacient().getNume() << ": Programarea trebuie sa fie facuta in viitor. :)!\n";
        return;
    }

    for (int i = 0; i < nrProgramari; i++) {
        if (programari[i].conflictOrar(p)) {
            std::cout << "Programare invalida - "<<p.getPacient().getNume()<< ": Conflict de orar cu programarea lui " << programari[i].getPacient().getNume() << "!\n";
            return;
        }
    }

    Programare* temp = new Programare[nrProgramari + 1];
    for (int i = 0; i < nrProgramari; i++)
        temp[i] = programari[i];
    temp[nrProgramari] = p;
    delete[] programari;
    programari = temp;
    nrProgramari++;
}

void adaugaConsultatie(Consultatie*& consultatii, int& nrConsultatii, const Consultatie& p) {
    Consultatie* temp = new Consultatie[nrConsultatii + 1];
    for (int i = 0; i < nrConsultatii; i++)
        temp[i] = consultatii[i];
    temp[nrConsultatii] = p;
    delete[] consultatii;
    consultatii = temp;
    nrConsultatii++;

}

void adaugaReteta(Reteta*& retete, int& nrRetete, const Reteta& p) {
    Reteta* temp = new Reteta[nrRetete + 1];
    for (int i = 0; i < nrRetete; i++)
        temp[i] = retete[i];
    temp[nrRetete] = p;
    delete[] retete;
    retete = temp;
    nrRetete++;
}

void adaugaData(Data*& date, int& nrDate, const Data& d) {
    Data* temp = new Data[nrDate + 1];
    for (int i = 0; i < nrDate; i++)
        temp[i] = date[i];
    temp[nrDate] = d;
    delete[] date;
    date = temp;
    nrDate++;
}

// Functie care verifica daca o data se afla in array-ul dinamic de date calendaristice
// Este utila la interogarea incasarilor dintr-o zi selectata.
bool existaData(Data*& date, int& nrDate, const Data& data) {
    for (int i = 0; i < nrDate; i++)
        if (date[i] == data)
            return true;
    return false;
}

// Functie de determinare a incasarilor dupa consultatii
float incasariTotale(Consultatie*& consultatii, int& nrConsultatii, const Data& data) {
    float total = 0;
    for (int i=0; i<nrConsultatii; i++) {
        if (consultatii[i].getData() == data)
            total += consultatii[i].getTarif();
    }
    return total;

}

void afiseazaMeniu() {
    std::cout<<"\n/===========================/\n";
    std::cout<<"    Cabinetul medical MERCY\n";
    std::cout<<"  Program zilnic: 8:00-16:00  ";
    std::cout<<"\n/===========================/\n";
    std::cout << "1. Afiseaza medici\n";
    std::cout << "2. Afiseaza pacienti\n";
    std::cout << "3. Afiseaza programari\n";
    std::cout << "4. Afiseaza consultatii\n";
    std::cout << "5. Afiseaza retete\n";
    std::cout << "6. Afiseaza tot\n";
    std::cout << "7. Afiseaza total incasari pentru ziua selectata\n";
    std::cout << "0. Iesire\n";
    std::cout << "========================================\n";
    std::cout << "Input: ";
}

int main() {
    int nrMedici = 0;
    int nrPacienti = 0;
    int nrProgramari = 0;
    int nrConsultatii = 0;
    int nrRetete = 0;
    int nrDate = 0;
    Medic* medici = nullptr;
    Pacient* pacienti = nullptr;
    Programare* programari = nullptr;
    Consultatie* consultatii = nullptr;
    Reteta* retete = nullptr;
    Data* date = nullptr;

    Ora incepereProgram("8:00");
    Ora sfarsitProgram("16:00");

    // Definire medici
    adaugaMedic(medici,nrMedici,Medic("Dr. Ghimbav Tudor","Cardiologie"));
    adaugaMedic(medici,nrMedici,Medic("Dr. Nicolaescu Raluca","Diabetologie"));
    adaugaMedic(medici,nrMedici,Medic("Dr. Conachiu Dumitru","Ortopedie"));
    adaugaMedic(medici,nrMedici,Medic("Dr. Ulmeanu Iuliana","Psihiatrie"));
    adaugaMedic(medici,nrMedici,Medic("Dr. Barbu Cristian", "Neurologie"));
    adaugaMedic(medici,nrMedici,Medic("Dr. Stanescu Ioana", "Dermatologie"));

    // Definire pacienti
    adaugaPacient(pacienti,nrPacienti,Pacient("Ionescu Horia", 45, "0739923187", "asigurat"));
    adaugaPacient(pacienti,nrPacienti,Pacient("Florescu Maria", 70, "0738713187", "neasigurat"));
    adaugaPacient(pacienti,nrPacienti,Pacient("Hreniuc Mihai", 16, "0751234567", "asigurat"));
    adaugaPacient(pacienti,nrPacienti,Pacient("Constantin Elena", 30, "0769876543", "neasigurat"));
    adaugaPacient(pacienti,nrPacienti,Pacient("Vasilescu Ion", 72, "0722334455", "asigurat"));
    adaugaPacient(pacienti,nrPacienti,Pacient("Radu Alexandra", 10, "0733445566", "neasigurat"));
    adaugaPacient(pacienti,nrPacienti,Pacient("Marinescu Dan", 55, "0744556677", "asigurat"));
    adaugaPacient(pacienti,nrPacienti,Pacient("Stoica Andreea", 28, "0755667788", "neasigurat"));

    // Definire programari VALIDE
    adaugaProgramare(programari, nrProgramari,
        Programare(pacienti[0], medici[0], "28.03.2026", "10:00"),
        incepereProgram, sfarsitProgram);

    adaugaProgramare(programari, nrProgramari,
        Programare(pacienti[1], medici[2], "28.03.2026", "11:00"),
        incepereProgram, sfarsitProgram);

    adaugaProgramare(programari, nrProgramari,
        Programare(pacienti[2], medici[3], "29.03.2026", "09:30"),
        incepereProgram, sfarsitProgram);

    adaugaProgramare(programari, nrProgramari,
        Programare(pacienti[4], medici[1], "29.03.2026", "14:00"),
        incepereProgram, sfarsitProgram);

    adaugaProgramare(programari, nrProgramari,
        Programare(pacienti[5], medici[4], "30.03.2026", "08:30"),
        incepereProgram, sfarsitProgram);

    adaugaProgramare(programari, nrProgramari,
        Programare(pacienti[6], medici[5], "30.03.2026", "12:00"),
        incepereProgram, sfarsitProgram);

    adaugaProgramare(programari, nrProgramari,
        Programare(pacienti[7], medici[0], "30.03.2026", "15:00"),
        incepereProgram, sfarsitProgram);


    // Definire scenarii INVALIDE

    std::cout << "\n---/ Scenariu: programare in afara programului /---\n";
    adaugaProgramare(programari, nrProgramari,Programare(pacienti[3], medici[0], "28.03.2026", "18:00"),
        incepereProgram, sfarsitProgram);

    // Programare invalida (conflict orar)
    std::cout << "\n---/ Scenariu: conflict de orar /---\n";
    adaugaProgramare(programari, nrProgramari,Programare(pacienti[3], medici[0], "28.03.2026", "10:15"),
        incepereProgram, sfarsitProgram);

    // Data invalida (31 aprilie nu exista)
    std::cout << "\n---/ Scenariu: data este invalida /---\n";
    adaugaProgramare(programari, nrProgramari,Programare(pacienti[3], medici[1], "31.04.2026", "10:00"),
        incepereProgram, sfarsitProgram);

    // Ora invalida (25:00)
    std::cout << "\n---/ Scenariu: ora este invalida /---\n";
    adaugaProgramare(programari, nrProgramari,Programare(pacienti[3], medici[1], "28.03.2026", "25:00"),
        incepereProgram, sfarsitProgram);

    // Efectuarea consultatiilor si generarea retetelor
    Consultatie c1(programari[0], "Hipertensiune arteriala","Azomezartan 40mg", 250);
    c1.aplicaReducere();
    adaugaConsultatie(consultatii, nrConsultatii, c1);
    adaugaReteta(retete, nrRetete, c1.generareReteta(30));

    Consultatie c2(programari[1], "Artrita reumatoida","Ibuprofen 400mg", 300);
    c2.aplicaReducere();
    adaugaConsultatie(consultatii, nrConsultatii, c2);
    adaugaReteta(retete, nrRetete, c2.generareReteta(45));

    Consultatie c3(programari[2], "Tulburare de anxietate","Terapie cognitiv-comportamentala", 400);
    c3.aplicaReducere();
    adaugaConsultatie(consultatii, nrConsultatii, c3);
    adaugaReteta(retete, nrRetete, c3.generareReteta(90));

    Consultatie c4(programari[3], "Diabet zaharat tip 2","Metformin 1000mg", 280);
    c4.aplicaReducere();
    adaugaConsultatie(consultatii, nrConsultatii, c4);
    adaugaReteta(retete, nrRetete, c4.generareReteta(60));

    Consultatie c5(programari[4], "Epilepsie juvenila","Levetiracetam 250mg", 350);
    c5.aplicaReducere();
    adaugaConsultatie(consultatii, nrConsultatii, c5);
    adaugaReteta(retete, nrRetete, c5.generareReteta(180));

    Consultatie c6(programari[5], "Dermatita atopica","Elidel crema, Cetirizina 10mg", 200);
    c6.aplicaReducere();
    adaugaConsultatie(consultatii, nrConsultatii, c6);
    adaugaReteta(retete, nrRetete, c6.generareReteta(21));

    Consultatie c7(programari[6], "Tahicardie sinusala","Bisoprolol 5mg", 250);
    c7.aplicaReducere();
    adaugaConsultatie(consultatii, nrConsultatii, c7);
    adaugaReteta(retete, nrRetete, c7.generareReteta(14));

    for (int i = 0; i < nrConsultatii; i++)
        if (!existaData(date,nrDate,consultatii[i].getData()))
            adaugaData(date,nrDate,consultatii[i].getData());

    int optiune = -1;
    do {
        if (optiune != 7)
            afiseazaMeniu();
        else {
            std::cout<<"Input: ";
            std::cin >> optiune;
            std::cout<< "Incasari totale in data "<< date[optiune-1]<<": ";
            std::cout << incasariTotale(consultatii,nrConsultatii,date[optiune-1]) << " RON\n";
            afiseazaMeniu();
        }

        std::cin >> optiune;

        switch (optiune) {
        case 1:
            std::cout << "\n--- MEDICI (" << nrMedici << ") ---\n";
            for (int i = 0; i < nrMedici; i++)
                std::cout << i + 1 << ". " << medici[i] << '\n';
            break;

        case 2:
            std::cout << "\n--- PACIENTI (" << nrPacienti << ") ---\n";
            for (int i = 0; i < nrPacienti; i++)
                std::cout << i + 1 << ". " << pacienti[i];
            break;

        case 3:
            std::cout << "\n--- PROGRAMARI (" << nrProgramari << ") ---\n";
            for (int i = 0; i < nrProgramari; i++)
                std::cout << i + 1 << ". " << programari[i] << '\n';
            break;

        case 4:
            std::cout << "\n--- CONSULTATII (" << nrConsultatii << ") ---\n";
            for (int i = 0; i < nrConsultatii; i++)
                std::cout << consultatii[i];
            break;

        case 5:
            std::cout << "\n--- RETETE (" << nrRetete << ") ---\n";
            for (int i = 0; i < nrRetete; i++)
                std::cout << retete[i];
            break;

        case 6:
            std::cout << "\n--- MEDICI (" << nrMedici << ") ---\n";
            for (int i = 0; i < nrMedici; i++)
                std::cout << i + 1 << ". " << medici[i] << '\n';

            std::cout << "\n--- PACIENTI (" << nrPacienti << ") ---\n";
            for (int i = 0; i < nrPacienti; i++)
                std::cout << i + 1 << ". " << pacienti[i];

            std::cout << "\n--- PROGRAMARI (" << nrProgramari << ") ---\n";
            for (int i = 0; i < nrProgramari; i++)
                std::cout << i + 1 << ". " << programari[i] << '\n';

            std::cout << "\n--- CONSULTATII (" << nrConsultatii << ") ---\n";
            for (int i = 0; i < nrConsultatii; i++)
                std::cout << consultatii[i];

            std::cout << "\n--- RETETE (" << nrRetete << ") ---\n";
            for (int i = 0; i < nrRetete; i++)
                std::cout << retete[i];
            break;

        case 7:
            std::cout<<"Selectati data:\n";
            for (int i = 0; i < nrDate; i++)
                std::cout<<'('<< i+1 << ") "<<date[i]<<'\n';
            break;
        case 0:
            std::cout << "\nLa revedere! Cabinetul Medical Mercy.\n";
            break;
        default:
            std::cout << "Optiune invalida! Alegeti intre 0 si 5.\n";
        }
    } while (optiune != 0);

    delete[] medici;
    delete[] pacienti;
    delete[] programari;
    delete[] retete;
    delete[] consultatii;
    delete[] date;
    return 0;
}
