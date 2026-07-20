#pragma once
#include"aircrafts.h"

class game
{//游戏运行
public:
	game();
	void ModeSelection();
	void fighterSelection();
	bool attack(int fighter, bool headon);
	void showStats();
//	void endTurn();
	bool AIplayer;

private:
	aircraft player[2];
	int distance;
	int angle;

};

void start();

bool attacking(int firepower, int distance, int dice, int* winrate);