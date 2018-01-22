using System;
namespace iterator {
	public class MyBooks : System.Collections.IEnumerable {
		string[] books = { "A Game of Thrones", "A Clash of Kings",
			"A Storm of Swords", "A Feast for Crows", "A Dance with Dragons" };
		public System.Collections.IEnumerator GetEnumerator() {
			for (int i = 0; i < books.Length; i++) {
				yield return books[i];
			}
		}
	}
	class Program {
		static void Main(string[] args) {
			MyBooks b = new MyBooks();
			foreach (string s in b) {
				System.Console.Write(s + "\n");
			}
		}
	}
}