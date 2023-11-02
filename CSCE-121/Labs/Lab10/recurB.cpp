#include <iostream>
using namespace std;

int recurB(int, int);

int main()
{
    cout << recurB(5, 5);
    return 0;
}

int recurB(int m, int n)
{
    if (n == 0)
        return m;
    return 1 + recurB(m, n - 1);
}