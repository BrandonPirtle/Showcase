using System;
namespace structure {
	struct Rectangle {
		public int length, width;
		public Rectangle(int length, int width) {
			this.length = length;
			this.width = width;
		}
		public int getArea() {
			return length * width;
		}
	}
	class Program {
		static void Main(string[] args) {
			Rectangle r = new Rectangle(2, 5);
			System.Console.WriteLine("The area is: {0}", r.getArea());
		}
	}
}