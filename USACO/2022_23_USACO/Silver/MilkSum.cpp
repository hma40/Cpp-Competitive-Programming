#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    //system("Color E4");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n;
    int arr[n], arr2[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        arr2[i] = arr[i];
    }
    sort(arr2, arr2+n);
    long long totalMilk = 0;
    int prev = -1;
    map<int, int> mp;
    for(int i = 0; i < n; i++) {
        if(arr2[i] != prev) {
            prev = arr2[i];
            mp[arr2[i]] = i;
        }
        totalMilk += arr2[i]*(long long)(i+1);
    }
    long long prefSum[n+1];
    prefSum[0] = 0;
    for(int i = 1; i <= n; i++) {
        prefSum[i] = prefSum[i-1] + arr2[i-1];
    }
    stringstream ans;
    cin >> q;
    while(q--) {
        int w, x, y, z;
        cin >> w >> x;
        w--;
        y = mp[arr[w]];
        int* p = lower_bound(arr2, arr2+n, x);
        if(p == arr2+n) {
            z = n;
        } else {
            z = p - arr2;
        }
        //cout << w << " " << x << " " << y << " " << z <<endl;
        long long temp = totalMilk;
        if(z == y) {
            temp -= (long long)(y+1)*arr[w] - (long long)(y+1)*x;
        } else if(z < y) {
            temp = temp - (long long)(y+1)*arr[w] + prefSum[y] - prefSum[z] + (long long)(z+1)*x;
        } else {
            temp = temp - (long long)(y+1)*arr[w] - prefSum[z] + prefSum[y+1] + (long long)z*x;
        }
        ans << temp << '\n';
    }
    cout << ans.str();
    return 0;
}