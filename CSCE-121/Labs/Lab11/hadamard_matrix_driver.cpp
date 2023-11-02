#include <iostream>
#include "hadamard_matrix.h"
#include <vector>

using namespace std;

int main (int argc, char *argv[])
{

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " [int]" << endl;
        return 1;
    }

    int n = str_to_int(argv[1]);

    vector<vector<bool>> result = hadamard(n);

    print(result);

    return 0;
}