#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> blackMagic;
int lb(int x, vector<int> arr2) {
    int lo = 0;
    int hi = blackMagic.size();
    while(lo+1<hi) {
        int mid = lo+(hi-lo)/2;
        if(arr2[blackMagic[mid]]<arr2[x]) {
            lo=mid;
        } else {
            hi=mid;
        }
    }
    if(arr2[blackMagic[lo]]>arr2[x]) { 
        return lo;
    } else {
        return hi;
    }
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> arr1(n), arr2(n+1);
    for(int i = 0; i < n; i++) {
        cin >> arr1[i];
    }
    for(int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        arr2[temp]=i;
    }
    blackMagic.push_back(arr1[0]);
    for(int i = 1; i < n; i++) {
        int lbb = lb(arr1[i], arr2);
        if(lbb==blackMagic.size()) {
            blackMagic.push_back(arr1[i]);
        } else {
            blackMagic[lbb]=arr1[i];
        }
    }
    cout << blackMagic.size() << endl;
}