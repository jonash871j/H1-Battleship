namespace Game.Core
{
	abstract class Controller
	{
		private System.Random random = new System.Random();
		protected Map map;
		protected Ship[] ships;
		protected int shipTypeAmount = 5;

		public Map Map
		{
			get { return map; }
			protected set { map = value; }
		}

		public Controller(Map map)
		{
			Map = map;
			ships = new Ship[shipTypeAmount];
			ships[(int)ShipType.ShipCarrier] = new Ship("Carrier", 3, (int)Field.H_ShipCarrier, (int)Field.V_ShipCarrier);
			ships[(int)ShipType.ShipBattle] = new Ship("Battleship", 3, (int)Field.H_ShipBattle, (int)Field.V_ShipBattle);
			ships[(int)ShipType.ShipDestroyer] = new Ship("Destroyer", 2, (int)Field.H_ShipDestroyer, (int)Field.V_ShipDestroyer);
			ships[(int)ShipType.ShipSubmarine] = new Ship("Submarine", 2, (int)Field.H_ShipSubmarine, (int)Field.V_ShipSubmarine);
			ships[(int)ShipType.ShipCruiser] = new Ship("Cruiser", 2, (int)Field.H_ShipCruiser, (int)Field.V_ShipCruiser);
		}
		public Controller(int width, int height) 
			: this(new Map(width, height, (int)Field.Water)){}
		public Controller()
			: this(10, 10){}

		/// <summary>
		/// Used to place ship on a map, returns false if the given coordinate is invalid
		/// </summary>
		public bool PlaceShip(Ship ship, int x, int y, ShipDirection shipDirection)
		{
			// Checks if the fields is water, if not return false
			for (int i = 0; i < ship.Size; i++)
			{
				if ((shipDirection == ShipDirection.Horizontal) && (map.GetFieldValue(x + i, y) != (int)Field.Water))
					return false;
				else if ((shipDirection == ShipDirection.Vertical) && (map.GetFieldValue(x, y + i) != (int)Field.Water))
					return false;
			}

			// Places ship on fields
			for (int i = 0; i < ship.Size; i++)
			{
				if (shipDirection == ShipDirection.Horizontal)
					map.SetFieldValue(x + i, y, ship.FieldValueHorizontal + i);
				else
					map.SetFieldValue(x, y + i, ship.FieldValueVertical + i);
			}
			return true;
		}

		/// <summary>
		/// Used to place a ship random on a map 
		/// </summary>
		public void PlaceShipRandom(Ship ship)
		{
			int count = 0;
			while (count < 50000)
			{
				if (PlaceShip(ship, random.Next(0, map.Width), random.Next(0, map.Height), (ShipDirection)random.Next(0, 2)))
					return;
				count++;
			}
		}

		/// <summary>
		/// Used to destroy a ship, returns false if the given coordinate is invalid
		/// </summary>
		public ShipAttack DestoryShip(int x, int y)
		{
			int fieldValue = map.GetFieldValue(x, y);
			int fieldAmount = map.GetFieldAmount(fieldValue);

			if ((fieldValue == -1) || (fieldValue == (int)Field.Hit) || (fieldValue == (int)Field.Miss))
				return ShipAttack.Invalid;

			if (fieldValue == 0)
			{
				map.SetFieldValue(x, y, (int)Field.Miss);
				return ShipAttack.Miss;
			}
			else
				map.SetFieldValue(x, y, (int)Field.Hit);

			if (fieldAmount == 1)
				return ShipAttack.Sank;


			return ShipAttack.Hit;
		}

		//public Ship GetShip(ShipType shipType)
		//{
		//	return ships[(int)shipType];
		//}
	}
}