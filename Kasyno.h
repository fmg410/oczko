#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include "Karta.h"

#ifdef _WIN32
#define czyscKonsole system("cls")
#elif __linux__
#define czyscKonsole system("clear")
#elif __APPLE__
#define czyscKonsole system("clear")
#else
#define czyscKonsole printf("\n\n\n");
#endif

class Gracz;
class Bot;

class Kasyno
{
private:
	Karta talia[52];
	int nastepnaKartaDoWydania;
	int iloscLudzi;
	int iloscBotow;
	int sumaGraczy; // suma ilosci ludzi i botow
	Gracz** tablicaGraczy;

	const int maksymalnaIloscLudzi;
	const int maksymalnaIloscBotow;

	const int minimalnaIloscLudzi;
	const int minimalnaIloscBotow;

public:
	Kasyno();
	void tasujTalie();
	Karta* dajKarte();
	void generujTalie();
	void zapiszGre();
	void graj();

	Kasyno(const Kasyno& _kopia) = delete;
	Kasyno& operator=(const Kasyno& _kopia) = delete;
};

std::ostream& operator<<(std::ostream& os, const Karta& karta);
void wczytajEnter();
void wczytajInt(int& liczba, int dolnaGranica, int gornaGranica);