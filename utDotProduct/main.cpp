#include <iostream>
#include "..\cppunitlite\TestHarness.h"
#include <string>
#include "..\ProductDot.h"
#include "..\getVector.h"
#include "utVector.h"
#include "..\Vector.h"

using namespace std;

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);

    return 0;
}






TEST(product_dot, subtract){
     int a[]={1,2};
     int b[]={3,4};
     int c[]={2,2};
     int * const d = minus_vector(b,a,2,2);

     LONGS_EQUAL(c[0],d[0]);
     LONGS_EQUAL(c[1],d[1]);
     delete []d;
}

TEST(product_dot, subtract_exception){
     int a[]={0};
     int b[]={0,0};
     try {
         minus_vector(b,a,2,1);
         FAIL("subtract_exception not thrown");
     }
     catch (string s) {
        CHECK(s == "subtract_exception");
     }
}




