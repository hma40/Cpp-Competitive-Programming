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
bool done(deque<int> v) {
    int s = v.size();
    F0R(i, s) {
        if(v.front()!=i+1) return false;
        v.pop_front();
    }
    return true;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;

    deque<int> d;
    F0R(i, n) {
        int kekw;
        cin >> kekw;
        d.push_back(kekw);
    }
    string ans = ""; 
    int iters = 0;
    ROF(lookFor, 1, n) {
        while(d.front()!=lookFor) {
            ans+="P";
            d.push_back(d.front());
            d.pop_front();
        }
        d.pop_front();
        while(d.front()!=lookFor+1) {
            ans+="SP";
            d.push_back(d.front());
            d.pop_front();
        }
        d.push_front(lookFor);
    }
    cout << ans << endl;
    return 0;
}
/*
5
1 2 5 3 4
*/