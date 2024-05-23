#include "f1.h"

Vozac vozaci[MAX_VOZACI];
int broj_vozaca = 0;
int globalni_id = 0;

typedef enum {
    IZLAZ = 0,
    UNOS_VOZACA,
    CITANJE_VOZACA,
    BRISANJE_VOZACA,
    AZURIRANJE_PODATAKA,
    SORTIRANJE_VOZACA
} Opcije;

const char* timovi[] = {
    "Red Bull",
    "Mercedes",
    "McLaren",
    "Ferrari",
    "Alpine",
    "Aston Martin",
    "Visa Cash App RB",
    "Williams",
    "Kick Sauber",
    "Haas"
};

void prikazi_timove() {
    printf("\n-----------------------------------\n");
    printf("Odaberite tim:\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < 10; i++) {
        printf("%d. %s\n", i + 1, timovi[i]);
    }
}

void spremi_podatke() {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    for (int i = 0; i < broj_vozaca; i++) {
        Vozac vozac = vozaci[i];
        fprintf(file, "%d,%s,%s,%s,%s,%d,%d\n", vozac.id, vozac.ime, vozac.prezime, vozac.drzava, vozac.tim, vozac.dob, vozac.bodovi);
    }

    fclose(file);
    printf("Podaci uspjesno azurirani u datoteci.\n");
    printf("-----------------------------------\n");
}

void unos_vozaca() {
    if (broj_vozaca >= MAX_VOZACI) {
        printf("Dosegnut maksimalan broj vozaca.\n");
        return;
    }

    Vozac novi_vozac;
    globalni_id++;
    novi_vozac.id = globalni_id;

    printf("\nUnesite ime vozaca: ");
    scanf("%s", novi_vozac.ime);
    printf("Unesite prezime vozaca: ");
    scanf("%s", novi_vozac.prezime);
    printf("Unesite drzavu vozaca: ");
    scanf("%s", novi_vozac.drzava);

    int izbor_tima;
    do {
        prikazi_timove();
        printf("-----------------------------------\n");
        printf("Unesite broj tima (1-10): ");
        if (scanf("%d", &izbor_tima) != 1 || izbor_tima < 1 || izbor_tima > 10) {
            printf("Neispravan unos. Pokusajte ponovo.\n");
            while (getchar() != '\n'); // Čišćenje ulaza
        }
        else {
            strcpy(novi_vozac.tim, timovi[izbor_tima - 1]);
            break;
        }
    } while (1);

    printf("Unesite dob vozaca: ");
    while (scanf("%d", &novi_vozac.dob) != 1) {
        printf("Neispravan unos. Unesite ponovo dob: ");
        while (getchar() != '\n'); // Čišćenje ulaza
    }
    printf("Unesite broj bodova vozaca: ");
    while (scanf("%d", &novi_vozac.bodovi) != 1) {
        printf("Neispravan unos. Unesite ponovo broj bodova: ");
        while (getchar() != '\n'); // Čišćenje ulaza
    }

    vozaci[broj_vozaca++] = novi_vozac;

    printf("\n-----------------------------------\n");
    printf("Vozac uspjesno dodan.\n");
    printf("-----------------------------------\n");

    spremi_podatke(); // Spremanje podataka nakon unosa
}

void citanje_vozaca() {
    if (broj_vozaca == 0) {
        printf("Nema unesenih vozaca.\n");
        return;
    }

    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("|  ID |         Ime        |        Prezime       |     Drzava     |          Tim         | Godine |  Bodovi  |\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < broj_vozaca; i++) {
        Vozac vozac = vozaci[i];
        printf("| %3d | %18s | %20s | %14s | %20s | %6d | %8d |\n", vozac.id, vozac.ime, vozac.prezime, vozac.drzava, vozac.tim, vozac.dob, vozac.bodovi);
    }
    printf("---------------------------------------------------------------------------------------------------------------\n");
}

void brisanje_vozaca() {
    int id;
    printf("\n-----------------------------------\n");
    printf("Unesite ID vozaca kojeg zelite izbrisati: ");
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos ID-a.\n");
        while (getchar() != '\n'); // Čišćenje ulaza
        return;
    }

    int found = 0;
    for (int i = 0; i < broj_vozaca; i++) {
        if (vozaci[i].id == id) {
            for (int j = i; j < broj_vozaca - 1; j++) {
                vozaci[j] = vozaci[j + 1];
            }
            broj_vozaca--;
            found = 1;
            printf("Vozac uspjesno obrisan.\n");
            break;
        }
    }

    if (!found) {
        printf("\n-----------------------------------\n");
        printf("Vozac sa ID %d nije pronaden.\n", id);
        printf("-----------------------------------\n");
    }

    spremi_podatke(); // Spremanje podataka nakon brisanja
}

