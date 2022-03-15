#pragma once
#include "Gracz.h"
class Bot : public Gracz
{
private:
	int odwaga;
	int limitPunktow;
public:
	Bot();
	bool sprawdzCzySpasowac();
	void wykonajTure() override;

	void setNazwa(std::string _nazwa) override;
	void setOdwaga(int _odwaga);
	int getOdwaga() { return odwaga; }
};