#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

void resizeIntArray(int*&, int&);
void displayIntArray (int[], int);

int main()
try
{
    int array_sz = 3;
    int *array = new int[array_sz];
    for (int i = 0; i < array_sz; ++i)
        array[i] = i;
    displayIntArray(array, array_sz);
    resizeIntArray(array, array_sz);
    displayIntArray(array, array_sz);
    delete [] array;

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

void resizeIntArray(int *&ref_old_array, int &ref_array_sz)
{
    /* Four steps are required to resize an array */
    int new_sz = ref_array_sz * 2;
    // 1. Create an entirely new array of the appropriate type and size (here, 2x the old size)
    int *new_array = new int[ref_array_sz];
    // 2. Copy the data from the old array into the new array (keeping them at the same position) -- here we are multiplying the original data by 2
    for (int i = 0; i < (ref_array_sz); ++i) {
        new_array[i] = ref_old_array[i] * 2;
    }
    // 3. Delete the old array as you don't need it anymore
    delete [] ref_old_array;
    // 4a. Update the pointer to reflect the new address
    ref_old_array = new_array;
    // 4b. Update the variable containing the array's size
    ref_array_sz = new_sz;
}

void displayIntArray (int array[], int array_sz)
{
    for (int i = array_sz - 1; i >= 0; --i) {
        cout << "      |----------------------|   " << endl;
        cout << setw(6) << i << "|" << setw(22) << array[i] << "|" << endl;
    }
    if (array_sz > 0)
        cout << "      |----------------------|   " << endl << endl;
    else
        cout << endl << "The Array Is Empty" << endl << endl;
}