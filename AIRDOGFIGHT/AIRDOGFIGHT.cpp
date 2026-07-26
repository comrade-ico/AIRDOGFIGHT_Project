#include <cstdlib>
#include"aircrafts.h"
#include<stdexcept>
#include"game.h"
//卡牌！？

int main()
{
	try
	{
		std::string inpMem;
		std::cout << "嘿！欢迎打开AIRDOGFIGHT——一款空战卡牌游戏！" << std::endl;
		Sleep(500);
		std::cout << "想要查看游戏规则吗？Y/N" << std::endl;
		inpMem = readToken();
		
		if (inpMem != "N" && inpMem != "n")
		{
			std::ifstream file;
			file.open(dataFilePath("Rules_CH.txt"), std::ios::in);
			if (!file.is_open())
			{
				throw std::runtime_error("无法打开 Rules_CH.txt");
			}
			while (getline(file, inpMem))
			{
				std::cout << inpMem << std::endl;
				Sleep(50);
			}
			std::cout << "输入任意键后按回车以继续……" << std::endl;
			inpMem = readToken();
			clearScreen();
		}
		start();
	}
	catch (const std::exception& err)
	{
		std::cerr << "程序无法继续：" << err.what() << "。" << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}
