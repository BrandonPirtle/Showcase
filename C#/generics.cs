using System;
namespace generics {
	class Genclass<T> {
		public void genfunc(int a, T b) {
			for (int i = 0; i < a; i++) {
				System.Console.WriteLine(b);
			}
		}
	}
	class Program {
		static void Main(string[] args) {
			Genclass<float> p = new Genclass<float>();
			p.genfunc(3, (float)5.7);
		}
	}
}