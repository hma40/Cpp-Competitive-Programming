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
    string solve(string s) {
        if(s.size()==1) {
            return "-1";
        }
        if(s.size()==2&&s[0]!=s[1]) {
            return "-1";
        }
        string ret = "";
        if(s[0]==s[1]) {
            ret+=s[0];
            ret+=s[0];
        } else if(s[1]!=s[2]) {
            ret+=s[0];
            ret+=s[1];
            ret+=s[2];
        } else {
            ret+=s[1];
            ret+=s[1];
        }
        return ret;
    }
};
bool works(string s) {
    set<string> seen;   
    F0R(start, s.size()) {
        FOR(end, start, s.size()) {
            string t = "";
            FOR(i, start, end+1) t+=s[i];
            seen.insert(t);
        }
    }
    cout << seen << endl;
    return seen.size()%2==0;
}

signed main() {
    WrongSol w;
    while(true) {
        string s = "";
        int sz = rand_num(1,5);
        F0R(i, sz) {
            char c = char('a'+rand_num(0,25));
            s+=c;
        }
        s="ababa";
        cout << "LINE 115 " << s << endl;
        auto ss = w.solve(s);
        if(ss=="-1") {
            bool found = false;
            F0R(i, s.size()) {
                FOR(j, i, s.size()) {
                    string tt = "";
                    FOR(k, i, j+1) tt+=s[k];
                    if(works(tt)) {
                        cout << "WRONG ANSWER LINE 132" << endl << s << endl << ss << endl << tt << endl;
                        cout << i << " " << j << endl;
                        return 0;

                    }
                }
            }
        } else {
            F0R(i, s.size()) {
                FOR(j, i, s.size()) {
                    string tt = "";
                    FOR(k, i, j+1) tt+=s[k];
                    if(works(tt)) {
                        cout << tt << endl;
                        return 0;

                    }
                }
            }
            if(!works(ss)) {
                cout << "WRONG ANSWER" << endl;
                cout << s << endl << ss << endl;
                return 0;
            }
        }
    }
    return 0;
}