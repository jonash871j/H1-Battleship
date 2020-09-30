#include "ControllerAI.h"
using namespace Game;

ControllerAI::ControllerAI(Map map)
	: Controller(map){}
ControllerAI::ControllerAI(int width, int height)
	: Controller(width, height) {}
ControllerAI::ControllerAI()
	: Controller() {}

void ControllerAI::PlaceShip()
{
	map.SetAllFieldValues((int)Field::Water);
	for (int i = 0; i < shipTypeAmount; i++)
		PlaceShipRandom(ships[i]);
}
ShipAttack ControllerAI::SmartAttack(Controller* controller)
{
	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
	// AI algorithm for battleship game									//
	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

	// Checks if all cells has been searched, then return invalid
	if (!CheckAnyLeftCells(controller))
		return ShipAttack::Invalid;

	if (aIAttackMessage == ShipAttack::Sank)
	{
		aIRandomSearch = true;
		aIShipDirectionFound = false;
	}

	while (1)
	{
		// Picks random coordinate
		if (aIRandomSearch == true)
			RandomizePosition(controller);
		else
		{
			// Trys to find the direction the ship is placed
			if (aIShipDirectionFound == false)
			{
				// Picks between horizontal or vertical 
				int pick = rand() % 2;
				if (pick == 0)
				{
					int y = rand() % 2;
					if (y == 0) y = -1;
					if (y == 1) y = 1;
					aIShipLastDirection = y;

					aIX = aIHitStartX;
					aIY = aIHitStartY + y;

					// Checks if coordinate is inside the map
					if ((aIY < 0) || (aIY >= controller->GetMap().GetHeight()))
						continue;
				}
				else
				{
					int x = rand() % 2;
					if (x == 0) x = -1;
					if (x == 1) x = 1;
					aIShipLastDirection = x;

					aIX = aIHitStartX + x;
					aIY = aIHitStartY;

					// Checks if coordinate is inside the map
					if ((aIX < 0) || (aIX >= controller->GetMap().GetWidth()))
						continue;
				}
			}
			else
			{
				if (aIShipDirection == ShipDirection::Horizontal)
				{
					aIX = aIHitPreX + aIShipLastDirection;
					aIY = aIHitPreY;

					if ((aIX <= 0) || (aIX >= controller->GetMap().GetWidth() - 1) || (controller->GetMap().GetFieldValue(aIX, aIY) == (int)Field::Miss))
					{
						Toggle(&aIShipLastDirection);
						aIX = aIHitStartX + aIShipLastDirection;
					}
				}
				else
				{
					aIX = aIHitPreX;
					aIY = aIHitPreY + aIShipLastDirection;

					if ((aIY <= 0) || (aIY >= controller->GetMap().GetHeight() - 1) || (controller->GetMap().GetFieldValue(aIX, aIY) == (int)Field::Miss))
					{
						Toggle(&aIShipLastDirection);
						aIY = aIHitStartY + aIShipLastDirection;
					}
				}
			}
		}

		// Checking if coordinate is known
		if (!CheckCoordinateExist(controller))
			break;
	}

	// Store the coordinate
	aIHitPreX = aIX;
	aIHitPreY = aIY;

	// When random search is disabled and there was discovered a ship cell
	if ((aIRandomSearch == false) && ((controller->GetMap().GetFieldValue(aIX, aIY) != (int)Field::Water)))
	{
		// Here is the ship direction determined when there is still not found a direction
		if (aIShipDirectionFound == false)
		{
			// Checks if the previews x cell is not at the starting ship coordinate then it's pointing horizontal else it must be pointing vertical
			if (aIHitPreX != aIHitStartX)
				aIShipDirection = ShipDirection::Horizontal;
			else
				aIShipDirection = ShipDirection::Vertical;

			aIShipDirectionFound = true;
		}
	}

	// When seaching randomly and there was discovered a ship cell, then disable random search and store the coordinate as start
	if ((aIRandomSearch == true) && (controller->GetMap().GetFieldValue(aIX, aIY) != (int)Field::Water))
	{
		aIHitStartX = aIX;
		aIHitStartY = aIY;
		aIRandomSearch = false;
	}

	// Stores the coordinate
	SaveCoordinate(controller);

	// Attack cell and return the attack state
	aIAttackMessage = controller->DestoryShip(aIX, aIY);
	return aIAttackMessage;
}
ShipAttack ControllerAI::RandomAttack(Controller* controller)
{
	// Checks if all cells has been searched, then return invalid
	if (!CheckAnyLeftCells(controller))
		return ShipAttack::Invalid;

	while (1)
	{
		// Picks random coordinate
		RandomizePosition(controller);

		// Checking if coordinate is known
		if (!CheckCoordinateExist(controller))
			break;
	}
	// Stores the coordinate
	SaveCoordinate(controller);

	// Attack cell and return the attack state
	aIAttackMessage = controller->DestoryShip(aIX, aIY);
	return aIAttackMessage;
}

bool ControllerAI::CheckAnyLeftCells(Controller* controller)
{
	if (aIBannedIndex.size() > controller->GetMap().GetWidth()* controller->GetMap().GetHeight())
		return false;
	return true;
}
bool ControllerAI::CheckCoordinateExist(Controller* controller)
{
	// Checking if coordinate is known
	for (int i = 0; i < aIBannedIndex.size(); i++)
	{
		if (aIBannedIndex[i] == (aIY * controller->GetMap().GetWidth() + aIX))
			return true;
	}
	return false;
}
void ControllerAI::RandomizePosition(Controller* controller)
{
	aIX = rand() % controller->GetMap().GetWidth();
	aIY = rand() % controller->GetMap().GetHeight();
}
void ControllerAI::SaveCoordinate(Controller* controller)
{
	aIBannedIndex.push_back(aIY * controller->GetMap().GetWidth() + aIX);
}

void ControllerAI::Toggle(int* lastDirection)
{
	if (*lastDirection == -1)
		*lastDirection = 1;
	else
		*lastDirection = -1;
}
