using System;
namespace object_initializer {
	class Client {
		public string Name { get; set; }
	}
	class Program {
		static void Main(string[] args) {
			// object initializer
			Client c = new Client { Name = "Bobo" };
			System.Console.WriteLine(c.Name);
		}
	}
}