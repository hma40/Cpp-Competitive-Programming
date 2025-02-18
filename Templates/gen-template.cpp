#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
const int mx = 2e5;
void generateArrays(int n, int m, vector<int>& current, vector<vector<int>>& result) {
    if (current.size() == n) {
        // Base case: array of size n is complete
        result.push_back(current);
        return;
    }

    for (int i = 1; i <= m; ++i) {
        current.push_back(i); // Add the current element
        generateArrays(n, m, current, result); // Recurse
        current.pop_back(); // Backtrack
    }
}

vector<vector<int>> generateAllArrays(int n, int m) {
    vector<vector<int>> result;
    vector<int> current;
    generateArrays(n, m, current, result);
    return result;
}
int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    
}