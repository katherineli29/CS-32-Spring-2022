#include "NewSequence.h"
#include <cassert>
#include <iostream>

using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1 && s.find(42) == 0);
    assert(s.insert(6) == 1);
    assert(s.size() == 2);

    Sequence s2;
    assert(s2.insert(31) == 0);
    assert(s2.insert(5) == 1);
    assert(s2.insert(7) == 1);
    assert(s2.size() == 3 && s2.find(5) == 2);
    assert(s2.insert(1) == 3);
    assert(s2.erase(3));

    s2.swap(s);
    assert(s2.size() == 2);
    assert(s.size() == 3);

    cout << "Passed all tests" << endl;

    return 0;
}