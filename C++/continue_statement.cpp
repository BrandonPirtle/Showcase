/*H**********************************************************************
* FILENAME :    continue_statement.cpp
*
* DESCRIPTION :
*       Exhibits fuctionality of c++11 continue keyword
*
* NOTES :
*       Compiled using: g++ -std=c++11 continue_statement.cpp -o continue_statement
* 
* AUTHOR :    Brandon Pirtle        START DATE :     4 Jul 15
*                                   EDIT  DATE :    13 Dec 17
*
*H*/

#include <iostream>
    using std::cout;
    using std::endl;

int main(){

    int i, array[6] = {1, 11, 5, 7, 2, 10};
    cout << "Displaying array:" << endl;
    for (i = 0; i < 6; i++)
        cout << array[i] << " ";
    cout << endl << "Values in array <= 5:" << endl;
    for (i = 0; i < 6; i++) {
        if (array[i] > 5) continue;
        cout << array[i] << " ";
    }

    return 0;
}