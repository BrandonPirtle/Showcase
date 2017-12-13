/*H**********************************************************************
* FILENAME :    override_final.cpp
*
* DESCRIPTION :
*       Exhibits fuctionality of c++11 class keywords override and final
*
* NOTES :
*       !!!!! This file does not compile as is.
*             This is meant to exhibit different ways of overloading methods.
*             To compile correctly, comment out needed class definitions for
*                 the wanted class definitions to comply together. !!!!!
*       Compiled using: g++ -std=c++11 override_final.cpp -o override_final
* 
* AUTHOR :    Brandon Pirtle        START DATE :    4 Jul 15
*                                   EDIT  DATE :   13 Dec 17
*
*H*/

#include <iostream>
    using std::cout;

/* BASE CLASS */
class Base {
    public:
        virtual void foo(int number) {
            cout << "Base::foo checking in.\n";
        }
};

/* DEFAULT DERIVED 1 CLASS */
class Derived1 : public Base {
    public:
        virtual void foo(int number) override {
            cout << "Derived1::foo checking in.\n";
        }
};

/* DERIVED 1 USING OVERRIDE WHEN OVERLOADING */
class Derived1 : public Base {
    public:
        virtual void foo(double number) override {
            cout << "Derived1::foo checking in.\n";
        }
};

/* DERIVED 1 OVERLOADING */
class Derived1 : public Base {
    public:
        virtual void foo(double number) {
            cout << "Derived1::foo checking in.\n";
        }
};

/* DERIVED 1 OVERRIDING AND SETTING AS FINAL */
class Derived1 : public Base {
    public:
        virtual void foo(int number) override final {
            cout << "Derived1::foo checking in.\n";
        }
};

/* FINAL DERIVED 1 CLASS */
class Derived1 final : public Base {
    public:
        virtual void foo(int number) override {
            cout << "Derived1::foo checking in.\n";
        }
};

/* EMPTY DERIVED 2 */
class Derived2 : public Derived1 {};

/* DERIVED 2 ATTEMPTING TO OVERRIDE */
class Derived2 : public Derived1 {
    public:
        virtual void foo(int number) override {
            cout << "Derived2::foo checking in.\n";
        }
};

int main(int argc, char *argv[]) {

    Base     b1;
    Derived1 d1;
    Derived2 d2;

    b1.foo(1);
    d1.foo(2);
    d2.foo(3);

    return 0;
}