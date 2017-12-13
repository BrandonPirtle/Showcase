/*H**********************************************************************
* FILENAME :    main.cpp
*
* DESCRIPTION :
*       Exhibits basic usage of classes with separate files
*
* NOTES :
*       Compiled using: g++ main.cpp Potato.cpp -o classy_potato
* 
* AUTHOR :    Brandon Pirtle        START DATE :     8 Nov 16
*                                   EDIT  DATE :    13 Dec 17
*
*H*/

#include <iostream>
	using std::cout;
	using std::cin;
	using std::endl;

#include "Potato.h"

int main(int argc, char *argv[]) {

	Potato* papato = new Potato();
	papato->set_name("Papato");
	cout << "Hi! My name is " << papato->get_name() << "!" << endl;

	return 0;
}