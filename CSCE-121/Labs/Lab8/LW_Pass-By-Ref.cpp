// MUST COMPILE ON COMPUTE.CSE.TAMU.EDU

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                Skeleton Code : Pass By Reference Labwork                 //
//                            LW_Pass-By-Ref.cpp                            //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "/home/faculty/m/michael.nowak/shared/csce121/src/cxx-printvisual/PrintVisualV2.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                          Function Declarations                           //
//////////////////////////////////////////////////////////////////////////////
int vint_half_sum(vector<int>&);

//////////////////////////////////////////////////////////////////////////////
//                                   main                                   //
//////////////////////////////////////////////////////////////////////////////
int main ()
{
    // initialize vector<int> with v.at(0) = 2, v.at(1) = 4,
    //    v.at(2) = 6, v.at(3) = 8.
    vector<int> vint {2, 4, 6, 8};
    // print the contents vint using the instructor's library code
    cout << "contents of vint (declared in main) before " <<
         "vint_half_sum call" << endl;
    vis::print(vint);

    // calling vint_half_sum with vint provided as an actual argument
    int half_sum = vint_half_sum(vint);

    // print the contents of vint after function call to
    //   vint_half_sum with vint provided as an actual argument
    cout << endl << endl << "contents of vint (declared in main) " <<
         "after vint_half_sum call" << endl;
    vis::print(vint);

    return 0;
}

//////////////////////////////////////////////////////////////////////////////
//                           Function Definitions                           //
//////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
*                     int vint_half_sum(vector<int> v)                       *
*                                                                            *
* Description : Provided a vector<int> v, half each of element v[i], and add *
*               the result to a running sum.  Return this sum when finished. *
*****************************************************************************/
int vint_half_sum(vector<int>& v)
{
    cout << endl << endl << "contents of v, the formal argument of " <<
         "vint_half_sum, upon entry to vint_half_sum " <<
         "(directly after initialization with the actual argument " <<
         "from main, vint) " << endl;
    vis::print(v);

    int sum = 0;
    for (int i = 0 ; i < v.size() ; i++) {
        // to illustrate the implications of providing a variable
        //   of type vector<int> as the formal parameter in this
        //   function,we're going to assign the result of v.at(i)/2
        //   back to v.at(i), then add v.at(i) to the sum.
        v.at(i) = v.at(i) / 2;
        sum += v.at(i);
    }

    // printing the contents of the formal argument v
    cout << endl << endl << "contents of v, the formal argument of " <<
         "vint_half_sum, prior to return from vint_half_sum" << endl;
    vis::print(v);
    return sum;
}