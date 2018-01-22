using System;
namescape types {
	class Program {
		static void Main(string[] args) {
			int? a = null;
			int b = a ?? -99;
			// the ?? operator picks -99 if null
			System.Console.WriteLine("This is null. {0}", b);
			a = 23; // no longer null
			b = a ?? -99;
			System.Console.WriteLine("This is not null. {0}", b);

			var c = 3; // the type is automatically inferred by compiler
			var d = new { id = 21, name = "Tito" };
			System.Console.WriteLine("c={0}, d.id={1}, d.name={2}",
				c, d.id, d.name);
		}
	}
}