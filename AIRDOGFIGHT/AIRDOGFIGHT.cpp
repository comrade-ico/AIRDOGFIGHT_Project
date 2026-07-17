#include <cstdlib>
#include"aircrafts.h"
//卡牌！？

int main()
{
	std::string inpMem;
	std::cout << "嘿！欢迎打开AIRDOGFIGHT——一款空战卡牌游戏！" << std::endl;
	Sleep(500);
	std::cout << "想要查看游戏规则吗？Y/N" << std::endl;
	std::cin >> inpMem;
	
	if (inpMem != "N" && inpMem != "n")
	{
		std::ifstream file("Rules_CH.txt", std::ios::in);
		while (getline(file, inpMem))
		{
			std::cout << inpMem << std::endl;
			Sleep(50);
		}
		std::cout << "输入任意键后按回车以继续……" << std::endl;
		std::cin >> inpMem;
		clearScreen();
	}

	while (1)
	{
		
	}



	return 0;
}
