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
#include<stdexcept>

int attackWinrate_list1[8] = { 7,6,5,3,4,5,6,7 };
int attackWinrate_list2[8] = { 7,5,4,3,3,4,5,6 };
int attackWinrate_list3[8] = { 7,5,3,2,4,5,6,7 };


aircraft selectAircraft()
{
	std::string input;
	while (1)
	{
		std::cout << "请选择战机编号（现版本编号范围：0~2，输入-1拉出战斗机列表）：";
		input = readToken();

		int tNum;
		try
		{
			size_t parsed = 0;
			tNum = std::stoi(input, &parsed);
			if (parsed != input.size())
			{
				throw std::invalid_argument("含有非数字字符");
			}
		}
		catch (const std::exception&)
		{
			std::cout << "输入错误，请输入-1或0~2之间的整数。" << std::endl;
			continue;
		}

		if (tNum == -1)
		{
			std::ifstream Fighters(dataFilePath("Fighters.txt"));
			if (!Fighters.is_open())
			{
				throw std::runtime_error("无法打开 Fighters.txt");
			}
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
		else if (tNum >= 0 && tNum <= 2)
		{
			aircraft fighter(tNum);
			return fighter;
		}
		else
		{
			std::cout << "编号超出范围，请输入-1或0~2。" << std::endl;
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
		Fighters.open(dataFilePath("Fighters.txt"), std::ios::in);
		if (!Fighters.is_open())
		{
			throw std::runtime_error("无法打开 Fighters.txt");
		}

		while (getline(Fighters, line))
		{
			if (line.empty())
			{
				continue;
			}
			if (stoi(line) == id)
			{
				success = 1;
				auto readValue = [&Fighters](std::string& value)
				{
					if (!getline(Fighters, value))
					{
						throw std::runtime_error("Fighters.txt 数据不完整");
					}
				};
				readValue(line);
				name = line;
				readValue(line);
				WEP = stoi(line);
				readValue(line);
				turnRate = stod(line);
				readValue(line);
				SpdMx = stoi(line);
				readValue(line);
				SpdUs = stoi(line);
				readValue(line);
				energyTransRate = stod(line);
				readValue(line);
				firePower = stoi(line);
				Fighters.close();
				break;
			}
			else
			{
				//std::cout << "jump:" << std::endl;
				for (int i = 0; i < 7; i++)
				{
					if (!getline(Fighters, line))
					{
						throw std::runtime_error("Fighters.txt 数据不完整");
					}
				}
				continue;
			}
		}


	}
	catch (const std::exception& err)
	{
		std::cerr << "错误：未能读取战斗机数据（" << err.what() << "）。" << std::endl;
		Sleep(3000);
		exit(EXIT_FAILURE);
	}
	if (success)
	{
		//std::cout << "读取战斗机数据成功！" << std::endl;
		//Sleep(200);
		return;
	}
	else
	{
		std::cout << "对应战机未能找到，已自动选择默认飞机" << std::endl;
		Sleep(200);
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

std::string readToken()
{
	std::string value;
	if (!(std::cin >> value))
	{
		throw std::runtime_error("标准输入已关闭或不可用");
	}
	return value;
}

std::filesystem::path dataFilePath(const std::filesystem::path& fileName)
{
	const auto workingDirectoryFile = std::filesystem::current_path() / fileName;
	if (std::filesystem::exists(workingDirectoryFile))
	{
		return workingDirectoryFile;
	}

	wchar_t executablePath[MAX_PATH];
	const DWORD pathLength = GetModuleFileNameW(nullptr, executablePath, MAX_PATH);
	if (pathLength != 0 && pathLength < MAX_PATH)
	{
		const auto executableDirectoryFile =
			std::filesystem::path(executablePath).parent_path() / fileName;
		if (std::filesystem::exists(executableDirectoryFile))
		{
			return executableDirectoryFile;
		}
	}

	throw std::runtime_error("找不到数据文件：" + fileName.string());
}

//没有任何初始化的卡牌对象
card::card()
	:id(0), name("null"), description("description"), SpdGet(0), AltGet(0), AngleTrans(0), distanceGet(0), type("lev")
{}

//初始化卡牌对象
card::card(int id, std::string name, std::string description, int SpdGet, int AltGet, double AngleTrans, int distanceGet, std::string type)
	:id(id),name(name),description(description),SpdGet(SpdGet),AltGet(AltGet),AngleTrans(AngleTrans),distanceGet(distanceGet),type(type)
{}


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
			std::cout << player.SpdUs - player.Spd << "    ";
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
		player.Spd += static_cast<int>(std::floor((player.Spd > player.SpdUs) ? player.SpdUs - player.Spd : this->SpdGet));
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
