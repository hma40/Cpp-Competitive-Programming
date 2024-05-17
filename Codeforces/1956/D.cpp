#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
#define int long long
#define vt vector
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
vt<vt<int>> dp, split;
int steps = 0;
string ans = "";
vector<int> a;
int mex(int start, int end) {
    set<int> e;
    FOR(i, start, end+1) {
        e.insert(a[i]);
    }
    F0R(i, 20) {
        if(!e.count(i)) return i;
    }
    return 0;
}
void ascending(int start, int end, bool triv, int amount) {
    //cout << "LINE 59 " << start << " " << end << " " << triv << " " << amount << endl;
    if(triv) {
        ascending(end-amount+1, end, false, -1);
        if(start!=end&&a[start]!=0) {
            steps++;
            ans+=to_string(1+start)+" "+to_string(1+start)+"\n";
            a[start]=0;
        }
        steps++;
        ans+=to_string(1+start)+" "+to_string(end+1)+"\n";
        FOR(i, start, end+1) a[i]=amount;

        // cout << "Wrap-up: " << start << " " << end << " " << triv << " " << amount << a << endl;
        return;
    }
    if(start==end) {
        if(a[start]==0) {
            return;
        }
        ans+=to_string(start+1)+" "+to_string(end+1)+"\n";
        a[start]=0;
        steps++;
        return;
    }
    ascending(start, end, true, end-start);
    //cout << "MID: " << start << " " << end << " " << triv << " " << amount << a << endl;
    ascending(start, end-1, false, -1);
    //cout << "WRAP: " << start << " " << end << " " << triv << " " << amount << a << endl;
}
void printSteps(int start, int end) {
    if(split[start][end]==-1) {
        if(dp[start][end]==(end-start+1)*(end-start+1)) {
            ascending(start,end, true, end-start+1);
        } 
        return;
    }
    printSteps(start, split[start][end]);
    printSteps(split[start][end]+1, end);
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    a.resize(n);
    F0R(i, n) cin >> a[i];
    dp.resize(n, vt<int>(n));
    split.resize(n, vt<int>(n, -1));
    F0R(i, n) dp[i][i]=max(1LL, a[i]);
    FOR(diff, 1, n) {
        F0R(start, n-diff) {
            int end = start+diff;
            dp[start][end]=(diff+1)*(diff+1);
            split[start][end]=-1;
            FOR(mid, start, end) {
                if(dp[start][mid]+dp[mid+1][end]>dp[start][end]) {
                    split[start][end]=mid;
                    dp[start][end]=dp[start][mid]+dp[mid+1][end];
                }
            }
        }
    }
    printSteps(0, n-1);
    cout << dp[0].back() << " " << steps << endl << ans;

    return 0;
}