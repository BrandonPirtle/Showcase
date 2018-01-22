using System;
namespace properties {
	class Client1 {
		private string name;
		public string Name {
			get { return name; }
			set { name = value; }
		}
	}
	class Client2 {
		// automatically implements getters and setters
		public string Name { get; set; }
	}
	class Program {
		static void Main(string[] args) {
			Client1 c1 = new Client1();
			c.Name = "Celia";
			System.Console.WriteLine(c.Name);

			Client2 c2 = new Client2();
			c.Name = "Cruz";
			System.Console.WriteLine(c.Name);
		}
	}
}