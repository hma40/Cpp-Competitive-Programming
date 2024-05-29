#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
ll mod = 1000000007;
struct Compare {
    bool operator()(pair<int, ll> a, pair<int, ll> b) {
        return a.second>b.second;
    }
};
int main() {
    int n,c;
    cin >> n >> c;
    vector<int> numbers(n);
    F0R(i, n) cin >> numbers[i];
    ll bestAns = 0;
    vector<int> matchingIndex;
    F0R(i, n) {
        if(numbers[i]==c) {
            matchingIndex.push_back(i);
            bestAns++;
        }
    }
    vector<int> includeLast(500001);
    vector<int> lastPosition(500001, -1);
    F0R(i, n) {
        if(numbers[i]!=c) {
            if(lastPosition[numbers[i]]==-1) {
                lastPosition[numbers[i]]=i;
                includeLast[numbers[i]]=1;
            } else {
                if(matchingIndex.size()) {
                    int lb, ub;
                    lb=lower_bound(begin(matchingIndex), end(matchingIndex), lastPosition[numbers[i]])-begin(matchingIndex);
                    ub=upper_bound(begin(matchingIndex), end(matchingIndex), i)-begin(matchingIndex);
                    includeLast[numbers[i]]=max(1, includeLast[numbers[i]]+1-ub+lb);
                    //cout << i << " " << lb << " " << ub << " " << includeLast[numbers[i]] << endl;
                } else {
                    includeLast[numbers[i]]++;
                }
                lastPosition[numbers[i]]=i;
            }
            bestAns=max(bestAns, includeLast[numbers[i]]+(ll)matchingIndex.size());
        }
    }
    cout << bestAns << endl;
    return 0;
}