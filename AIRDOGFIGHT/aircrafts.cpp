//fighterinfo format：
//ID
//name
//WEP
//Turnrate 
//SpdMx
//SpdUs
//EnergyTrans
//Firepower

//cards format:
//ID
//name
//description
//SpdGet
//AltGet
//AngleTrans
//distanceGet
//type

#include"aircrafts.h"

int cardQueue[4];
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
	:Spd(0), Alt(0), name(""), WEP(0), turnRate(0), SpdMx(0),SpdUs(0),energyTransRate(0), firePower(0), stall(false)
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

//没有任何初始化的卡牌对象
card::card()
	:id(0), name("null"), description("description"), SpdGet(0), AltGet(0), AngleTrans(0), distanceGet(0), type("lev")
{}

//初始化卡牌对象
card::card(int id, std::string name, std::string description, int SpdGet, int AltGet, double AngleTrans, int distanceGet, std::string type)
	:id(id),name(name),description(description),SpdGet(SpdGet),AltGet(AltGet),AngleTrans(AngleTrans),distanceGet(distanceGet),type(type)
{}


void card::operator=(card& inp)
{
	this->id = inp.id;
	this->name = inp.name;
	this->description = inp.description;
	this->SpdGet = inp.SpdGet;
	this->AltGet = inp.AltGet;
	this->AngleTrans = inp.AngleTrans;
	this->distanceGet = inp.distanceGet;
	this->type = inp.type;
	return;
}



void card::showInfo(aircraft& player)
{
	std::cout << this->name << ":  ";
	Sleep(100);
	std::cout << this->description << std::endl;
	Sleep(40);
	//----------------------------
	std::cout << "此牌作用效果如下：" << std::endl;
	Sleep(40);
	std::cout << "获取角度：" << static_cast<int>(std::floor((player.Spd > player.SpdUs) ? this->AngleTrans * player.SpdUs * player.turnRate : this->AngleTrans * player.Spd * player.turnRate)) << "      ";
	Sleep(40); 
	std::cout << "间距变化：" << this->distanceGet << std::endl;
	Sleep(40);

	if (this->type == "lev")
	{
		std::cout << "速度变化：";
		Sleep(40);
		if (player.Spd > player.SpdUs)
		{
			std::cout << static_cast<int>(std::floor(player.WEP * player.energyTransRate * 0.5 + this->SpdGet)) << "    ";
		}
		else std::cout << static_cast<int>(std::floor(player.WEP * player.energyTransRate + this->SpdGet)) << "    ";
		std::cout << "高度变化：" << this->AltGet << std::endl;
		Sleep(40);
		std::cout << "平飞系卡牌：不额外产生高度，产能部分提供速度" << std::endl;
	}

	else if (this->type == "pos")
	{
		std::cout << "速度变化：";
		Sleep(40);
		if (player.Spd > player.SpdUs)
		{
			std::cout << player.Spd - player.SpdUs << "    ";
		}
		else std::cout << static_cast<int>(std::floor(this->SpdGet))<<"    ";
		std::cout << "高度变化：";
		Sleep(40);
		if (player.Spd > player.SpdUs)
		{
			std::cout << static_cast<int>(std::floor(player.SpdUs - player.Spd + player.WEP * 0.5 + this->AltGet)) << std::endl;
		}
		else std::cout << static_cast<int>(std::floor(player.WEP + this->AltGet)) << std::endl;
		std::cout << "上升系卡牌：牺牲速度获取高度，试着获取更有利位置" << std::endl;
	}

	else
	{
		std::cout << "速度变化：";
		Sleep(40);
		if (player.Spd > player.SpdUs)
		{
			std::cout << static_cast<int>(std::floor(this->SpdGet - this->AltGet * player.energyTransRate + player.WEP * 0.5 * player.energyTransRate)) << "    ";
		}
		else std::cout << static_cast<int>(std::floor(this->SpdGet - this->AltGet * player.energyTransRate + player.WEP * player.energyTransRate)) << "    ";

		std::cout << "高度变化：";
		Sleep(40);
		std::cout << static_cast<int>(std::floor(this->AltGet)) << std::endl;
		std::cout << "下降系卡牌：降低能量，依靠更高速度获取潜在优势" << std::endl;
	}


}

void card::cardUse(aircraft& player, int& angle, int& distance, int playerID)
{
	//卡牌的作用效果（逻辑）

	angle += static_cast<int>(std::floor((player.Spd > player.SpdUs) ? this->AngleTrans * player.SpdUs * player.turnRate : this->AngleTrans * player.Spd * player.turnRate)) * pow(-1, playerID);
	if (this->type == "lev")
	{
		player.Alt += (this->AltGet);
		player.Spd += static_cast<int>(std::floor((player.Spd > player.SpdUs)? player.WEP * player.energyTransRate * 0.5 + this->SpdGet : player.WEP * player.energyTransRate + this->SpdGet));
	}
	else if (this->type == "pos")
	{
		player.Alt += static_cast<int>(std::floor((player.Spd > player.SpdUs) ? player.SpdUs - player.Spd + player.WEP * 0.5 + this->AltGet : player.WEP + this->AltGet));
		player.Spd += static_cast<int>(std::floor((player.Spd > player.SpdUs) ? player.Spd - player.SpdUs : this->SpdGet));
	}
	else
	{
		player.Alt += static_cast<int>(std::floor(this->AltGet));
		player.Spd += static_cast<int>(std::floor((player.Spd > player.SpdUs) ? this->SpdGet - this->AltGet * player.energyTransRate + player.WEP * 0.5 * player.energyTransRate : this->SpdGet - this->AltGet * player.energyTransRate + player.WEP * player.energyTransRate));
	}

	distance += this->distanceGet;

	if (angle > 18) angle = 18;
	else if (angle < 0) angle = 0;
}