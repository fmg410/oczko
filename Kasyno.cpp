#include "Kasyno.h"
#include "Gracz.h"
#include "Bot.h"

std::ostream& operator<<(std::ostream& os, const Karta& karta)
{
	/*znaki zastepcze dla kolorow kart, oryginalne znaki nie wyswietlaly sie poprawnie w pliku*/
	char odpowiednikiKolorow[4] = { '&', '#', '%', '^' }; // kier ; karo ; trefl ; pik
	os << karta.getFigura() << odpowiednikiKolorow[karta.getKolor() - 3];
	return os;
}

void wczytajEnter()
{
	if (std::cin.get() != '\n')
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void wczytajInt(int& liczba, int dolnaGranica, int gornaGranica)
{
	while (true)
	{
		while (true) {
			std::cin >> liczba;
			if (std::cin.fail() == true) {
				std::cout << "wykryto blad" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else break;
		}
		if (liczba >= dolnaGranica && liczba <= gornaGranica)
		{
			break;
		}
		else
		{
			std::cout << "Wprowadzono liczbe z poza dostepnego zakresu" << std::endl;
		}
	}
	wczytajEnter();
}

Kasyno::Kasyno()
	: iloscLudzi(0)
	, iloscBotow(0)
	, sumaGraczy(0)
	, nastepnaKartaDoWydania(0)
	, tablicaGraczy(nullptr)
	, maksymalnaIloscLudzi(3)
	, maksymalnaIloscBotow(3)
	, minimalnaIloscLudzi(1)
	, minimalnaIloscBotow(1)
{
	generujTalie();
}

void Kasyno::tasujTalie()
{
	int karta1, karta2;
	Karta tymczasowaKarta;

	for (int i = 0; i < 100; i++)
	{
		karta1 = rand() % 52;
		do {
			karta2 = rand() % 52;
		} while (karta1 == karta2);
		tymczasowaKarta = talia[karta1];
		talia[karta1] = talia[karta2];
		talia[karta2] = tymczasowaKarta;
	}
}

Karta* Kasyno::dajKarte()
{
	if (nastepnaKartaDoWydania < 52)
	{
		nastepnaKartaDoWydania++;
		return &(talia[nastepnaKartaDoWydania]);
	}
	else
	{
		return nullptr;
	}
}

void Kasyno::generujTalie()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			talia[13 * i + j].setKolor(i);
			talia[13 * i + j].setWartosc(j);
		}
	}
}

void Kasyno::zapiszGre()
{
	std::ofstream plik;
	plik.open("PrzebiegGry.txt", std::ifstream::out);

	if (plik.is_open())
	{
		for (int i = 0; i < sumaGraczy; i++)
		{
			plik.setf(std::ios::left, std::ios::adjustfield);
			plik << std::setfill(' ');
			/*dodatkowe 5 znakow szerokosci, zeby od razu po nazwie gracza nie pojawila sie karta, jezeli nazwa gracza ma maksymalna dlugosc*/
			plik << std::setw(25);
			if (i < iloscLudzi)
			{
				plik << tablicaGraczy[i]->getNazwa();
			}
			else
			{
				plik << tablicaGraczy[i]->getNazwa().append(" ").append(std::to_string(((Bot*)tablicaGraczy[i])->getOdwaga()));
			}
			for (int j = 0; j < tablicaGraczy[i]->getIloscKart(); j++)
			{
				plik << *((*(tablicaGraczy[i]))[j]) << " ";
			}
			plik << std::setw(35 - (tablicaGraczy[i]->getIloscKart() * 3)) << "";
			plik.setf(std::ios::right, std::ios::adjustfield);
			plik << std::setw(2) << tablicaGraczy[i]->getIloscPunktow();
			plik << std::endl;
		}
		plik << "\n& - kier ; # - karo ; % - trefl ; ^ - pik";
		plik.close();
	}
}