void azuriraj_podatke() {
    citanje_vozaca();

    int id;
    printf("\nUnesite ID vozaca kojeg zelite azurirati:\n");
    if (scanf("%d", &id) != 1) {
        printf("Neispravan unos ID-a.\n");
        while (getchar() != '\n'); // Čišćenje ulaza
        return;
    }

    int found = 0;
    for (int i = 0; i < broj_vozaca; i++) {
        if (vozaci[i].id == id) {
            found = 1;

            printf("\nUnesite novo ime vozaca: ");
            scanf("%s", vozaci[i].ime);
            printf("Unesite novo prezime vozaca: ");
            scanf("%s", vozaci[i].prezime);
            printf("Unesite novu drzavu vozaca: ");
            scanf("%s", vozaci[i].drzava);

            int izbor_tima;
            do {
                prikazi_timove();
                printf("Unesite broj novog tima (1-10): ");
                if (scanf("%d", &izbor_tima) != 1 || izbor_tima < 1 || izbor_tima > 10) {
                    printf("Neispravan unos. Pokusajte ponovo.\n");
                    while (getchar() != '\n'); // Čišćenje ulaza
                }
                else {
                    strcpy(vozaci[i].tim, timovi[izbor_tima - 1]);
                    break;
                }
            } while (1);

            printf("Unesite novu dob vozaca: ");
            while (scanf("%d", &vozaci[i].dob) != 1) {
                printf("Neispravan unos. Unesite ponovo dob: ");
                while (getchar() != '\n'); // Čišćenje ulaza
            }
            printf("Unesite novi broj bodova vozaca: ");
            while (scanf("%d", &vozaci[i].bodovi) != 1) {
                printf("Neispravan unos. Unesite ponovo broj bodova: ");
                while (getchar() != '\n'); // Čišćenje ulaza
            }

            printf("-----------------------------------\n");
            printf("Podaci vozaca uspjesno azurirani.\n");
            printf("-----------------------------------\n");
            break;
        }
    }

    if (!found) {
        printf("Vozac sa ID %d nije pronaden.\n", id);
    }

    spremi_podatke(); // Spremanje podataka nakon ažuriranja
}

void ucitaj_podatke() {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Nema podataka za ucitati.\n");
        return;
    }

    broj_vozaca = 0;
    while (fscanf(file, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%d,%d\n", &vozaci[broj_vozaca].id, vozaci[broj_vozaca].ime, vozaci[broj_vozaca].prezime, vozaci[broj_vozaca].drzava, vozaci[broj_vozaca].tim, &vozaci[broj_vozaca].dob, &vozaci[broj_vozaca].bodovi) != EOF) {
        broj_vozaca++;
    }

    fclose(file);

    // Postavljanje globalnog ID-a na najveći ID u datoteci
    globalni_id = 0;
    for (int i = 0; i < broj_vozaca; i++) {
        if (vozaci[i].id > globalni_id) {
            globalni_id = vozaci[i].id;
        }
    }
    printf("-----------------------------------\n");
    printf("\tUcitano %d vozaca.\n", broj_vozaca);
    printf("-----------------------------------\n");
}

int compare_bodovi_uzlazno(const void* a, const void* b) {
    Vozac* vozacA = (Vozac*)a;
    Vozac* vozacB = (Vozac*)b;
    return vozacA->bodovi - vozacB->bodovi;
}

int compare_bodovi_silazno(const void* a, const void* b) {
    Vozac* vozacA = (Vozac*)a;
    Vozac* vozacB = (Vozac*)b;
    return vozacB->bodovi - vozacA->bodovi;
}

int compare_ime_uzlazno(const void* a, const void* b) {
    Vozac* vozacA = (Vozac*)a;
    Vozac* vozacB = (Vozac*)b;
    return strcmp(vozacA->ime, vozacB->ime);
}

int compare_ime_silazno(const void* a, const void* b) {
    Vozac* vozacA = (Vozac*)a;
    Vozac* vozacB = (Vozac*)b;
    return strcmp(vozacB->ime, vozacA->ime);
}

int compare_id_uzlazno(const void* a, const void* b) {
    Vozac* vozacA = (Vozac*)a;
    Vozac* vozacB = (Vozac*)b;
    return vozacA->id - vozacB->id;
}

