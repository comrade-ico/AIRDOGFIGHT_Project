#define RELANGLE min(angle,18-angle) != 0? static_cast<int>(std::floor(max(angle,18-angle)*2/min(angle,18-angle))) : 18
#define DISTANCE (distance + 0.5 * static_cast<int>(std::floor(abs(player[0].Alt - player[1].Alt))))
#include "game.h"

void start()
{
	game mainGame;
	mainGame.ModeSelection();
	bool turn = false;
	std::string choice0;
	std::string choice1;
	if (mainGame.AIplayer == 1)
	{
		std::cout << "对战自动敌人功能敬请期待！" << std::endl;
		Sleep(1000);
		return;
	}
	else
	{
		mainGame.fighterSelection();
		clearScreen();

		std::cout << "准备……" << std::endl;
		Sleep(500);
		std::cout << "战斗" << std::endl;
		Sleep(500);
		std::cout << "开始！" << std::endl;
		Sleep(2000);
		std::cout << "\n\n\n" << std::endl;

		clearScreen();
		while (1)
		{
			turn = (mainGame.angle > 9) ? true : false;
			for (int i = 0; i < 2; i++)
			{
				mainGame.showStats();
				std::cout << "卡牌抽取：" << std::endl;
				mainGame.genKardQueue(static_cast<int>(turn), cardQueue);
				std::cout << "玩家" << static_cast<int>(turn) + 1 << "-输入数字1-4以选择使用的卡牌：";
				std::cin >> ((turn) ? choice1 : choice0);

				std::cout << "玩家" << static_cast<int>(turn) + 1 << "-已确认卡牌选项" <<std::endl;
				Sleep(1000);
				turn = not turn;

				clearScreen();
			}
			mainGame.turnUseCard(choice0, 0);
			mainGame.turnUseCard(choice1, 1);
			Sleep(200);
			clearScreen();
			mainGame.showStats();
			if (mainGame.enableAttack())
			{
				std::cout << "玩家" << ((mainGame.angle > 9) ? "1" : "2") << "有攻击可能,是否尝试？（Y/N）" << std::endl;
				std::cin >> choice0;
				if (choice0 == "Y" || choice0 == "y")
				{
					if (mainGame.attack((mainGame.angle > 9) ? 0 : 1, false))
					{
						std::cout << "击落敌机！" << std::endl;
						Sleep(500);
						std::cout << "游戏结束，玩家" << ((mainGame.angle > 9) ? "1" : "2") << "获胜！" << std::endl;
						Sleep(3000);
						break;
					}
				}
			}
			else if (mainGame.enableHeadon())
			{
				std::cout << "玩家" << ((mainGame.player[0].Spd > mainGame.player[1].Spd) ? "1" : (mainGame.player[0].Spd == mainGame.player[1].Spd) ? (mainGame.player[0].Alt > mainGame.player[1].Alt) ? "1" : "2" : "2") << "决定是否进入[对头](Y/N):" << std::endl;
				std::cin >> choice1;
				if (choice1 == "Y" || choice1 == "y")
				{
					std::cout << "对头开始！" << std::endl;
				}
			}
			clearScreen();
			//mainGame.endTurn();
		}

	}
}


game::game()
	:AIplayer(0),distance(8),angle(9),cardCount(0)
{
	std::ifstream cardFile("cards.txt", std::ios::in);
	std::string fetchMem;
	int id;
	std::string name;
	std::string desc;
	int SGet;
	int AGet;
	double AnTrs;
	int disGet;
	std::string type;

	try
	{
		if (!cardFile.is_open())
		{
			throw "missing file!";
		}
		while (getline(cardFile, fetchMem))
		{
			if (fetchMem != "")
			{
				id = std::stoi(fetchMem);
				getline(cardFile, fetchMem);
				name = fetchMem;
				getline(cardFile, fetchMem);
				desc = fetchMem;
				getline(cardFile, fetchMem);
				SGet = std::stoi(fetchMem);
				getline(cardFile, fetchMem);
				AGet = std::stoi(fetchMem);
				getline(cardFile, fetchMem);
				AnTrs = std::stod(fetchMem);;
				getline(cardFile, fetchMem);
				disGet = std::stoi(fetchMem);
				getline(cardFile, fetchMem);
				type = fetchMem;
				card tempC(id, name, desc, SGet, AGet, AnTrs, disGet, type);
				cards.push_back(tempC);
				cardCount += 1;
			}
			else break;
		}
		
	}
	catch (std::string err)
	{
		std::cerr << "错误：未能读取文件！（请检查文件完整性）" << std::endl;
		Sleep(3000);
		exit(EXIT_FAILURE);
	}

}

