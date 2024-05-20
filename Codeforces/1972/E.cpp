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
ll mod = 998244353;
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
int bexpo(int base, int exp) {
    int ans = 1;
    while(exp) {
        if(exp%2) {
            ans*=base;
            ans%=mod;
        }
        base*=base;
        base%=mod;
        exp/=2;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int MAXN = 2e5+5;
    vt<int> fact(MAXN), invFact(MAXN);
    fact[0]=invFact[0]=1;
    FOR(i, 1, MAXN) {
        // if(i%10000) cout << i << endl;
        fact[i]=fact[i-1]*i;
        invFact[i]=bexpo(fact[i], mod-2);
    }
    vt<vt<int>> dist(20);
    F0R(i, 20) {
        FOR(j, 1, 1<<i) {
            int temp = j;
            int times = 0;
            while(temp<(1<<i)) {
                temp+=temp&-temp;
                times++;
            }
            dist[i].add(times);
        }
    }
    // cout << dist << endl;
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> coef;
        int chooseTop = k-1, chooseBot = 0;
        coef.add(1);
        while((1<<coef.size())<=n) {
            // cout << coef << " " << chooseTop << " " << chooseBot << endl;
            int temp = coef.back();
            temp*=++chooseTop;
            temp%=mod;
            temp*=bexpo(++chooseBot, mod-2);
            temp%=mod;
            coef.add(temp);
        }
        vt<int> bit(n);
        F0R(i, n) cin >> bit[i];
        vt<int> orig(n);
        vt<vt<int>> layers(20);
        map<int, int> mp;
        F0R(i, 20) {
            mp[1<<i]=i;
        }
        F0R(i, n+1) {
            int b = i&-i;
            layers[mp[b]].add(i);
        }
        // cout << layers << " " << coef << endl;
        for(int layer = 0; layer < 20; layer++) {
            trav(x, layers[layer]) {
                if(x==0) continue;
                x--;
                F0R(y, (1<<layer)-1) {
                    // cout << layer << " " << x << " " << y << endl;
                    bit[x]-=orig[x-(1<<layer)+1+y]*coef[dist[layer][y]];
                    bit[x]%=mod;
                    bit[x]+=mod;
                    bit[x]%=mod;
                }
                orig[x]=bit[x];
            }
        }
        cout << orig[0];
        FOR(i, 1, n) cout << " " << orig[i];
        cout << endl;
    }
    return 0;
}
/*
1
8 1
1 2 1 4 1 2 1 8
*/
/*
0 0 0 0 0 0 0 1
0 0 0 0 0 0 1 2
0 0 0 0 0 1 0 0
0 0 0 0 1 2 2 3
0 0 0 1 0 0 0 0
0 0 1 2 0 0 0 0
0 1 0 0 0 0 0 0
1 3 3 6 3 6 6 10
*/
/*
0001
0010
0100
1000

0011
0100
1000


*/