//format：
//ID
//name
//WEP
//Turnrate 
//SpdMx
//EnergyTrans
//Firepower

#include"FighterSelection.h"
#include<fstream>
#include<iostream>
#include<Windows.h>

void selectAircraft()
{
	int tNum;
	while (1)
	{
		std::cout << "请选择您的战机编号（现版本编号范围：0~1，输入-1拉出战斗机列表）：";
		std::cin >> tNum;
		if (tNum == -1)
		{
			std::ifstream Fighters;
			Fighters.open("Fighters.txt", std::ios::in);
			std::string line;
			while (getline(Fighters, line))
			{
				std::cout << "ID:" << line << std::endl;
				getline(Fighters, line);
				std::cout << "战机名称:" << line << std::endl;
				getline(Fighters, line);
				std::cout << "产能:" << line << std::endl;
				getline(Fighters, line);
				std::cout << "回转能力值:" << line << std::endl;
				getline(Fighters, line);
				std::cout << "最大速度:" << line << std::endl;
				getline(Fighters, line);
				std::cout << "存能值:" << line << std::endl;
				getline(Fighters, line);
				std::cout << "火力值:" << line << std::endl << std::endl;
			}
		}
		else
		{
			aircraft fighter(tNum);
			break;
		}
	}
	return;
}


aircraft::aircraft(int id)
	:Spd(0), Alt(0), name(""), WEP(0), turnRate(0), SpdMx(0), EnergyTransRate(0), firePower(0)
{
	std::ifstream Fighters;
	std::string line;
	bool success = 0;
	try
	{
		Fighters.open("Fighters.txt", std::ios::in);
		if (!Fighters.is_open())
		{
			throw "missing file!";
		}

		while (getline(Fighters, line))
		{
			if (stoi(line) == id)
			{
				success = 1;
				getline(Fighters, line);
				name = line;
				getline(Fighters, line);
				WEP = stoi(line);
				getline(Fighters, line);
				turnRate = stod(line);
				getline(Fighters, line);
				SpdMx = stoi(line);
				getline(Fighters, line);
				EnergyTransRate = stod(line);
				getline(Fighters, line);
				firePower = stoi(line);
				Fighters.close();
				break;
			}
			else
			{
				//std::cout << "jump:" << std::endl;
				for (int i = 0; i < 6; i++)
				{
					//std::cout << line;
					getline(Fighters, line);
				}
				continue;
			}
		}


	}
	catch (std::string err)
	{
		std::cerr << "错误：未能读取文件！（请检查文件完整性）" << std::endl;
		Sleep(3000);
		exit(EXIT_FAILURE);
	}
	if (success)
	{
		std::cout << "读取战斗机数据成功！请进入座机！" << std::endl;
		return;
	}
	else
	{
		std::cout << "对应战机未能找到，请进入默认座机！" << std::endl;
		aircraft temp(0);
		name = temp.name;
		WEP = temp.WEP;
		turnRate = temp.turnRate;
		SpdMx = temp.SpdMx;
		EnergyTransRate = temp.EnergyTransRate;
		firePower = temp.firePower;
		return;
	}
}

