#include "Controller.h"
#include <time.h>
using namespace Game;

Controller::Controller(Map map)
	: map(map)
{
	srand(time(NULL));
	ships[(int)ShipType::ShipHanger] = Ship("Hanger ship", 5, int(Field::ShipHanger));
	ships[(int)ShipType::ShipBattle] = Ship("Battleship", 4, int(Field::ShipBattle));
	ships[(int)ShipType::ShipDestroyer] = Ship("Destroyer", 3, int(Field::ShipDestroyer));
	ships[(int)ShipType::ShipSubmarine] = Ship("Submarine", 3, int(Field::ShipSubmarine));
	ships[(int)ShipType::ShipCruiser] = Ship("Cruiser", 2, int(Field::ShipCruiser));
}
Controller::Controller(int width, int height) 
	: Controller(Map(width, height, (int)Field::Water)){}
Controller::Controller() : Controller(10, 10){}

bool Controller::PlaceShip(Ship ship, int x, int y, ShipDirection shipDirection)
{
	// Checks if the fields is water, if not return false
	for (int i = 0; i < ship.GetSize(); i++)
	{
		if ((shipDirection == ShipDirection::Horizontal) && (map.GetFieldValue(x + i, y) != int(Field::Water)))
			return false;
		else if ((shipDirection == ShipDirection::Vertical) && (map.GetFieldValue(x, y + i) != int(Field::Water)))
			return false;
	}

	// Places ship on fields
	for (int i = 0; i < ship.GetSize(); i++)
	{
		if (shipDirection == ShipDirection::Horizontal)
			map.SetFieldValue(x + i, y, ship.GetFieldValue());
		else
			map.SetFieldValue(x, y + i, ship.GetFieldValue());
	}
	return true;
}
void Controller::PlaceShipRandom(Ship ship)
{
	int count = 0;
	while (count < 50000)
	{
		if (PlaceShip(ship, rand() % map.GetWidth(), rand() % map.GetHeight(), ShipDirection(rand() % 2)))
			return;
		count++;
	}
}
ShipAttack Controller::DestoryShip(int x, int y)
{
	int fieldValue = map.GetFieldValue(x, y);
	int fieldAmount = map.GetFieldAmount(fieldValue);

	if ((fieldValue == -1) || (fieldValue == (int)Field::Hit) || (fieldValue == (int)Field::Miss))
		return ShipAttack::Invalid;

	if (fieldValue == 0)
	{
		map.SetFieldValue(x, y, (int)Field::Miss);
		return ShipAttack::Miss;
	}
	else
		map.SetFieldValue(x, y, (int)Field::Hit);

	if (fieldAmount == 1)
		return ShipAttack::Sank;


	return ShipAttack::Hit;
}

Map Controller::GetMap()
{
	return map;
}
Ship Controller::GetShip(ShipType shipType)
{
	return ships[(int)shipType];
}
