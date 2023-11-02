#include <iostream>
#include <stdexcept>
#include "DynArrayStack.h"

using namespace std;

int main()
try {
    DynArrayStack das{};
    return 0;
}
catch(runtime_error& e){
    cerr << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "exception\n";
    return 2;
}