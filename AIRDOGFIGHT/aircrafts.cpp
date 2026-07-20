//format：
//ID
//name
//WEP
//Turnrate 
//SpdMx
//SpdUs
//EnergyTrans
//Firepower

#include"aircrafts.h"


int attackWinrate_list1[8] = { 7,6,5,3,4,5,6,7 };
int attackWinrate_list2[8] = { 7,5,4,3,3,4,5,6 };
int attackWinrate_list3[8] = { 7,5,3,2,4,5,6,7 };


aircraft selectAircraft()
{
	int tNum;
	while (1)
	{
		std::cout << "请选择战机编号（现版本编号范围：0~1，输入-1拉出战斗机列表）：";
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
				Sleep(40);
				std::cout << "战机名称:" << line << std::endl;
				getline(Fighters, line);
				Sleep(40);
				std::cout << "产能:" << line << std::endl;
				getline(Fighters, line);
				Sleep(40);
				std::cout << "回转能力值:" << line << std::endl;
				getline(Fighters, line);
				Sleep(40);
				std::cout << "最大速度:" << line << std::endl;
				getline(Fighters, line);
				Sleep(40);
				std::cout << "有效速度:" << line << std::endl;
				getline(Fighters, line);
				Sleep(40);
				std::cout << "存能值:" << line << std::endl;
				getline(Fighters, line);
				Sleep(40);
				std::cout << "火力值:" << line << std::endl << std::endl;
				Sleep(40);
			}
		}
		else
		{
			aircraft fighter(tNum);
			return fighter;
		}
	}
}

aircraft::aircraft(int id)
	:Spd(0), Alt(0), name(""), WEP(0), turnRate(0), SpdMx(0),SpdUs(0),energyTransRate(0), firePower(0)
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
				SpdUs = stoi(line);
				getline(Fighters, line);
				energyTransRate = stod(line);
				getline(Fighters, line);
				firePower = stoi(line);
				Fighters.close();
				break;
			}
			else
			{
				//std::cout << "jump:" << std::endl;
				for (int i = 0; i < 7; i++)
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
		std::cout << "读取战斗机数据成功！" << std::endl;
		Sleep(500);
		return;
	}
	else
	{
		std::cout << "对应战机未能找到，已自动选择默认飞机" << std::endl;
		Sleep(500);
		aircraft temp(0);
		name = temp.name;
		WEP = temp.WEP;
		turnRate = temp.turnRate;
		SpdMx = temp.SpdMx;
		SpdUs = temp.SpdUs;
		energyTransRate = temp.energyTransRate;
		firePower = temp.firePower;
		return;
	}
}


void aircraft::statUpdate(int Alt, int Spd)
{
	this->Alt = Alt;
	this->Spd = Spd;
	if (this->Spd >= this->SpdMx)
	{
		this->Spd = this->SpdMx;
	}

	return;
}

void aircraft::operator=(aircraft x)
{
	this->name = x.name;
	this->energyTransRate = x.energyTransRate;
	this->firePower = x.firePower;
	this->SpdMx = x.SpdMx;
	this->SpdUs = x.SpdUs;
	this->turnRate = x.turnRate;
	this->WEP = x.WEP;
	return;
}


void clearScreen()
{
	std::cout << "\033[2J\033[H";
}


int randInt(int min, int max)
{
	static 	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> dist(min,max);
	return dist(gen);
}
