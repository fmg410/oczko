#include "Gracz.h"
#include "Kasyno.h"

Gracz::Gracz()
	: iloscKart(0)
	, iloscPunktow(0)
	, czySpasowano(false)
	, kasyno(nullptr)
	, reka{ nullptr, }
{}

void Gracz::wezKarte(Karta* karta)
{
	if (karta != nullptr)
	{
		if (iloscKart < 10)
		{
			reka[iloscKart] = karta;
			iloscPunktow += reka[iloscKart]->getWartosc();
			iloscKart++;
			if (iloscPunktow >= 21)
			{
				czySpasowano = true;
			}
		}
	}
}

void Gracz::wyswietlKarty()
{
	for (int i = 0; i < iloscKart; i++)
	{
		reka[i]->wypisz();
		std::cout << std::endl;
	}
}

void Gracz::wykonajTure()
{
	while (true)
	{
		czyscKonsole;
		int wyborUzytkownika = 0;
		std::cout << "Gracz " << nazwa << ":\n\n";
		std::cout << "Wybierz akcje:\n1.Wyswietl reke\n2.Dobierz\n3.Pasuj\n";
		wczytajInt(wyborUzytkownika, 1, 3);

		if (wyborUzytkownika == 1)
		{
			std::cout << "\nKarty na rece:\n";
			wyswietlKarty();
			std::cout << "Suma punktow: " << iloscPunktow << "\n";
			std::cout << "Nacisnij enter aby kontynuowac\n";
			wczytajEnter();
		}
		else if (wyborUzytkownika == 2)
		{
			wezKarte(kasyno->dajKarte());
			std::cout << "\nKarty po dobraniu:\n";

			wyswietlKarty();
			std::cout << "Suma punktow: " << iloscPunktow << "\n";
			std::cout << "Nacisnij enter aby kontynuowac\n";
			wczytajEnter();
			break;
		}
		else if (wyborUzytkownika == 3)
		{
			czySpasowano = true;
			break;
		}
	}
}

Karta* Gracz::operator[](const int _indeks)
{
	if (_indeks >= 0 && _indeks < iloscKart)
	{
		return reka[_indeks];
	}
	return nullptr;
}