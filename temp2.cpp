#include <bits/stdc++.h>

using namespace std;
#define double long double
#define int long long
signed main() {
    std::ios::sync_with_stdio(false);

    cin.tie(0);

    int a,b,c,d;
    cin >> a >> b >> c >> d;
    vector<int> correct(a+1), penalty(a+1);
    vector<map<int, int>> v(a+1);
    vector<array<int,4>> x(c);
    for(int i = 0; i < c; i++) cin >> x[i][0] >> x[i][1] >> x[i][2] >> x[i][3];
    for(int i = c-1; i >= 0; i--) {
        if(x[i][2]>=300) continue;
        if(x[i][3]==1) {
            if(v[x[i][0]].count(x[i][1])) {
                
            }
        }
    }
}