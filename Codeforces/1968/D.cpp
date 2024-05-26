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
ll mod = 1000000007;
ll inf = 1e15;
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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,k,pb,ps;
        cin >> n >> k >> pb >> ps;
        vector<int> perm(n), score(n);
        F0R(i, n) cin >> perm[i];
        pb--;
        ps--;
        F0R(i, n) perm[i]--;
        F0R(i, n) cin >> score[i];
        vector<bool> visB(n), visS(n);
        int bScore = 0, sScore = 0;
        int maxB = 0, maxS = 0;
        int kb = k;
        while(kb) {
            if(visB[pb]) break;
            visB[pb]=true;
            maxB=max(maxB, bScore+kb*score[pb]);
            bScore+=score[pb];
            pb=perm[pb];
            kb--;
        }
        while(k) {
            if(visS[ps]) break;
            visS[ps]=true;
            maxS=max(maxS, sScore+k*score[ps]);
            sScore+=score[ps];
            ps=perm[ps];
            k--;
        }
        if(maxB>maxS) {
            cout << "Bodya" << endl;
        } else if(maxB==maxS) {
            cout << "Draw" << endl;
        } else {
            cout << "Sasha" << endl;
        }
    }
    return 0;
}