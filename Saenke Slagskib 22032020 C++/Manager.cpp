#include "Manager.h"
#include <time.h>
using namespace Game;

Manager::Manager(int mapWidth, int mapHeight)
	: mapWidth(mapWidth), mapHeight(mapHeight)
{
	controllerAI = ControllerAI(mapWidth, mapHeight);
	controllerUser = ControllerUser(mapWidth, mapHeight);
}

bool Manager::UserPlaceShip(ShipType shipType, int x, int y, ShipDirection shipDirection)
{
	return controllerUser.UserPlaceShip(shipType, x, y, shipDirection);
}

ShipAttack Manager::UserAttack(int x, int y)
{
	return Attack(controllerUser.UserAttack(&controllerAI, x, y));
}

void Manager::AIPlaceShip()
{
	controllerAI.PlaceShip();
}

ShipAttack Manager::AISmartAttack()
{
	return  Attack(controllerAI.SmartAttack(&controllerUser));
}

ShipAttack Manager::AIRandomAttack()
{
	return  Attack(controllerAI.RandomAttack(&controllerUser));
}

bool Manager::OnWin()
{
	bool winAI = CheckWin(&controllerAI);
	bool winUser = CheckWin(&controllerUser);

	if ((winAI == true) || (winUser == true))
		return true;
	return false;
}

void Manager::Reset(int mapWidth, int mapHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	Reset();
}

void Manager::Reset()
{
	round = 0;
	controllerAI = ControllerAI(mapWidth, mapHeight);
	controllerUser = ControllerUser(mapWidth, mapHeight);
}

bool Manager::CheckWin(Controller* controller)
{
	int count = 0;
	for (int y = 0; y < controller->GetMap().GetHeight(); y++)
		for (int x = 0; x < controller->GetMap().GetWidth(); x++)
			if ((controller->GetMap().GetFieldValue(x, y) >= 3))
				count++;

	if (count == 0)
		return true;
	return false;
}

ShipAttack Manager::Attack(ShipAttack shipAttack)
{
	if (shipAttack != ShipAttack::Invalid)
		round++;

	return shipAttack;
}

Map Manager::GetUserMap()
{
	return controllerUser.GetMap();
}

Map Manager::GetAIMap()
{
	return controllerAI.GetMap();
}

Ship Manager::GetShip(ShipType shipType)
{
	return controllerUser.GetShip(shipType);
}

int Manager::GetRound()
{
	return round;
}
