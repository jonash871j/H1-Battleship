#include <iostream>
#include <Windows.h>
#include "Manager.h"

//#include "ControllerAI.h"
//#include "ControllerUser.h"

using namespace Game;

ShipDirection GetDirectionFromChar(char character)
{
	// Direction
	if ((character == 'H') || (character == 'h'))
		return ShipDirection::Horizontal;
	if ((character == 'V') || (character == 'v'))
		return ShipDirection::Vertical;

	return ShipDirection::Horizontal;
}
int GetColumnFromChar(char character)
{
	for (int i = 0; i < 10; i++)
	{
		if (character == i + 65)
			return i;
		if (character == i + 97)
			return i;
	}
	return 0;
}

void PrintMap(Map map, bool hideShips)
{
	std::cout << " |";
	for (int i = 0; i < map.GetWidth(); i++)
		std::cout << i << '|';
	std::cout << '\n';

	for (int y = 0; y < map.GetHeight(); y++)
	{
		std::cout << char(y + 65) << " ";
		for (int x = 0; x < map.GetWidth(); x++)
		{
			if (map.GetFieldValue(x, y) == (int)Field::Water)
				std::cout << ". ";
			else if (map.GetFieldValue(x, y) == (int)Field::Miss)
				std::cout << ", ";
			else if (map.GetFieldValue(x, y) == (int)Field::Hit)
				std::cout << "X ";
			else
			{
				if (hideShips == false)
					std::cout << map.GetFieldValue(x, y) - 1 << ' ';
				else
					std::cout << ". ";
			}
		}
		std::cout << "\n";
	}
}
void PrintAttackMessage(ShipAttack attack)
{
	switch (attack)
	{
	case ShipAttack::Invalid: std::cout << "Invalid position..."; break;
	case ShipAttack::Miss	: std::cout << "Splash...";           break;
	case ShipAttack::Hit	: std::cout << "Hit...";              break;
	case ShipAttack::Sank	: std::cout << "Sank...";             break;
	}
}

template<typename T>
void PrintUserInput(std::string text, char from, char to, T* value)
{
	std::cout  << text << ": ";
	bool isSelected = false;
	while (!isSelected)
	{
		for (char i = from; i <= to; i++)
		{
			if (GetAsyncKeyState(i) & 0x0001)
			{
				*value = i;
				isSelected = true;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
Manager game(10, 10);
//ControllerUser user;
//ControllerAI ai;
int shipType = 0;
int numberRow;
char charCol = 0;
bool beginFighting = false;

void PlaceShipState()
{
	char charDirection = 0;

	// User input
	std::cout << "\n- Place " << game.GetShip((ShipType)shipType).GetName() << '\n';
	//std::cout << "\nNumber: ", std::cin >> numberRow;
	
	PrintUserInput("Number", '0', '9', &numberRow);
	numberRow -= '0';
	std::cout << numberRow << '\n';
	PrintUserInput("Character", 'A', 'J', &charCol);
	std::cout << charCol << '\n';
	PrintUserInput("Direction H or V", 'H', 'W', &charDirection);
	std::cout << charDirection << '\n';

	if (game.UserPlaceShip((ShipType)shipType, numberRow, GetColumnFromChar(charCol), GetDirectionFromChar(charDirection)))
		shipType++;
	else
	{
		std::cout << "Failed to place " << game.GetShip((ShipType)shipType).GetName() << " at specified position..";
		Sleep(500);
	}
}
void AttackState()
{
	std::cout << "\n- Attack your enemy | ROUND  " << game.GetRound() << "\n";
	PrintUserInput("Number", '0', '9', &numberRow);
	numberRow -= '0';
	std::cout << numberRow << '\n';
	PrintUserInput("Character", 'A', 'J', &charCol);
	std::cout << charCol << '\n';
	std::cout << '\n';

	ShipAttack attackPlayer = game.UserAttack(numberRow, GetColumnFromChar(charCol));
	PrintAttackMessage(attackPlayer);

	std::cout << "\n\n";

	if (attackPlayer != ShipAttack::Invalid)
	{
		ShipAttack attackAI = game.AIRandomAttack();

		std::cout << "\n- Enemy attacking you\n";
		PrintAttackMessage(attackAI);

		std::cout << "\n\n";
		Sleep(1000);
	}
}

int main()
{
	while (1)
	{
		game.AIPlaceShip();

		while (!game.OnWin() || (shipType != 5))
		{
			//std::cout << "              xStart: " << game.aIHitStartX << '\n';
			//std::cout << "              yStart: " << game.aIHitStartY << '\n';
			//std::cout << "                xPre: " << game.aIHitPreX << '\n';
			//std::cout << "                yPre: " << game.aIHitPreY << '\n';
			//std::cout << "      aIRandomSearch: " << game.aIRandomSearch << '\n';
			//std::cout << "aIShipDirectionFound: " << game.aIShipDirectionFound << '\n';
			//std::cout << "     aIShipDirection: " << (int)game.aIShipDirection << '\n';

			//std::cout << game.aIBannedIndex.size() << "\n";
			//for (int i = 0; i < game.aIBannedIndex.size(); i++)
			//	std::cout << game.aIBannedIndex[i] << ", ";

			std::cout << "- Your ship field\n";
			PrintMap(game.GetUserMap(), false);
			std::cout << "\n- Enemy's ship field\n";
			PrintMap(game.GetAIMap(), false);


			if (shipType < 5)
				PlaceShipState();
			else
				AttackState();


			std::cout << "\n\n";
			system("cls");
		}
		std::cout << "\nThere was a winer!\n";
		system("pause");
		system("cls");
		game.Reset();
		shipType = 0;
		numberRow;
		charCol = 0;
		beginFighting = false;
	}
}