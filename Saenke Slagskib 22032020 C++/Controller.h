#pragma once
#include "Map.h"
#include "Ship.h"
#include "Enums.h"
#include <vector>

namespace Game
{
	class Controller
	{
		friend class ControllerAI;
		friend class ControllerUser;

	protected:
		static const int shipTypeAmount = 5;
		Map map;
		Ship ships[shipTypeAmount];

	public:
		Controller(Map map);
		Controller(int width, int height);
		Controller();

	protected:
		// Used to place ship on a map, returns false if the given coordinate is invalid
		bool PlaceShip(Ship ship, int x, int y, ShipDirection shipDirection);

		// Used to place a ship random on a map 
		void PlaceShipRandom(Ship ship);

		// Used to destroy a ship, returns false if the given coordinate is invalid
		ShipAttack DestoryShip(int x, int y);

	public: 
		Map GetMap();
		Ship GetShip(ShipType shipType);
	};
}

