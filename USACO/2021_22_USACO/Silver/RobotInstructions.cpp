#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    pair<ll, ll> destination;
    cin >> destination.first >> destination.second;
    vector<pair<ll,ll>> instructions(n);
    for(int i = 0; i < n; i++) {
        cin >> instructions[i].first >> instructions[i].second;
    }
    vector<vector<ll>> firstHalf, secondHalf;
    vector<ll> temp{0,0,0};
    firstHalf.push_back(temp);
    secondHalf.push_back(temp);
    map<pair<ll, ll>, map<int, ll>> first, second;
    first[make_pair(0,0)][0]=second[make_pair(0,0)][0]=1;
    for(int i = 0; i < n/2; i++) {
        int sz = firstHalf.size();
        for(int j = 0; j < sz; j++) {
            vector<ll> tem = firstHalf[j];
            tem[0]+=instructions[i].first;
            tem[1]+=instructions[i].second;
            tem[2]++;
            first[make_pair(tem[0], tem[1])][tem[2]]++;
            firstHalf.push_back(tem);
        }
    }
    vector<ll> ans(n+1);
    for(int i = n/2; i < n; i++) {
        int sz = secondHalf.size();
        for(int j = 0; j < sz; j++) {
            vector<ll> tem = secondHalf[j];
            tem[0]+=instructions[i].first;
            tem[1]+=instructions[i].second;
            tem[2]++;
            second[make_pair(tem[0], tem[1])][tem[2]]++;
            secondHalf.push_back(tem);
        }
    }
    for(pair<pair<ll, ll>, map<int, ll>> p: first) {
        pair<ll, ll> need = make_pair(destination.first-p.first.first, destination.second-p.first.second);
        map<int, ll> m = second[need];
        for(pair<int, ll> pp: p.second) {
            for(pair<int, ll> mm: m) {
                ans[pp.first+mm.first]+=pp.second*mm.second;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
}