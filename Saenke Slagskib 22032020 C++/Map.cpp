#include "Map.h"
using namespace Game;

Map::Map(int width, int height, int initFieldValue)
	: width(width), height(height)
{
	mapArray = std::make_unique<int[]>(width * height);
	SetAllFieldValues(initFieldValue);
}

void Map::SetFieldValue(int x, int y, int fieldValue)
{
	if ((x < 0) || (x >= width) || (y < 0) || (y >= width))
		return;

	mapArray[y * width + x] = fieldValue;
}
void Map::SetAllFieldValues(int fieldValue)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			mapArray[y * width + x] = fieldValue;
		}
	}
}
void Map::SetFieldValues(int fieldValues, int replaceFieldValues)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (mapArray[y * width + x] == fieldValues)
				mapArray[y * width + x] = replaceFieldValues;
		}
	}
}
void Map::SetMapDimensions(int width, int height)
{
	mapArray = std::make_unique<int[]>(width * height);
}

int Map::GetFieldAmount(int fieldValue)
{
	int amount = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (mapArray[y * width + x] == fieldValue)
				amount++;
		}
	}
	return amount;
}
int Map::GetFieldValue(int x, int y)
{
	if ((x < 0) || (x >= width) || (y < 0) || (y >= width))
		return -1;

	return mapArray[y * width + x];
}
int Map::GetWidth()
{
	return width;
}
int Map::GetHeight()
{
	return height;
}
