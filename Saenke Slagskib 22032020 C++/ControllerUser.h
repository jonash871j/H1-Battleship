#pragma once
#include "Controller.h"

namespace Game
{
	class ControllerUser : public Controller
	{
	public:
		ControllerUser(Map map);
		ControllerUser(int width, int height);
		ControllerUser();

	public:
		// Used to place ship on the controller map, returns false if the given coordinate is invalid
		bool UserPlaceShip(ShipType shipType, int x, int y, ShipDirection shipDirection);

		// Used to attack a controller, returns false if it's a miss
		ShipAttack UserAttack(Controller* controller, int x, int y);
	};
}
