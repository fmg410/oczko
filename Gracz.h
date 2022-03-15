#pragma once
#include <iostream>
#include <string>
#include "Karta.h"

class Kasyno;

class Gracz
{
protected:
	Karta* reka[10];
	int iloscKart;
	int iloscPunktow;
	std::string nazwa; // maksymalna dlugosc - 20 znakow
	bool czySpasowano;
	Kasyno* kasyno;

public:
	Gracz();
	void wezKarte(Karta* karta);
	void wyswietlKarty();
	virtual void wykonajTure();
	Karta* operator[](const int _indeks);

	int getIloscPunktow() { return iloscPunktow; }
	int getIloscKart() { return iloscKart; }
	void setCzySpasowano(bool _czySpasowano) { czySpasowano = _czySpasowano; }
	bool getCzySpasowano() { return czySpasowano; }
	virtual void setNazwa(std::string _nazwa) { nazwa = _nazwa.substr(0, 20); }
	std::string getNazwa() { return nazwa; }
	void setKasyno(Kasyno* _kasyno) { kasyno = _kasyno; }
};

