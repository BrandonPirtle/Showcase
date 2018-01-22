using System;
namespace delegates {
	class Program {
		delegate int mydel1(int aa);
		delegate int mydel2(int aa, int bb);
		int myfunc1(int a) {
			return a * a;
		}
		int myfunc2(int a) {
			return a + a;
		}
		static void Main(string[] args) {
			Program p = new Program();
			mydel1 d1 = p.myfunc1;
			System.Console.WriteLine(d1(5));
			d1 = p.myfunc2;
			System.Console.WriteLine(d1(5));
			// lambda operator "=>": anonymous, inline, on the fly
			mydel2 d2 = (a, b) => a + b * 2;
			System.Console.WriteLine(d2(2, 3));
		}
	}
}