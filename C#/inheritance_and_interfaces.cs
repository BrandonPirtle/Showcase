using System;
namespace inheritance_and_interfaces {
	class BaseClass {
		public virtual void show() {
			System.Console.WriteLine("base class");
		}
	}
	interface Interface1 {
		void showMe();
	}
	interface Interface2 {
		void showYou();
	}
	class DerivedAndImplemented: BaseClass, Interface1, Interface2 {
		public void showMe() {
			System.Console.WriteLine("Me!");
		}
		public void showYou() {
			System.Console.WriteLine("You!");
		}
		public override void show() {
			System.Console.WriteLine("I'm in derived class");
		}
	}
	class Program {
		static void Main(string[] args) {
			DerivedAndImplemented de = new DerivedAndImplemented();
			de.show();
		}
	}
}