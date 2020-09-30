namespace Game.Core
{
	class Ship
	{
		private string name;
		private int size;
		private int fieldValueHorizontal;
		private int fieldValueVertical;

		public string Name
		{
			get { return name; }
			private set { name = value; }
		}
		public int Size
		{
			get { return size; }
			private set { size = value; }
		}
		public int FieldValueHorizontal
		{
			get { return fieldValueHorizontal; }
			private set { fieldValueHorizontal = value; }
		}
		public int FieldValueVertical
		{
			get { return fieldValueVertical; }
			private set { fieldValueVertical = value; }
		}

		public Ship(string name, int size, int fieldValueHorizontal, int fieldValueVertical)
		{
			Name = name;
			Size = size;
			FieldValueHorizontal = fieldValueHorizontal;
			FieldValueVertical = fieldValueVertical;
		}
	};
}