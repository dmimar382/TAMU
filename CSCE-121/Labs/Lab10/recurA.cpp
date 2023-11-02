#include <iostream>
using namespace std;

int recurA(int, int);

int main()
{
    cout << recurA(5, 5);
    return 0;
}

int recurA(int m, int n)
{
    if (n == 0)
        return 0;
    return m + recurA(m, n - 1);
}