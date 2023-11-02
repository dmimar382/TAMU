#include <iostream>
#include <vector>
#include <stdexcept>
// creates two new types... don't worry about this syntax, but understand that we can make objects of type someother_error and of type val_not_found... that we can throw... and subsequently catch.
class someother_error {};
class val_not_found {};

using namespace std;

int& find_int(vector<int>&, int);

int main()
try
{
    vector<int> vint {2, 4, 6, 8};
    cout << "Enter value to find: ";
    int val;
    cin >> val;
    try {
        int& i = find_int(vint, val);
    } catch(val_not_found &e) { 
        cerr << "val_not_found" << endl; 
        return 7;
    } catch (someother_error &e) {
        cerr << "exeption: someother_error" << '\n';
}
    return 0;
} catch (runtime_error& e)
{
    cerr << e.what() << '\n';
    return 1;
} catch (...)
{
    cerr << "exception\n";
    return 2;
}

int& find_int(vector<int>& vint, int val)
{
    for (decltype(vint.size()) i = 0; i < vint.size(); ++i)
        // decltype as used in this expression essencially says that I want the base type of i to be whatever type the value returned by vint.size() is.
        if (val == vint.at(i))
            return vint.at(i);
    throw val_not_found{};
}
