#pragma once
#include <string>

namespace Game
{
	class Ship
	{
	private:
		std::string name;
		int size;
		int fieldValue;

	public:
		Ship(std::string name, int size, int fieldValue);
		Ship() {};
		~Ship() {};
	
	public:
		std::string GetName();
		int GetSize();
		int GetFieldValue();
	};
}
