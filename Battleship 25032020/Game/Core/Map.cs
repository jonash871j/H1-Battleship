namespace Game.Core
{
	class Map
	{
		private int[,] array;
		private int width, height;

		public int Width
		{
			get { return width; }
			private set { width = value; }
		}
		public int Height
		{
			get { return height; }
			private set { height = value; }
		}
		public int[,] Array
		{
			get { return array; }
			private set { array = value; }
		}

		public Map(int width, int height, int initFieldValue)
		{
			SetMapDimensions(width, height, initFieldValue);
		}

		public void SetFieldValue(int x, int y, int fieldValue)
		{
			if ((x < 0) || (x >= width) || (y < 0) || (y >= width))
				return;
			array[y, x] = fieldValue;
		}
		public void SetAllFieldValues(int fieldValue)
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					array[y, x] = fieldValue;
				}
			}
		}
		public void SetFieldValues(int fieldValues, int replaceFieldValues)
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if (array[y, x] == fieldValues)
						array[y, x] = replaceFieldValues;
				}
			}
		}
		public void SetMapDimensions(int width, int height, int initFieldValue)
		{
			Width = width;
			Height = height;
			array = new int[height, width];
			SetAllFieldValues(initFieldValue);
		}

		public int GetFieldAmount(int fieldValue)
		{
			int amount = 0;
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if (array[y, x] == fieldValue)
						amount++;
				}
			}
			return amount;
		}
		public int GetFieldValue(int x, int y)
		{
			if ((x < 0) || (x >= width) || (y < 0) || (y >= height))
				return -1;

			return array[y, x];
		}
	};
}
