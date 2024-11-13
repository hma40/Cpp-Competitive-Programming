#include <bits/stdc++.h>

using namespace std;
#define double long double
#define int long long
signed main() {
    std::ios::sync_with_stdio(false);

    cin.tie(0);

    int a,b,c,d;
    cin >> a >> b >> c >> d;
    int r = 1000000000  , gg = 1000000000;
    for(int sum = c; sum <= d; sum++) {
        for(int i = 0; i <= sum; i++) {
            int j = sum-i;
            if(j<i) continue;
            int num = 2*i*j;
            int deno = sum*(sum-1);
            if(num*b==deno*a) {
                cout << i << " " << j << endl;
                return 0;
            }
        }
    }
    cout << "NO SOLUTION" << endl;
}
/*
1/5 * 4/4 * 2 = 2/5
*/