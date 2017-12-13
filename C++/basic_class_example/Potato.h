/*H**********************************************************************
* FILENAME :    Potato.h
*
* DESCRIPTION :
*       Class Header File
*
* NOTES :
*       Class header files need to be included in files they are used in.
* 
* AUTHOR :    Brandon Pirtle        START DATE :     8 Nov 16
*                                   EDIT  DATE :    13 Dec 17
*
*H*/

#include <string>
	using std::string;

class Potato {
	private:
		string name;
	public:
		void set_name(string new_name);
		string get_name();
};