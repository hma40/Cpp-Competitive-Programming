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

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rand_num(int l, int h) {
    return rnd()%(h-l+1)+l;
}
struct TestCase {
    int n;

};
void fill_rand(vt<int> &v, int lo, int hi) {
    for(auto &x: v) {
        x=rnd()%(hi-lo+1)+lo;
    }
}
void rand_tree(vt<vt<int>> &adj) {
    for(int i = 1; i < adj.size(); i++) {
        int par = rnd()%i;
        adj[par].add(i);
        adj[i].add(par);
    }
}
void print_TC(TestCase tc) {

}
TestCase randTC() {
    TestCase tc;

    return tc;
}
struct WrongSol {
    string solve(TestCase tc) {

    }
};
struct CorrectSol {
    string solve(TestCase tc) {

    }
};
signed main() {
    while(true) {
        TestCase tc = randTC();
        WrongSol w;
        CorrectSol c;
        auto wa = w.solve(tc);
        auto cor = c.solve(tc);
        if(wa==cor) {
            cout << "PASSED" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
        } else {
            cout << "WRONG ANSWER" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
            break;
        }
    }
    return 0;
}