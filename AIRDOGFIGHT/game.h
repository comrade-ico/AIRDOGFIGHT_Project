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
	void genKardQueue(int fighter, int (& outQueue)[4]);
	void useCard(int choise, int(&outQueue)[4],int fighter);
	void turnUseCard(std::string choice, int (&cardQueue)[4], int id);
	bool enableAttack();
	bool enableHeadon();
	void endTurn();
	int headon();
	int relativeAngleRatio() const;
	double effectiveDistance() const;

	bool AIplayer;
	aircraft player[2];
	int distance;
	int angle;
	bool stall[2];
	int cardQueues[2][4];

private:
	std::vector<card> cards;
	int cardCount;

};

void start();
bool checkQueue(int inp, int queue[4]);
bool attacking(int firepower, int distance, int dice, int* winrate);
