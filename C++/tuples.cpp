/*H**********************************************************************
* FILENAME :    tuples.cpp
*
* DESCRIPTION :
*       Exhibits fuctionality of c++11 tuples
*
* NOTES :
*       Compiled using: g++ -std=c++11 tuples.cpp -o tuples
* 
* AUTHOR :    Brandon Pirtle        START DATE :    11 Apr 14
*                                   EDIT  DATE :    13 Dec 17
*
*H*/

#include <tuple>
    using std::tuple;
    using std::get;
    using std::tie;
    using std::make_tuple;
    using std::swap;
    using std::tuple_size;
    using std::tuple_element;
    using std::tuple_cat;
#include <string>
    using std::string;
#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;

int main(int argc, char *argv[]) {

    tuple<int, double, char, bool, string> t1(7, 9000.1, 'X', true, "#YOLO");

    cout << "t1 contains (called by std::get()):\n"
         << "t1<0>: " << get<0>(t1) << endl
         << "t1<1>: " << get<1>(t1) << endl
         << "t1<2>: " << get<2>(t1) << endl
         << "t1<3>: " << get<3>(t1) << endl
         << "t1<4>: " << get<4>(t1) << endl << endl;

    int int1;
    double doub1;
    char char1;
    bool bool1;
    string str1;

    tie(int1, doub1, char1, bool1, str1) = t1;

    cout << "t1 contains (called by 'ties'):\n"
         << "t1<0>: " <<  int1 << endl
         << "t1<1>: " << doub1 << endl
         << "t1<2>: " << char1 << endl
         << "t1<3>: " << bool1 << endl
         << "t1<4>: " <<  str1 << endl << endl;

    cout << "t1 contains (called by std::get()):\n"
         << "t1<0>: " << get<0>(t1) << endl
         << "t1<1>: " << get<1>(t1) << endl
         << "t1<2>: " << get<2>(t1) << endl
         << "t1<3>: " << get<3>(t1) << endl
         << "t1<4>: " << get<4>(t1) << endl << endl;

    tuple<int, double, char, bool, string> t2(7, 9000.1, 'X',  true, "#YOLO");
    tuple<int, double, char, bool, string> t3(7, 9000.2, 'X', false, "#YOLO");

    cout << "t2 contains (called by std::get()):\n"
         << "t2<0>: " << get<0>(t2) << endl
         << "t2<1>: " << get<1>(t2) << endl
         << "t2<2>: " << get<2>(t2) << endl
         << "t2<3>: " << get<3>(t2) << endl
         << "t2<4>: " << get<4>(t2) << endl << endl;

    cout << "t3 contains (called by std::get()):\n"
         << "t3<0>: " << get<0>(t3) << endl
         << "t3<1>: " << get<1>(t3) << endl
         << "t3<2>: " << get<2>(t3) << endl
         << "t3<3>: " << get<3>(t3) << endl
         << "t3<4>: " << get<4>(t3) << endl << endl;

    cout << "The == and != operators stop when a mismatch occurs.\n"
         << "The < , > , <= , >= function similarly to lexicographical comparision.\n"
         << "For tuples, the type within the tuple must be functional with the relational\n"
         << "operator == and < , for only these two operators are used in tuple comparision.\n"
         << "(This may result in the need of operator overloading.)\n"
         << "a == b  |   a == b \n"
         << "a != b  | !(a == b)\n"
         << "a  < b  |   a  < b \n"
         << "a  > b  |   b  < a \n"
         << "a <= b  | !(b  < a)\n"
         << "a >= b  | !(a  < b)\n\n";

    cout << "Relational operators :"         << endl
         << "Is t1 == t2 ? : " << (t1 == t2) << endl
         << "Is t1 == t3 ? : " << (t1 == t3) << endl
         << "Is t1 != t2 ? : " << (t1 != t2) << endl
         << "Is t1 != t3 ? : " << (t1 != t3) << endl
         << "Is t1  < t2 ? : " << (t1  < t2) << endl
         << "Is t1  < t3 ? : " << (t1  < t3) << endl
         << "Is t1  > t2 ? : " << (t1  > t2) << endl
         << "Is t1  > t3 ? : " << (t1  > t3) << endl
         << "Is t1 <= t2 ? : " << (t1 <= t2) << endl
         << "Is t1 <= t3 ? : " << (t1 <= t3) << endl
         << "Is t1 >= t2 ? : " << (t1 >= t2) << endl
         << "Is t1 >= t3 ? : " << (t1 >= t3) << endl << endl;

    cout << "Expected results: 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0\n\n";

    cout << "Expected results stored into new tuple: t4.\n"
         << "Results received stored into new tuple: t5.\n\n";

    auto t4 = make_tuple(1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0);
    auto t5 = make_tuple(
        (t1 == t2),
        (t1 == t3),
        (t1 != t2),
        (t1 != t3),
        (t1  < t2),
        (t1  < t3),
        (t1  > t2),
        (t1  > t3),
        (t1 <= t2),
        (t1 <= t3),
        (t1 >= t2),
        (t1 >= t3)
    );

    cout << "Is t4 == t5 ? : " << (t4 == t5) << endl << endl;

    cout << "Testing tuple::swap:\n";
    t2.swap(t3);
    cout << "Swap of t2 and t3 completed...\n\n";

    cout << "t2 contains (called by std::get()):\n"
         << "t2<0>: " << get<0>(t2) << endl
         << "t2<1>: " << get<1>(t2) << endl
         << "t2<2>: " << get<2>(t2) << endl
         << "t2<3>: " << get<3>(t2) << endl
         << "t2<4>: " << get<4>(t2) << endl << endl;

    cout << "t3 contains (called by std::get()):\n"
         << "t3<0>: " << get<0>(t3) << endl
         << "t3<1>: " << get<1>(t3) << endl
         << "t3<2>: " << get<2>(t3) << endl
         << "t3<3>: " << get<3>(t3) << endl
         << "t3<4>: " << get<4>(t3) << endl << endl;

    cout << "Testing tuple::tuple_size:\n"
         << "Size of t1: " << tuple_size<decltype(t1)>::value << endl << endl;

    cout << "Testing tuple::tuple_element:\n"
         << "Declaring variable t1_1 based upon type of t1 at index 0\n"
         << "and assigning value at index 0 to t1_1...\n\n";

    tuple_element<0,decltype(t1)>::type t1_1 = get<0>(t1);

    cout << "t1_1 contains: " << t1_1 << endl << endl;

    cout << "Testing tuple::tuple_cat:\n"
         << "Declaring new tuple, t6, consisting of a concatinated\n"
         << "tuple of t1 and t2...\n\n";

    auto t6 = tuple_cat(t1, t2);

    cout << "t6 contains (called by std::get()):\n"
         << "t6<0>: " << get<0>(t6) << endl
         << "t6<1>: " << get<1>(t6) << endl
         << "t6<2>: " << get<2>(t6) << endl
         << "t6<3>: " << get<3>(t6) << endl
         << "t6<4>: " << get<4>(t6) << endl
         << "t6<5>: " << get<5>(t6) << endl
         << "t6<6>: " << get<6>(t6) << endl
         << "t6<7>: " << get<7>(t6) << endl
         << "t6<8>: " << get<8>(t6) << endl
         << "t6<9>: " << get<9>(t6) << endl << endl;

    return 0;
}