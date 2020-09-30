#include "ControllerUser.h"
using namespace Game;

ControllerUser::ControllerUser(Map map)
	: Controller(map) {}
ControllerUser::ControllerUser(int width, int height)
	: Controller(width, height) {}
ControllerUser::ControllerUser()
	: Controller() {}

bool ControllerUser::UserPlaceShip(ShipType shipType, int x, int y, ShipDirection shipDirection)
{
	if (!PlaceShip(ships[int(shipType)], x, y, shipDirection))
		return false;
	return true;
}
ShipAttack ControllerUser::UserAttack(Controller* controller, int x, int y)
{
	return controller->DestoryShip(x, y);
}