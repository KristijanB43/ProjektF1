#ifndef F1_H
#define F1_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define FILENAME "formula1_data.txt"
#define MAX_VOZACI 100

typedef struct {
    int id;
    char ime[MAX_LENGTH];
    char prezime[MAX_LENGTH];
    char drzava[MAX_LENGTH];
    char tim[MAX_LENGTH];
    int dob;
    int bodovi;
} Vozac;

extern Vozac vozaci[MAX_VOZACI];
extern int broj_vozaca;

void unos_vozaca();
void citanje_vozaca();
void brisanje_vozaca();
void azuriraj_podatke();
void sortiraj_vozace();
void izbornik();
void ucitaj_podatke();  // Dodano: Funkcija za učitavanje podataka iz datoteke

#endif // F1_H
