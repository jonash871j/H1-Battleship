namespace Game
{
	public enum Field
	{
		Water = 0,
		Miss = 1,
		Hit = 2,
		H_ShipCarrier = 10,
		V_ShipCarrier = 15,
		H_ShipBattle = 20,
		V_ShipBattle = 25,
		H_ShipDestroyer = 30,
		V_ShipDestroyer = 35,
		H_ShipSubmarine = 40,
		V_ShipSubmarine = 45,
		H_ShipCruiser = 50,
		V_ShipCruiser = 55,
	};
	public enum ShipType
	{
		ShipCarrier,
		ShipBattle,
		ShipDestroyer,
		ShipSubmarine,
		ShipCruiser,
	};
	public enum ShipDirection
	{
		Horizontal,
		Vertical,
	};
	public enum ShipAttack
	{
		Invalid,
		Miss,
		Hit,
		Sank,
	};
}