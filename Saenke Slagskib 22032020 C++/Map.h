#pragma once
#include <memory>

namespace Game
{
	class Map
	{
	private:
		std::shared_ptr<int[]> mapArray;
		int width, height;

	public:
		Map(int width, int height, int initFieldValue);
		Map() {};
		~Map() {};

	public:
		void SetFieldValue(int x, int y, int fieldValue);
		void SetAllFieldValues(int fieldValue);
		void SetFieldValues(int fieldValues, int replaceFieldValues);
		void SetMapDimensions(int width, int height);

	public:
		// Returns -1 if field value is invalid
		int GetFieldAmount(int fieldValue);
		int GetFieldValue(int x, int y);
		int GetWidth();
		int GetHeight();
	};
}

