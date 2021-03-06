//
// Created by Temesgen on 11/13/2019.
//

#include "skiplist.h"
#include <iostream>
#include <climits>

using namespace std;

void test04() {
    cout << "test 4 begins" << endl;
    SkipList s(5);
    for (int i = 0; i < 20; ++i) {
        int number = rand() % 100;
        s.Add(number); //valgrind
        cout << "After adding " << number << endl;
        cout << s << endl;
    }
}

void test05() {
    cout << "test 5 begins" << endl;
    SkipList s(5);
    for (int i = 0; i < 20; ++i) {
        int number = rand() % 100;
        s.Add(number);
        cout << "After adding " << number << endl;
        cout << s << endl;

        s.Remove(number);

        cout << "After removing " << number << endl;
        cout << s << endl;
    }


}


int main(){
    //tests:
    //adding to empty list, populated list, duplicates, adding at every level
    test04();
    //tests:
    //removing number that exists only on level 1, all the way to level "depth"
    test05();

    SkipList tester(4);
    cout << tester << endl; //tests printing "empty" list (just guards)

    tester.Add(4);
    cout << "After adding " << 4 << endl;
    cout << tester << endl;

    tester.Add(4); //tests for adding duplicates
    cout << "After adding duplicate of " << 4 << endl;
    cout << tester << endl;

    tester.Remove(4); //test for removing last item
    cout << "After removing " << 4 << endl;
    cout << tester << endl;

    tester.Remove(4); //should return notification output
    cout << "After removing from empty list " << endl;
    cout << tester << endl;

    tester.Add(INT_MAX); //test edgecases
    tester.Add(INT_MIN);
    cout << tester << endl;
}