void game::ModeSelection()
{
	std::string choise;
	clearScreen();
	std::cout << "选项游戏模式：输入0-本地对战（两个玩家）；输入1-机器对战（对战自动敌人）：";
	std::cin >> choise;
	if (choise == "1")
	{
		this->AIplayer = 1;
		Sleep(200);
		std::cout << "已确认对战自动敌人！" << std::endl;
		return;
	}
	Sleep(200);
	this->AIplayer = 0;
	std::cout << "已确认本地对战！" << std::endl;
	return;
}

void game::fighterSelection()
{
	clearScreen();
	std::cout << "为玩家1选择战斗机！" << std::endl;
	Sleep(100);
	player[0] = selectAircraft();
	player[0].statUpdate(20, player[0].SpdUs);
	clearScreen();
	std::cout << "为玩家2选择战斗机！" << std::endl;
	Sleep(100);
	player[1] = selectAircraft();
	player[1].statUpdate(20, player[1].SpdUs);

}


bool game::attack(int fighter, bool headon = false)
{
	int dice = randInt(1, 6);
	if (headon)
	{
		return(dice >= player[fighter].firePower);
	}
	else
	{
		switch (RELANGLE)
		{
		case 2:
			return false;
			break;
		case 3:
			return (attacking(player[fighter].firePower, DISTANCE, dice, attackWinrate_list1));
			break;
		case 4:
			return (attacking(player[fighter].firePower, DISTANCE, dice, attackWinrate_list2));
			break;
		case 5:
			return (attacking(player[fighter].firePower, DISTANCE, dice, attackWinrate_list2));
			break;
		default:
			return (attacking(player[fighter].firePower, DISTANCE, dice, attackWinrate_list3));
		}
	}
}




void game::showStats()
{
	std::cout << "当前态势：——————" << std::endl;
	Sleep(100);
	std::cout << "玩家1：机型："<< player[0].name << "\n高度：" << player[0].Alt << "\n速度：" << player[0].Spd << "\n所持角度：";
	for (int i = 0; i < angle; i++)
	{
		Sleep(50);
		std::cout << "*";
	}
	std::cout << std::endl;
	std::cout << "玩家2：机型：" << player[1].name << "\n高度：" << player[1].Alt << "\n速度：" << player[1].Spd << "\n所持角度：";
	for (int i = 0; i < (18-angle); i++)
	{
		Sleep(50);
		std::cout << "*";
	}
	std::cout << "\n间距：" << this->distance << "\n" << std::endl;
	return;
}

bool attacking(int firepower, int distance, int dice, int* winrate)
{
	if (dice >= winrate[distance])
	{
		std::cout << "抓到角度！" << std::endl;
		Sleep(150);
		int altDice = randInt(1, 6);
		std::cout << "攻击！";
		Sleep(200);
		if (altDice >= firepower)
		{
			std::cout << "命中目标！" << std::endl;
			Sleep(200);
			return true;
		}
		else
		{
			std::cout << "未能造成杀伤！" << std::endl;
			Sleep(200);
			return false;
		}
	}
	else
	{
		std::cout << "未能抓到角度！" << std::endl;
		Sleep(500);
		return false;
	}
}

void game::genKardQueue(int fighter, int(&outQueue)[4])
{
	//抽出牌堆里不重复的4张牌
	int random = randInt(0, cardCount - 1);
	int pin = 0;
	int queue[4] = { -1,-1,-1,-1 };
	while (checkQueue(-1,queue))
	{
		if (!checkQueue(random, queue))
		{
			std::cout << pin + 1 << ":";
			cards[random].showInfo(player[fighter]);
			queue[pin] = random;
			outQueue[pin] = random;
			std::cout << std::endl;
			pin++;
			Sleep(300);
		}
		random = randInt(0, cardCount - 1);
	}
	//std::cout << "一次抽牌结束\n\n\n\n" << std::endl;
	return;
}


//检查卡牌是否已经在队列中
bool checkQueue(int inp, int queue[4])
{
	for (int i = 0; i < 4; i++)
	{
		if (inp == queue[i])
		{
			return true;
		}
	}
	return false;
}

void game::useCard(int choise, int(&outQueue)[4], int fighter)
{
	this->cards[outQueue[choise]].cardUse(this->player[fighter], this->angle, this->distance, fighter);

	std::cout << "已确认使用卡牌:" << this->cards[outQueue[choise]].name << std::endl;
	Sleep(500);
	return;
}

void game::turnUseCard(std::string choice, int id)
{
	//注意此处有差1现象
	if (choice == "1")
	{
		this->useCard(0, cardQueue, static_cast<int>(id));
	}
	else if (choice == "2")
	{
		this->useCard(1, cardQueue, static_cast<int>(id));
	}
	else if (choice == "3")
	{
		this->useCard(2, cardQueue, static_cast<int>(id));
	}
	else
	{
		this->useCard(3, cardQueue, static_cast<int>(id));
	}
}

bool game::enableAttack()
{
	return (this->distance < 8 && RELANGLE >= 3);
}

bool game::enableHeadon()
{
	return (this->distance < 8 && RELANGLE < 3);
}
