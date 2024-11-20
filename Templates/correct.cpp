#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
    int n;
    std::cin >> n;

    // Initialize a vector with values from 1 to n
    std::vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
        permutation[i] = i + 1;
    }
    vector<int> a(n);
    for(int i = 0 ; i < n; i++) cin >> a[i];
    int ans = 0;
    // Print all permutations
    do {
        bool good = true;
        for(int i = 0; i < n; i++) {
            int count = 0;
            for(int j = 0; j <= i; j++) if(permutation[j]<=i+1) count++;
            if(count!=a[i]) good=false;
        }
        if(good) ans++;
        if(good) cout << permutation << endl;
    } while (std::next_permutation(permutation.begin(), permutation.end()));
    cout << ans << endl;
    }
    return 0;
}
