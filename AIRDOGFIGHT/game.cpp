
#include "game.h"

void start()
{
	game mainGame;
	mainGame.ModeSelection();
	if (mainGame.AIplayer == 1)
	{
		std::cout << "对战自动敌人功能敬请期待！" << std::endl;
		return;
	}
	else
	{
		mainGame.fighterSelection();
		clearScreen();
		mainGame.showStats();
		std::cout << "准备……" << std::endl;
		Sleep(300);
		std::cout << "战斗" << std::endl;
		Sleep(300);
		std::cout << "开始！" << std::endl;
	}
}


game::game()
	:AIplayer(0),distance(8),angle(9)
{}

void game::ModeSelection()
{
	std::string choise;
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
	std::cout << "为玩家1选择战斗机！" << std::endl;
	Sleep(100);
	player[0] = selectAircraft();
	player[0].statUpdate(20, player[0].SpdUs);
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
		switch (static_cast<int>(std::floor(max(angle,18-angle)*2/min(angle,18-angle))))
		{
		case 2:
			return false;
			break;
		case 3:
			return (attacking(player[fighter].firePower, distance, dice, attackWinrate_list1));
			break;
		case 4:
			return (attacking(player[fighter].firePower, distance, dice, attackWinrate_list2));
			break;
		case 5:
			return (attacking(player[fighter].firePower, distance, dice, attackWinrate_list2));
			break;
		default:
			return (attacking(player[fighter].firePower, distance, dice, attackWinrate_list3));
		}
	}
}

void game::showStats()
{
	std::cout << "当前状况：——————" << std::endl;
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
	std::cout << std::endl;

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
			return true;
		}
		else
		{
			std::cout << "未能造成杀伤！" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "未能抓到角度！" << std::endl;
		return false;
	}
}