using Game.Core;

namespace Game
{
	class Manager
	{
		private ControllerAI controllerAI;
		private ControllerUser controllerUser;

		private bool[] userShipPlaced = new bool[5] { false, false, false, false, false };

		private bool readyToAttack = false;

		private int mapWidth, mapHeight;
		private int round = 0;

		public Map MapAI
		{
			get { return controllerAI.Map; }
		}
		public Map MapUser
		{
			get { return controllerUser.Map; }
		}

		public bool ReadyToAttack
		{
			get { return readyToAttack; }
			private set { readyToAttack = value; }
		}

		public int MapWidth
		{
			get { return mapWidth; }
			private set { mapWidth = value; }
		}
		public int MapHeight
		{
			get { return mapHeight; }
			private set { mapHeight = value; }
		}
		public int Round
		{
			get { return round; }
			private set { round = value; }
		}

		public Manager(int mapWidth, int mapHeight)
		{
			MapWidth = mapWidth;
			MapHeight = mapHeight;
			controllerAI = new ControllerAI(mapWidth, mapHeight);
			controllerUser = new ControllerUser(mapWidth, mapHeight);
		}

		/// <summary>
		/// Used to get user to place ship on the controller map, returns false if the given coordinate is invalid
		/// </summary>
		public bool UserPlaceShip(ShipType shipType, int x, int y, ShipDirection shipDirection)
		{
			bool placeState = false;

			if (userShipPlaced[(int)shipType] == false)
			{
				placeState = controllerUser.UserPlaceShip(shipType, x, y, shipDirection);
				if (placeState == true)
					userShipPlaced[(int)shipType] = true;
			}
			int count = 0;
			for (int i = 0; i < 5; i++)
				if (userShipPlaced[i] == true)
					count++;

			if (count == 5)
				readyToAttack = true;

			return placeState;
		}

		/// <summary>
		/// Used to get user to attack AI controller, returns false if it's a miss
		/// </summary>
		public ShipAttack UserAttack(int x, int y)
		{
			return Attack(controllerUser.UserAttack(controllerAI, x, y));
		}

		public void UserClearMap()
		{
			controllerUser.Map.SetAllFieldValues((int)Field.Water);
		}

		/// <summary>
		/// Used to get ai to place ship on the controller map
		/// </summary>
		public void AIPlaceShip()
		{
			controllerAI.PlaceShip();
		}

		/// <summary>
		///  Used to get smart AI to attack user controller, returns false if it's a miss
		/// </summary>
		public ShipAttack AISmartAttack()
		{
			return Attack(controllerAI.SmartAttack(controllerUser));
		}

		/// <summary>
		/// Used to get dummy AI to attack user controller, returns false if it's a miss
		/// </summary>
		public ShipAttack AIRandomAttack()
		{
			return Attack(controllerAI.RandomAttack(controllerUser));
		}

		public bool OnWin()
		{
			bool winAI = CheckWin(controllerAI);
			bool winUser = CheckWin(controllerUser);

			if ((winAI == true) || (winUser == true))
				return true;
			return false;
		}

		public void Reset(int mapWidth, int mapHeight)
		{
			this.mapWidth = mapWidth;
			this.mapHeight = mapHeight;
			Reset();
		}
		public void Reset()
		{
			readyToAttack = false;
			round = 0;
			controllerAI = new ControllerAI(mapWidth, mapHeight);
			controllerUser = new ControllerUser(mapWidth, mapHeight);
		}

		private bool CheckWin(Controller controller)
		{
			int count = 0;
			for (int y = 0; y < MapHeight; y++)
			{
				for (int x = 0; x < MapWidth; x++)
				{
					if ((controller.Map.GetFieldValue(x, y) >= 3))
						count++;
				}
			}

			if (count == 0)
				return true;
			return false;
		}
		private ShipAttack Attack(ShipAttack shipAttack)
		{
			if (shipAttack != ShipAttack.Invalid)
				round++;

			return shipAttack;
		}

		//public Ship GetShip(ShipType shipType)
		//{
		//	return controllerUser.GetShip(shipType);
		//}
	};
}