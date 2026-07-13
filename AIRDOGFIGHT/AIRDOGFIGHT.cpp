#include <fstream>
#include<Windows.h>
#include <iostream>
#include"FighterSelection.h"
//卡牌！？

int main()
{
	std::cout << "嘿！欢迎打开AIRDOGFIGHT——一款空战卡牌游戏！" << std::endl;
	Sleep(500);
	std::cout << "第一步是选择您的战机！" << std::endl;

	selectAircraft();
	return 0;
}
