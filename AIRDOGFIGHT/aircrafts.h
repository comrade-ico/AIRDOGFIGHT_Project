#pragma once

#include<string>
#include<fstream>
#include<iostream>
#include<Windows.h>
#include<random>
#include<cmath>
#include<vector>

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

	bool stall;

	aircraft(int id = 0);
	void operator=(aircraft x);

	void statUpdate(int Alt, int Spd);

};

class card
{
public:
	card(int id, std::string name, std::string description, int SpdGet, int AltGet, double AngleTrans, int distanceGet, std::string type);
	card();
	void cardUse(aircraft& player, int& angle, int& distance, int playerID);
	void showInfo(aircraft& player);

	void operator=(card& inp);
	std::string name;
	std::string description;

private:
	int id;
	int SpdGet;
	int AltGet;
	double AngleTrans;
	int distanceGet;
	std::string type;

};


aircraft selectAircraft();

void clearScreen();

int randInt(int min, int max);

extern int attackWinrate_list1[8];
extern int attackWinrate_list2[8];
extern int attackWinrate_list3[8];

extern int cardQueue[4];

