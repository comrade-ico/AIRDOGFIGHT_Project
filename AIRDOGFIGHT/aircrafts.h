#pragma once

#include<string>
#include<fstream>
#include<iostream>
#include<Windows.h>
#include<random>
#include<cmath>

class aircraft
{
public:
	std::string name;
	double turnRate;
	int SpdMx;
	int SpdUs;
	int WEP;
	double energyTransRate;
	int firePower;

	int Alt;
	int Spd;

	aircraft(int id = 0);
	void operator=(aircraft x);

	void statUpdate(int Alt, int Spd);

private:

};


aircraft selectAircraft();

void clearScreen();

int randInt(int min, int max);

extern int attackWinrate_list1[8];
extern int attackWinrate_list2[8];
extern int attackWinrate_list3[8];