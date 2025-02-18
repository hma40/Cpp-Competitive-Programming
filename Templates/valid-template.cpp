#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the number of test cases
    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    // Process each test case
    for (int i = 1; i <= t; i++) {
        setTestCase(i);  // Set the current test case for error tracking
        
    }

    // Ensure we reach the end of the file
    inf.readEof();
}
