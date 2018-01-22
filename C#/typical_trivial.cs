using System;
namescape typical_trivial {
	class House {
		private int location;
		protected string name;
		public House() {
			name = "No Name Yet!";
		}
		// every class inherits 'object' that has ToString()
		public override string ToString() {
			string disp = "Name is " + name + ", location = "
				+ location.ToString();
			return disp;
		}
	}
	class Program {
		static void Main(string[] args) {
			House h = new House();
			for (int i = 0; i < 4; i++) {
				System.Console.WriteLine("i={0}, house says: {1}",
					i, h.ToString());
			}
		}
	}
}