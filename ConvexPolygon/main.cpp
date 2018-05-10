#include <iostream>
#include "..\cppunitlite\TestHarness.h"
#include "utCP.h"

using namespace std;

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);

    return 0;
}
