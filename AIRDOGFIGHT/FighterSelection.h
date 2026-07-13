#pragma once
#include<string>
class aircraft
{
public:
	std::string name;
	double turnRate;
	int SpdMx;
	int WEP;
	double EnergyTransRate;
	int firePower;

	aircraft(int id);

	void statUpdate(int Alt, int Spd);

private:
	int Alt;
	int Spd;

};


void selectAircraft();