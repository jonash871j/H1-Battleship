namespace Game.Core
{
	class ControllerUser : Controller
	{
		public ControllerUser(Map map)
			: base(map){}
		public ControllerUser(int width, int height)
		: base(width, height) { }
		public ControllerUser()
		: base() { }

		/// <summary>
		/// Used to place ship on the controller map, returns false if the given coordinate is invalid
		/// </summary>
		public bool UserPlaceShip(ShipType shipType, int x, int y, ShipDirection shipDirection)
		{
			if (!PlaceShip(ships[(int)shipType], x, y, shipDirection))
				return false;
			return true;
		}

		/// <summary>
		/// Used to attack a controller, returns false if it's a miss
		/// </summary>
		public ShipAttack UserAttack(Controller controller, int x, int y)
		{
			return controller.DestoryShip(x, y);
		}
	};
}