int compare_id_silazno(const void* a, const void* b) {
    Vozac* vozacA = (Vozac*)a;
    Vozac* vozacB = (Vozac*)b;
    return vozacB->id - vozacA->id;
}

void sortiraj_vozace() {
    if (broj_vozaca == 0) {
        printf("\n-----------------------------------\n");
        printf("Nema unesenih vozaca.\n");
        printf("-----------------------------------\n");
        return;
    }

    int opcija;
    printf("\n-----------------------------------\n");
    printf("Odaberite kriterij za sortiranje:\n");
    printf("-----------------------------------\n");
    printf("1. Bodovi - (Uzlazno)\n");
    printf("2. Bodovi - (Silazno)\n");
    printf("3. Ime - (Uzlazno)\n");
    printf("4. Ime - (Silazno)\n");
    printf("5. ID - (Uzlazno)\n");
    printf("6. ID - (Silazno)\n");
    printf("-----------------------------------\n");

    if (scanf("%d", &opcija) != 1) {
        printf("Neispravan unos.\n");
        while (getchar() != '\n'); // Čišćenje ulaza
        return;
    }

    switch (opcija) {
    case 1:
        qsort(vozaci, broj_vozaca, sizeof(Vozac), compare_bodovi_uzlazno);
        printf("\n-----------------------------------\n");
        printf("Vozaci sortirani po bodovima uzlazno.\n");
        printf("-----------------------------------\n");
        break;
    case 2:
        qsort(vozaci, broj_vozaca, sizeof(Vozac), compare_bodovi_silazno);
        printf("\n-----------------------------------\n");
        printf("Vozaci sortirani po bodovima silazno.\n");
        printf("-----------------------------------\n");
        break;
    case 3:
        qsort(vozaci, broj_vozaca, sizeof(Vozac), compare_ime_uzlazno);
        printf("\n-----------------------------------\n");
        printf("Vozaci sortirani po imenu abecedno uzlazno.\n");
        printf("-----------------------------------\n");
        break;
    case 4:
        qsort(vozaci, broj_vozaca, sizeof(Vozac), compare_ime_silazno);
        printf("\n-----------------------------------\n");
        printf("Vozaci sortirani po imenu abecedno silazno.\n");
        printf("-----------------------------------\n");
        break;
    case 5:
        qsort(vozaci, broj_vozaca, sizeof(Vozac), compare_id_uzlazno);
        printf("\n-----------------------------------\n");
        printf("Vozaci sortirani po ID-u uzlazno.\n");
        printf("-----------------------------------\n");
        break;
    case 6:
        qsort(vozaci, broj_vozaca, sizeof(Vozac), compare_id_silazno);
        printf("\n-----------------------------------\n");
        printf("Vozaci sortirani po ID-u silazno.\n");
        printf("-----------------------------------\n");
        break;
    default:
        printf("\n-----------------------------------\n");
        printf("Neispravna opcija.\n");
        printf("-----------------------------------\n");
        return;
    }

    citanje_vozaca(); // Ispisivanje sortirane liste vozača
    spremi_podatke(); // Spremanje podataka nakon sortiranja
}

void izbornik() {
    ucitaj_podatke(); //Učitaj podatke pri pokretanju programa
    Opcije izbor;
    do {
        printf("\n\tIzaberite opciju:\n");
        printf("-----------------------------------\n");
        printf("1. Unos novog vozaca\n");
        printf("2. Prikazi sve vozace\n");
        printf("3. Brisanje vozaca\n");
        printf("4. Azuriraj podatke\n");
        printf("5. Sortiraj vozace\n");
        printf("0. Izlaz iz programa\n");
        printf("-----------------------------------\n");
        printf("\n");

        if (scanf("%d", &izbor) != 1) {
            printf("Neispravan unos.\n");
            while (getchar() != '\n'); // Čišćenje ulaza
            continue;
        }

        switch (izbor) {
        case UNOS_VOZACA:
            unos_vozaca();
            break;
        case CITANJE_VOZACA:
            citanje_vozaca();
            break;
        case BRISANJE_VOZACA:
            brisanje_vozaca();
            break;
        case AZURIRANJE_PODATAKA:
            azuriraj_podatke();
            break;
        case SORTIRANJE_VOZACA:
            sortiraj_vozace();
            break;
        case IZLAZ:
            printf("\n-----------------------------------\n");
            printf("Izlazak iz programa.\n");
            printf("-----------------------------------\n");
            break;
        default:
            printf("Neispravan izbor. Pokusajte ponovo.\n");
            break;
        }
    } while (izbor != IZLAZ);
}