void Kasyno::graj()
{
	tasujTalie();
	nastepnaKartaDoWydania = 0;
	iloscLudzi = 0;
	iloscBotow = 0;
	int wyborUzytkownika = 0;
	bool czyKoniecGry = false;

	std::cout << "Podaj liczbe graczy (od " << minimalnaIloscLudzi << " do " << maksymalnaIloscLudzi << "): ";
	wczytajInt(wyborUzytkownika, minimalnaIloscLudzi, maksymalnaIloscLudzi);

	iloscLudzi = wyborUzytkownika;

	std::cout << "Podaj liczbe graczy komputerowych (od " << minimalnaIloscBotow << " do " << maksymalnaIloscBotow << "): ";
	wczytajInt(wyborUzytkownika, minimalnaIloscBotow, maksymalnaIloscBotow);

	iloscBotow = wyborUzytkownika;

	sumaGraczy = iloscLudzi + iloscBotow;

	tablicaGraczy = new Gracz * [sumaGraczy];

	if (tablicaGraczy == nullptr)
	{
		return;
	}

	for (int i = 0; i < iloscLudzi; i++)
	{
		tablicaGraczy[i] = new Gracz;
	}

	for (int i = iloscLudzi; i < sumaGraczy; i++)
	{
		tablicaGraczy[i] = new Bot;
	}

	for (int i = 0; i < iloscLudzi; i++)
	{
		std::string bufor;
		do {
			std::cout << "\nPodaj nazwe gracza " << i + 1 << " (maksymalnie 20 znakow):\n";
			std::getline(std::cin, bufor);
		} while (bufor.length() == 0);
		tablicaGraczy[i]->setNazwa(bufor);
	}

	for (int i = iloscLudzi; i < sumaGraczy; i++)
	{
		tablicaGraczy[i]->setNazwa(std::to_string(i - iloscLudzi + 1));
		std::cout << "\nWybierz poziom ryzyka dla " << tablicaGraczy[i]->getNazwa() << "\n1.Zachowawczy\n2.Normalny\n3.Ryzykujacy\n";
		wczytajInt(wyborUzytkownika, 1, 3);

		((Bot*)tablicaGraczy[i])->setOdwaga(wyborUzytkownika);
	}

	for (int i = 0; i < sumaGraczy; i++)
	{
		tablicaGraczy[i]->setKasyno(this);
		for (int j = 0; j < 2; j++)
		{
			tablicaGraczy[i]->wezKarte(dajKarte());
		}
	}

	/*glowna petla gry*/
	while (!czyKoniecGry)
	{
		/*tury graczy*/
		for (int i = 0; i < sumaGraczy; i++)
		{
			if (!tablicaGraczy[i]->getCzySpasowano())
			{
				tablicaGraczy[i]->wykonajTure();
			}
		}

		/*sprawdzenie czy wszyscy spasowali*/
		czyKoniecGry = true;
		for (int i = 0; i < sumaGraczy; i++)
		{
			if (tablicaGraczy[i]->getCzySpasowano() == false)
			{
				czyKoniecGry = false;
				break;
			}
		}

	}

	/*wyznaczanie zwyciezcy*/
	int zwyciezca = 0;
	int punktyZwyciezcy = 0;

	for (int i = 0; i < sumaGraczy; i++)
	{
		if (tablicaGraczy[i]->getIloscPunktow() > punktyZwyciezcy)
		{
			if (tablicaGraczy[i]->getIloscPunktow() <= 21)
			{
				punktyZwyciezcy = tablicaGraczy[i]->getIloscPunktow();
				zwyciezca = i;
			}
		}
	}

	int iloscZwyciezcow = 0;
	for (int i = 0; i < sumaGraczy; i++)
	{
		if (tablicaGraczy[i]->getIloscPunktow() == punktyZwyciezcy)
		{
			iloscZwyciezcow++;
		}
	}

	czyscKonsole;
	if (punktyZwyciezcy == 0)
	{
		std::cout << "Nikt nie wygral, wszyscy przekroczyli limit punktow\n";
	}
	else if (iloscZwyciezcow == 1)
	{
		std::cout << "Wygral gracz " << tablicaGraczy[zwyciezca]->getNazwa() << " z iloscia punktow : " << punktyZwyciezcy << "\n";
	}
	else if (iloscZwyciezcow > 1)
	{
		std::cout << "Remis! Zwyciezcy to:\n";
		for (int i = 0; i < sumaGraczy; i++)
		{
			if (tablicaGraczy[i]->getIloscPunktow() == punktyZwyciezcy)
			{
				std::cout << "Gracz " << tablicaGraczy[i]->getNazwa() << std::endl;
			}
		}
	}

	zapiszGre();
	for (int i = 0; i < sumaGraczy; i++)
	{
		delete tablicaGraczy[i];
	}
	delete[] tablicaGraczy;
	tablicaGraczy = nullptr;
	std::cout << "Nacisnij enter aby kontynuowac\n";
	wczytajEnter();
}