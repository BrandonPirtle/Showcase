/*H**********************************************************************
* FILENAME :    Potato.cpp
*
* DESCRIPTION :
*       Class Implementation File
*
* NOTES :
*       Class implementation files need to be used when compiling
* 
* AUTHOR :    Brandon Pirtle        START DATE :     8 Nov 16
*                                   EDIT  DATE :    13 Dec 17
*
*H*/

#include "Potato.h"

void Potato::set_name(string new_name) {
	name = new_name;
};

string Potato::get_name() {
	return name;
};