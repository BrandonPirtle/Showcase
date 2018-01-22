using System;
namespace attributes {
	[Obsolete("Do not use this")]
	public class Myclass {
		public void disp() {
			System.Console.WriteLine("...");
		}
	}
	class Program {
		[STAThread] // this is thread safe for COM
		static void Main(string[] args) {
			Myclass mc = new Myclass();
			mc.disp();
		}
	}
}