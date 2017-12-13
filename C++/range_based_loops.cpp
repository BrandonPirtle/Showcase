/*H**********************************************************************
* FILENAME :    range_based_loops.cpp
*
* DESCRIPTION :
*       Exhibits fuctionality of c++11 for loops
*
* NOTES :
*       Compiled using: g++ -std=c++11 range_based_loops.cpp -o range_based_loops
* 
* AUTHOR :    Brandon Pirtle        START DATE :    21 Mar 14
*                                   EDIT  DATE :    13 Dec 17
*
*H*/

#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;
#include <string>
    using std::string;

int main(){

    int     array1[3] = {    7,     24,     42};
    double  array2[3] = {7.777, 24.777, 42.777};
    char    array3[3] = {  'Y',    'a',    'y'};
    bool    array4[3] = { true,  false,   true};
    string  array5[3] = { "So", "much", "wow!"};

    cout << "Interger array:" << endl;
    for (int value : array1)
        cout << value << " ";
    cout << endl;

    cout << "Double array:" << endl;
    for (double value : array2)
        cout << value << " ";
    cout << endl;

    cout << "Character array:" << endl;
    for (char value : array3)
        cout << value << " ";
    cout << endl;

    cout << "Boolean array:" << endl;
    for (bool value : array4)
        cout << value << " ";
    cout << endl;

    cout << "String array:" << endl;
    for (string value : array5)
        cout << value << " ";
    cout << endl;

    cout << endl << "Displaying arrays with use of auto typing:" << endl;

    cout << "Interger array:" << endl;
    for (auto value : array1)
        cout << value << " ";
    cout << endl;

    cout << "Double array:" << endl;
    for (auto value : array2)
        cout << value << " ";
    cout << endl;

    cout << "Character array:" << endl;
    for (auto value : array3)
        cout << value << " ";
    cout << endl;

    cout << "Boolean array:" << endl;
    for (auto value : array4)
        cout << value << " ";
    cout << endl;

    cout << "String array:" << endl;
    for (auto value : array5)
        cout << value << " ";
    cout << endl;

    return 0;
}