
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
using ll = long long;
struct keys {
    int subset[6];
    keys() {
        for(int i = 0; i < 6; i++) {
            subset[i]=0;
        }
    }
};
bool operator< (const keys a, const keys b)
{
  for (int j=0; j<6; j++) {
    if (a.subset[j] < b.subset[j]) return true;
    if (a.subset[j] > b.subset[j]) return false;
  }
  return false;
}
int main() {    
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("cowpatibility.in", "r", stdin);
    freopen("cowpatibility.out", "w", stdout);
    ll n;
    cin >> n;
    map<keys, ll> mp;
    for(int i = 0; i < n; i++) {
        int temp[5];
        for(int j = 0; j < 5; j++) {
            cin >> temp[j];
        }
        sort(begin(temp), end(temp));
        for(int k = 1; k < 32; k++) {
            keys l;
            int count = 0;
            for(int j = 0; j < 5; j++) {
                if((k&(1<<j))!=0) {
                    count++;
                    l.subset[count]=temp[j];
                }
            }
            l.subset[0]=count;
            mp[l]++;
        }
    }
    ll ans = n * (n-1) / 2;
    for(auto a: mp) {
        if(a.first.subset[0]%2==1) {
            ans-=a.second * (a.second-1)/2;
        } else {
            ans+=a.second * (a.second-1)/2;
        }
    }
    cout << ans;
}