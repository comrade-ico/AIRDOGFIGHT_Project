#pragma once

#include<string>
#include<fstream>
#include<iostream>
#include<Windows.h>

class aircraft
{
public:
	std::string name;
	double turnRate;
	int SpdMx;
	int SpdUs;
	int WEP;
	double EnergyTransRate;
	int firePower;

	aircraft(int id);

	void statUpdate(int Alt, int Spd);

private:
	int Alt;
	int Spd;

};


aircraft selectAircraft();

void clearScreen();