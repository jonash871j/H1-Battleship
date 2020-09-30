#include "Ship.h"
using namespace Game;

Ship::Ship(std::string name, int size, int fieldValue)
	: name(name), size(size), fieldValue(fieldValue)
{
}

std::string Game::Ship::GetName()
{
	return name;
}
int Game::Ship::GetSize()
{
	return size;
}
int Game::Ship::GetFieldValue()
{
	return fieldValue;
}
