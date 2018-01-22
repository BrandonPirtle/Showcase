using System;
namespace arrays {
	class Program {
		static void Main(string[] args) {
			int[] items = new int[]{5, 19, 41, 1, 9};
			foreach (int i in items) {
				System.Console.WriteLine("{0}\n", i-1);
			}
		}
	}
}