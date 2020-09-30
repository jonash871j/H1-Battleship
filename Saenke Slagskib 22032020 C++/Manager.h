#pragma once
#include "ControllerAI.h"
#include "ControllerUser.h"
#include <vector>

namespace Game
{
	class Manager
	{
	private:
		ControllerAI controllerAI;
		ControllerUser controllerUser;

	private:
		int mapWidth, mapHeight;
		int round = 0;

	public:
		Manager(int mapWidth, int mapHeight);

	public:
		// Used to get user to place ship on the controller map, returns false if the given coordinate is invalid
		bool UserPlaceShip(ShipType shipType, int x, int y, ShipDirection shipDirection);

		// Used to get user to attack AI controller, returns false if it's a miss
		ShipAttack UserAttack(int x, int y);

	public:
		// Used to get ai to place ship on the controller map
		void AIPlaceShip();

		// Used to get smart AI to attack user controller, returns false if it's a miss
		ShipAttack AISmartAttack();

		// Used to get dummy AI to attack user controller, returns false if it's a miss
		ShipAttack AIRandomAttack();

	public:
		bool OnWin();

	public:
		void Reset(int mapWidth, int mapHeight);
		void Reset();

	private:
		bool CheckWin(Controller* controller);
		ShipAttack Attack(ShipAttack shipAttack);

	public:
		Map GetUserMap();
		Map GetAIMap();
		Ship GetShip(ShipType shipType);
		int GetRound();
	};
}

