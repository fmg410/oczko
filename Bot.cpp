#include "Bot.h"
#include "Kasyno.h"

const int limitPunktowOdOdwagi[3] = { 11, 14, 18 }; // zachowawczy ; normalny ; ryzykujacy

Bot::Bot()
	: odwaga(0)
	, limitPunktow(0)
{}


bool Bot::sprawdzCzySpasowac()
{
	if (getIloscPunktow() >= limitPunktow)
	{
		setCzySpasowano(true);
		return true;
	}
	return false;
}

void Bot::wykonajTure()
{
	if (!sprawdzCzySpasowac())
	{
		wezKarte(kasyno->dajKarte());
	}
}

void Bot::setNazwa(std::string nazwa)
{
	std::string nazwaBota("Bot");
	nazwaBota.append(nazwa);
	Gracz::setNazwa(nazwaBota);
}

void Bot::setOdwaga(int _odwaga)
{
	if (_odwaga > 0 && odwaga < 4) {
		odwaga = _odwaga;
		limitPunktow = limitPunktowOdOdwagi[odwaga - 1];
	}
}