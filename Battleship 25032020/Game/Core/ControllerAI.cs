namespace Game.Core
{
	class ControllerAI : Controller
	{
		private System.Random random = new System.Random();
		private System.Collections.Generic.List<int> aIBannedIndex = new System.Collections.Generic.List<int>();
		private ShipDirection aIShipDirection;
		private ShipAttack aIAttackMessage = ShipAttack.Invalid;
		private bool aIRandomSearch = true;
		private bool aIShipDirectionFound = false;
		private int aIShipLastDirection = 0;
		private int aIX, aIY;
		private int aIHitStartX, aIHitStartY;
		private int aIHitPreX, aIHitPreY;

		public ControllerAI(Map map)
			: base(map) { }
		public ControllerAI(int width, int height)
		: base(width, height) { }
		public ControllerAI()
		: base() { }

		/// <summary>
		/// Used to get AI placeing the ships on the AI map
		/// </summary>
		public void PlaceShip()
		{
			for (int i = 0; i < shipTypeAmount; i++)
				PlaceShipRandom(ships[i]);
		}

		/// <summary>
		/// Gets smart AI to attack a controller
		/// </summary>
		public ShipAttack SmartAttack(Controller controller)
		{
			//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//
			// AI algorithm for battleship game									//
			//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-//

			// Checks if all cells has been searched, then return invalid
			if (!CheckAnyLeftCells(controller))
				return ShipAttack.Invalid;

			if (aIAttackMessage == ShipAttack.Sank)
			{
				aIRandomSearch = true;
				aIShipDirectionFound = false;
			}

			while (true)
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
						int pick = random.Next(0, 2);
						if (pick == 0)
						{
							int y = random.Next(0, 2);
							if (y == 0) y = -1;
							if (y == 1) y = 1;
							aIShipLastDirection = y;

							aIX = aIHitStartX;
							aIY = aIHitStartY + y;

							// Checks if coordinate is inside the map
							if ((aIY < 0) || (aIY >= controller.Map.Height))
								continue;
						}
						else
						{
							int x = random.Next(0, 2);
							if (x == 0) x = -1;
							if (x == 1) x = 1;
							aIShipLastDirection = x;

							aIX = aIHitStartX + x;
							aIY = aIHitStartY;

							// Checks if coordinate is inside the map
							if ((aIX < 0) || (aIX >= controller.Map.Width))
								continue;
						}
					}
					else
					{
						if (aIShipDirection == ShipDirection.Horizontal)
						{
							aIX = aIHitPreX + aIShipLastDirection;
							aIY = aIHitPreY;

							if ((aIX <= 0) || (aIX >= controller.Map.Width - 1) || (controller.Map.GetFieldValue(aIX, aIY) == (int)Field.Miss))
							{
								aIShipLastDirection = Toggle(aIShipLastDirection);
								aIX = aIHitStartX + aIShipLastDirection;
							}
						}
						else
						{
							aIX = aIHitPreX;
							aIY = aIHitPreY + aIShipLastDirection;

							if ((aIY <= 0) || (aIY >= controller.Map.Height - 1) || (controller.Map.GetFieldValue(aIX, aIY) == (int)Field.Miss))
							{
								aIShipLastDirection = Toggle(aIShipLastDirection);
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
			if ((aIRandomSearch == false) && ((controller.Map.GetFieldValue(aIX, aIY) != (int)Field.Water)))
			{
				// Here is the ship direction determined when there is still not found a direction
				if (aIShipDirectionFound == false)
				{
					// Checks if the previews x cell is not at the starting ship coordinate then it's pointing horizontal else it must be pointing vertical
					if (aIHitPreX != aIHitStartX)
						aIShipDirection = ShipDirection.Horizontal;
					else
						aIShipDirection = ShipDirection.Vertical;

					aIShipDirectionFound = true;
				}
			}

			// When seaching randomly and there was discovered a ship cell, then disable random search and store the coordinate as start
			if ((aIRandomSearch == true) && (controller.Map.GetFieldValue(aIX, aIY) != (int)Field.Water))
			{
				aIHitStartX = aIX;
				aIHitStartY = aIY;
				aIRandomSearch = false;
			}

			// Stores the coordinate
			SaveCoordinate(controller);

			// Attack cell and return the attack state
			aIAttackMessage = controller.DestoryShip(aIX, aIY);
			return aIAttackMessage;
		}

		/// <summary>
		/// Gets dummy AI to attack a controller
		/// </summary>
		public ShipAttack RandomAttack(Controller controller)
		{
			// Checks if all cells has been searched, then return invalid
			if (!CheckAnyLeftCells(controller))
				return ShipAttack.Invalid;

			while (true)
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
			aIAttackMessage = controller.DestoryShip(aIX, aIY);
			return aIAttackMessage;
		}

		// Checks if all cells has been searched, then return false
		private bool CheckAnyLeftCells(Controller controller)
		{
			if (aIBannedIndex.Count > controller.Map.Width * controller.Map.Height)
				return false;
			return true;
		}
		private bool CheckCoordinateExist(Controller controller)
		{
			// Checking if coordinate is known
			for (int i = 0; i < aIBannedIndex.Count; i++)
			{
				if (aIBannedIndex[i] == (aIY * controller.Map.Width + aIX))
					return true;
			}
			return false;
		}

		// Picks random coordinate
		private void RandomizePosition(Controller controller)
		{
			aIX = random.Next(0, controller.Map.Width);
			aIY = random.Next(0, controller.Map.Height);
		}
		private void SaveCoordinate(Controller controller)
		{
			aIBannedIndex.Add(aIY * controller.Map.Width + aIX);
		}
		private int Toggle(int lastDirection)
		{
			if (lastDirection == -1)
				return 1;
			else
				return -1;
		}
	};
}
