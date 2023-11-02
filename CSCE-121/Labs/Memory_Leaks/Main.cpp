#include <iostream>
#include <vector>
#include "Color.h"


using namespace std;

//***************************************************//
const int STEP_LEVEL = 8; // PLEASE BE SURE TO CHANGE STEP_LEVEL VALUE WHEN REQUESTED //
///***************************************************//

Color* ok_function(int R, int G, int B);
Color* bad_function(int R, int G, int B);
void bad_function2(int R, int G, int B, int L);

/**
* main()
*/
int main()
{
    cout << "STEP_LEVEL == 0" << endl;
    Color *a = new Color(80, 0, 0);
    Color *b = a;
    cout << "Color *a = new Color;" << endl << "Color *b = a;" << endl;
    cout << "a\t" << a << '\t' << *a << endl;
    cout << "b\t" << b << '\t' << *b << endl << endl;

    if (STEP_LEVEL >= 1) {
        cout << "STEP_LEVEL == 1" << endl;
        a = nullptr;
        cout << "a = nullptr" << endl;
        cout << "a\t" << a << '\t' << endl;
        cout << "b\t" << b << '\t' << *b << endl << endl;
    }

    if (STEP_LEVEL >= 2) {
        cout << "STEP_LEVEL == 2" << endl;
          delete b;
        cout << "delete b" << endl;
        cout << "b\t" << b << '\t' << *b << endl << endl; // VS will throw exception, comment this line after step_value 2 is passed so exception does is not raised on subsequent runs.
    }

	if (STEP_LEVEL >= 3) {
        cout << "STEP_LEVEL == 3" << endl;
        b = new Color(80, 0, 0);
        cout << "b = new Color (80, 0, 0);" << endl;
        cout << "b\t" << b << '\t' << *b << endl << endl;
    }

    if (STEP_LEVEL >= 4) {
        cout << "STEP_LEVEL == 4" << endl;
        b = nullptr;
        cout << "b = nullptr" << endl;
        cout << "b\t" << b << endl << endl;
    }

    if (STEP_LEVEL >= 5) {
        cout << "STEP_LEVEL == 5" << endl;
        // what do you think's going on?
        Color *old = nullptr;
        for (int i = 0; i < 10; i++) {
            Color *ptr = new Color(i, i, i);
            if (old != nullptr)
                cout << "old at i=" << i << ":\t" << old << '\t' << *old << endl;
            cout << "ptr at i=" << i << ":\t" << ptr << '\t' << *ptr << endl << endl;
            old = ptr;
        }
        cout << "old final : " << old << '\t' << *old << endl;
        cout << endl;
    }

    if (STEP_LEVEL >= 6) {
        cout << "STEP_LEVEL == 6" << endl;
        Color *c =  ok_function(255, 255, 0);
        cout << "c\t" << c << '\t' << *c << endl << endl;

    }
    if (STEP_LEVEL >= 7) {
         cout << "STEP_LEVEL == 7" << endl;
        Color *d = bad_function(255, 0, 255);
        cout << "bad_ret\t" << d << '\t' << *d << endl;  // does not throw an exception since it did not try to access deallocated memory, did not allocate on heap, it is on stack
       }

	if (STEP_LEVEL >= 8) {
         cout << "STEP_LEVEL == 8" << endl;
        int fori = 1000000;
		for (int i = 0; i < fori; ++i) {
			bad_function2(i*i % 255, i % 255, i*i*i % 255, fori);
		}
	}

	// uncomment on Visual Studio
	//system("pause");
}

Color* ok_function(int R, int G, int B)
{
    return new Color(R, G, B);
}

Color* bad_function(int R, int G, int B)
{
    Color color = Color(R, G, B);
    cout << "bad_\t" << &color << '\t' << color << endl;
    Color *c = &color;
    return c;
}

void bad_function2(int R, int G, int B, int L)
{
    Color *color = new Color(R, G, B);
    cout << "bad_2\t" << color << '\t' << *color << endl;
    vector<Color> * v = new vector<Color>(L);
    v = nullptr;
    delete v;
    color = nullptr;
    delete color;
}