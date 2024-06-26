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
#define int long long
#define vt vector
#define endl "\n"
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
int solve(vt<int> &v, int pref) {
    int ans = 0;
    int uniqs = 0;
    int next = 1;
    vt<int> lastSeen(v.size(), inf);
    int lastSlice = v.size();
    R0F(i, pref) {
        if(lastSeen[v[i]]>=lastSlice) {
            lastSeen[v[i]]=i;
            uniqs++;
        }
        if(uniqs==next) {
            uniqs=0;
            ans++;
            next++;
            // here.clear();
            lastSlice=i;
        }
    }
    return ans;
}   
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        vt<int> all;
        F0R(i, n) cin >> v[i];
        F0R(i, n) all.add(v[i]);
        sort(begin(all),end(all));
        map<int,int> comp;
        int next = 0;
        trav(x, all) {
            if(!comp.count(x)) {
                comp[x]=next++;
            }
        }
        F0R(i, n) v[i]=comp[v[i]];
        // cout << v << endl;
        map<int, int> ans;
        int finalAns = solve(v, n);
        ans[0]=1;
        while((*ans.rbegin()).s<finalAns) {
            auto last = *ans.rbegin();
            int lo = last.f+1,hi = n-1;
            while(lo<hi) {
                int mid = (lo+hi)/2;
                int ans = solve(v, mid+1);
                if(ans>last.s) {
                    hi=mid;
                } else {
                    lo=mid+1;
                }
            }
            ans[hi]=last.s+1;
        }
        // ans[n]=inf;
        vt<int> an(n+1);
        trav(x, ans) {
            an[x.f]=x.s;
        }
        FOR(i, 1, n) {
            if(an[i]==0) an[i]=an[i-1];
        }
        cout << an[0];
        FOR(i, 1, n) cout << " " << an[i];
        cout << endl;
    }
    return 0;
}