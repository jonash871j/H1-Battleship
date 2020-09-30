#pragma once
#include "Controller.h"

namespace Game
{
	class ControllerAI : public Controller
	{
	private:
		std::vector<int> aIBannedIndex;
		ShipDirection aIShipDirection;
		ShipAttack aIAttackMessage = ShipAttack::Invalid;
		bool aIRandomSearch = true;
		bool aIShipDirectionFound = false;
		int aIShipLastDirection = false;
		int aIX = 0, aIY = 0;
		int aIHitStartX, aIHitStartY;
		int aIHitPreX, aIHitPreY;

	public:
		ControllerAI(Map map);
		ControllerAI(int width, int height);
		ControllerAI();

	public:
		// Used to get AI placeing the ships on the AI map
		void PlaceShip();

		// Gets smart AI to attack a controller
		ShipAttack SmartAttack(Controller* controller);

		// Gets dummy AI to attack a controller
		ShipAttack RandomAttack(Controller* controller);

	private:
		// Checks if all cells has been searched, then return false
		bool CheckAnyLeftCells(Controller* controller);
		bool CheckCoordinateExist(Controller* controller);
	
	private:
		// Picks random coordinate
		void RandomizePosition(Controller* controller);
		void SaveCoordinate(Controller* controller);
		void Toggle(int* lastDirection);
	};
}

