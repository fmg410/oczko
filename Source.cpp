#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Kasyno.h"
#include "Gracz.h"
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

int main()
{
	srand((unsigned int)time(0));
	Kasyno kasyno;
	bool czyGracDalej = true;
	int wyborUzytkownika;

	do {
		kasyno.graj();
		czyscKonsole;
		std::cout << "Czy grac dalej?\n1.Tak\n2.Nie\n";
		wczytajInt(wyborUzytkownika, 1, 2);
		if (wyborUzytkownika == 2)
		{
			czyGracDalej = false;
		}
		czyscKonsole;
	} while (czyGracDalej);



	return 0;
}