#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> prefMax(n), suffMin(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    prefMax[0]=a[0];
    for(int i = 1; i < n; i++) prefMax[i]=max(prefMax[i-1], a[i]);
    suffMin[n-1]=a[n-1];
    for(int i = n-2; i >= 0; i--) suffMin[i]=min(suffMin[i+1], a[i]);
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        if(prefMax[i]==a[i]&&suffMin[i]==a[i]) {
            ans.push_back(a[i]);
        }
    }
    cout << ans.size() << endl;
    for(int i = 0; i < min(100LL, (int)ans.size()); i++) {
        cout << " " << ans[i];
    }
    cout << endl;
}