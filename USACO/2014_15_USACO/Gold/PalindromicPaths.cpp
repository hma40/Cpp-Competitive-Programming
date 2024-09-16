#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main() {
    // freopen("palpath.in" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    // if (!input) {
    //     std::cerr << "Error opening input file!" << std::endl;
    //     return 1;
    // }

    int t; // number of test cases
    cin >> t;
    cout << "LINE 15 " << t << endl;
    int query_count = 0;
    int testcase_with_135th_query = -1;
    std::vector<int> test_case_array;
    std::vector<std::pair<int, int>> test_case_queries;
    
    for (int testcase = 1; testcase <= t; ++testcase) {
        int n, q;
        cin >> n >> q;

        // Read the array values
        std::vector<int> array(n);
        for (int i = 0; i < n; ++i) {
            cin >> array[i];
        }

        // Read the queries
        std::vector<std::pair<int, int>> queries(q);
        for (int query = 0; query < q; ++query) {
            int i, x;
            cin >> i >> x;
            queries[query] = {i, x};
        }
        cout << n << " " << q << " " << testcase << endl;
        // Track the queries and find the testcase with the 135th query
        if (query_count + q >= 135) {
            testcase_with_135th_query = testcase;
            test_case_array = array;
            test_case_queries = queries;
            break;
        }

        query_count += q;
        cout << "LINE 48 " << query_count << " " << n << " " << q << endl;
    }

    // Output the result
    if (testcase_with_135th_query != -1) {
        std::cout << "Test case containing the 135th query: " << testcase_with_135th_query << std::endl;
        std::cout << "Array: ";
        for (int val : test_case_array) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        std::cout << "Queries:" << std::endl;
        for (const auto& query : test_case_queries) {
            std::cout << query.first << " " << query.second << std::endl;
        }
    } else {
        std::cout << "No test case contains the 135th query." << std::endl;
    }

    return 0;
}
