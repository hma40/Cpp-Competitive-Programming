#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    ll ans = 1;
    vector<ll> stalls(n);
    vector<ll> cows(n);
    for(int i = 0; i < n; i++) {
        cin >> cows[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> stalls[i];
    }
    sort(begin(stalls), end(stalls));
    sort(begin(cows), end(cows));
    int cowIndex = 0;
    for(int stallIndex = 0; stallIndex < n; stallIndex++) {
        while(cowIndex<n) {
            cowIndex++;
            if(cows[cowIndex]>stalls[stallIndex]) {
                break;
            }
        }
        cowIndex--;
        //cout << cowIndex << " " << stallIndex << endl;
        ans*=cowIndex-stallIndex+1;
    }
    cout << ans;
}