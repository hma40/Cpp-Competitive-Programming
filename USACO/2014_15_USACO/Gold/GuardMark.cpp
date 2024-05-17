#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct cow {
    int height, weight, strength;
};
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);
    int n,h;
    cin >> n >> h;
    vector<cow> cows(n);
    for(int i = 0; i < n; i++) {
        cin >> cows[i].height >> cows[i].weight >> cows[i].strength;
    }
    vector<int> safety(1<<n, -1);
    safety[0]=1<<31-1;
    for(int i = 1; i <= 1<<n; i++) {
        for(int j = 0; j < n; j++) {
            if((i&(1<<j))!=0) {
                safety[i]=max(safety[i], min(safety[i^(1<<j)]-cows[j].weight, cows[j].strength));
            }
        }
    }
    int ans = -1;
    for(int i = 1; i <= 1<<n; i++) {
        int height = 0;
        for(int j = 0; j < n; j++) {
            if((i&(1<<j))!=0) {
                height+=cows[j].height;
            }
        }
        if(height>=h) ans=max(ans, safety[i]);
    }
    if(ans<0) {
        cout << "Mark is too tall" << endl;
    } else {
        cout << ans << endl; 
    }
}