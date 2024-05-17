#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Friend {
    int popularity, mooney, icecream;
};
int main() {
    //cout << "START" << endl;
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n,a,b;
    cin >> n >> a >> b;
    vector<Friend> friends(n);
    for(int i = 0; i < n; i++) {
        cin >> friends[i].popularity >> friends[i].mooney >> friends[i].icecream;
    }
    //cout << "START2" << endl;
    sort(friends.begin(), friends.end(), [](const Friend a, const Friend b) -> bool{
        return a.icecream < b.icecream;
    });
    map<pair<int, int>, int> maxPopularity;
    maxPopularity[make_pair(a,b)]=0;
    for(int i = 0; i < n; i++) {
        map<pair<int, int>, int> tempMaxPop;
        for(const auto &q : maxPopularity) {
            pair<int, int> p = q.first;
            if(p.second>friends[i].icecream * friends[i].mooney) {
                pair<int, int> temp = make_pair(p.first, p.second-friends[i].icecream*friends[i].mooney);
                tempMaxPop[temp]=max(tempMaxPop[temp], q.second+friends[i].popularity);
            } else {
                int costDecreased = p.second/friends[i].icecream;
                pair<int, int> temp = make_pair(p.first-friends[i].mooney+costDecreased, 0);
                if(temp.first>=0) {
                    tempMaxPop[temp]=max(tempMaxPop[temp], q.second+friends[i].popularity);
                }
            }
        }
        for(const auto &q: tempMaxPop) {
            maxPopularity[q.first]=max(maxPopularity[q.first], q.second);
        }
    }
    int ans = 0;
    for (const auto &p : maxPopularity) {
        ans=max(ans, p.second);
    } 
    cout << ans << endl;
    //cout << "END" << endl;
}