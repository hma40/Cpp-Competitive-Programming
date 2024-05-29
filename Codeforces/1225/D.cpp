#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <map>
using namespace std;
using pi = pair<int, int>;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    int nums[n];
    map<vector<pi>, int> factor_freq;
    vector<vector<pi>> opposites;
    vector<vector<pi>> factors;
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        int nn = nums[i];
        vector<pair<int, int>> bruh;
        vector<pair<int, int>> opposite;
        for(int j = 2; j * j <= nn; j++) {
            int times = 0;
            while(nn%j==0) {
                times++;
                nn/=j;
            }
            if(times!=0) {
                times%=k;
                if(times!=0) {
                    pair<int, int> temp;
                    temp.first=j;
                    temp.second=times;
                    bruh.push_back(temp);
                    int opp = k-times;
                    pair<int, int> temp2;
                    temp2.first=j;
                    temp2.second=opp;
                    opposite.push_back(temp2);
                }
            }
        }
        if(nn!=1) {  
            pair<int, int> temp;
            temp.first=nn;
            temp.second=1;
            bruh.push_back(temp);
            int opp = k - 1;
            pair<int, int> temp2;
            temp2.first=nn;
            temp2.second=opp;
            opposite.push_back(temp2);
        }
        factor_freq[bruh]++;
        opposites.push_back(opposite);
        factors.push_back(bruh);
    }
    /*
    for(int i = 0; i < n; i++) {
        for(pair<int, int> p: factors[i]) {
            cout << p.first << " " << p.second << endl;
        }
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        for(pair<int, int> p: opposites[i]) {
            cout << p.first << " " << p.second << endl;
        }
    }
    cout << endl;
    */
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        if(factors[i]==opposites[i]) {
            ans += factor_freq[opposites[i]]-1;
        } else {
            ans+=factor_freq[opposites[i]];
        }
    }
    cout << ans/2;
}