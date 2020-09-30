#pragma once

namespace Game
{
	enum class Field
	{
		Water,
		Miss,
		Hit,
		ShipHanger,
		ShipBattle,
		ShipDestroyer,
		ShipSubmarine,
		ShipCruiser,
	};
	enum class ShipType
	{
		ShipHanger,
		ShipBattle,
		ShipDestroyer,
		ShipSubmarine,
		ShipCruiser,
	};
	enum class ShipDirection
	{
		Horizontal,
		Vertical,
	};
	enum class ShipAttack
	{
		Invalid,
		Miss,
		Hit,
		Sank,
	};
}