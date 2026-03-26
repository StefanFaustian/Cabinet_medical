# Cabinet medical

La cabinetul medical Mercy se testează implementarea unei aplicații software de gestiune a serviciilor medicale oferite la cabinetul medical. Clasele care stau la baza creării aplicației sunt:

* clasa _Pacient_, având câmpurile `nume`, `telefon`, `vârsta` și un boolean `asigurat`.
* clasa _Medic_ având câmpurile `nume` și `specializare`.
* clasa _Data_ având câmpurile `zi`, `luna`, `an`.
* clasa _Ora_ având câmpurile `ora`, `minut`.
* clasa _Rețetă_, caracterizată de `idReteta` (generată de `contorId`), `pacient`, `medic`, `data`, `tratament`, `durata`.
* clasa _Programare_ care conține obiectele `pacient`, `medic`, `dataProgramarii` și `oraProgramarii`.
* clasa _Consultație_ care are în componență obiectul `programare`, `tarif` și șirurile de caractere `tratament`, respectiv `diagnostic`.

Clasele _Data_ și _Ora_ sunt clase ajutătoare, asigurând organizarea programului cabinetului medical prin efectuarea de calcule pe diferite date calendaristice sau ore.

**Date de intrare**

Datele de intrare sunt predefinite în programul principal și cuprind:

* lista medicilor angajați la cabinet (nume și specializare)
* lista pacienților înregistrați (nume, vârstă, telefon, status asigurare)
* programările efectuate de pacienți (pacient, medic, data, ora)
* consultațiile realizate în urma programărilor (diagnostic, tratament, tarif)
* programul de funcționare al cabinetului (ora deschidere, ora închidere)

**Operații posibile**

* Validarea datelor calendaristice: verificarea corectitudinii zilei în funcție de lună și an;
* Validarea orei: verificarea că ora și minutele sunt în intervalele corecte (0-23, 0-59);
* Verificarea programului de lucru: o programare este acceptată doar dacă ora se încadrează în programul cabinetului;
* Detectarea conflictelor de orar: două programări la același medic, în aceeași zi, la ore prea apropiate sunt semnalate ca și conflict;
* Calculul reducerilor: tariful unei consultații este ajustat automat în funcție de statusul pacientului (asigurat, pensionar, copil);
* Generarea rețetelor: o rețetă este creată automat în urma unei consultații, preluând datele medicului, pacientului și tratamentul prescris;
* Gestionarea listelor: adăugarea dinamică a medicilor, pacienților, programărilor, consultațiilor și rețetelor în colecții alocate dinamic;
* Afișarea datelor: vizualizarea tuturor entităților înregistrate în sistem prin intermediul unui meniu interactiv bazat pe selectia unor optiuni date.


**Surse auxiliare utilizate:**
- pentru functia predefinita sscanf() - https://www.w3schools.com/c/ref_stdio_sscanf.php 

