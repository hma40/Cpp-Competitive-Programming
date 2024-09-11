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
    vt<int> a;
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
    cout << tc.n << endl << tc.a << endl;
}
TestCase randTC() {
    TestCase tc;
    tc.n=10;
    F0R(i, tc.n) {
        tc.a.add(rand_num(1,10));
    }
    return tc;
}
struct WrongSol {
    string make(int x) {
        int sofar = 0, combines=0;
        string s = "";
                R0F(i, 31) {
            // cout << i << " " << x << " " << sofar << endl;
            if(sofar) {
                int actual = (1<<i)-i;
                if(actual+sofar<=x) {
                    makePow2(i, s);
                    combines+=i+1;
                    s+="+";
                    sofar+=actual;
                    i++;
                }
            } else {
                if((1<<i)<=x) {
                    makePow2(i, s);
                    combines+=i;
                    sofar=(1<<i);
                    i++;
                }
            }
        }
        return s;
    }
    void makePow2(int pwr, string &s) {
    if(pwr==0) {
        s+="1";
        return;
    } 
    makePow2(pwr-1, s);
    s+="d+";
}
    string solve(TestCase tc) {
        int n;
        // cin >> n;
        n=tc.n;
        vt<int> a=tc.a;
        // F0R(i, n) cin >> a[i];
        vt<string> makeEach(n);
        int combines = 0;
        R0F(x, n) {
            // cout << x << " " << combines << endl;
            //2^i takes i combines
            a[x]+=combines;
            int sofar = 0;
            R0F(i, 31) {
                // cout << i << " " << x << " " << sofar << endl;
                if(sofar) {
                    int actual = (1<<i)-i;
                    if(actual+sofar<=a[x]) {
                        makePow2(i, makeEach[x]);
                        combines+=i+1;
                        makeEach[x]+="+";
                        sofar+=actual;
                        i++;
                    }
                } else {
                    if((1<<i)<=a[x]) {
                        makePow2(i, makeEach[x]);
                        combines+=i;
                        sofar=(1<<i);
                        i++;
                    }
                }
            }
        }
        string ret = "";
        // cout << makeEach << endl;
        // F0R(i, n) cout << makeEach[i];
        // cout << endl;
        trav(x, makeEach) ret+=x;
        return ret;
    }
};
bool works(TestCase tc, string s) {
    if(s.size()>100000) {
        cout << "TOO MANY CHARACTERS";
        return false;
    }
    vt<int> stack;
    trav(x, s) {
        if(x=='1') {
            stack.add(1);
        }
        if(x=='d') {
            stack.add(stack.back());
        }
        if(x=='+') {
            int xx = stack.back();
            stack.pop_back();
            stack.back()+=xx;
            F0R(i, stack.size()-1) stack[i]--;
        }
    }
    cout << stack << endl;
    return stack==tc.a;
}
signed main() {
    // while(true) {
    //     TestCase tc = randTC();
    //     WrongSol w;
    //     auto wa = w.solve(tc);
    //     if(works(tc,wa)) {
    //         cout << "PASSED" << endl;
    //         print_TC(tc);
    //         cout << wa << endl;
    //     } else {
    //         cout << "WRONG ANSWER" << endl;
    //         print_TC(tc);
    //         cout << wa << endl;
    //         break;
    //     }
    // }
    WrongSol w;
    FOR(i, 1, 1000000) {
        // cout << w.make(i) << endl;
        cout << i << " " << w.make(i).size() << endl;
    }
    return 0;
}
/*
x in y moves
can make x+1 in y+2 moves
can make 2x in y+2 moves

31
15
7
3
1

1 -> 2 -> 3 -> 6 -> 7 -> 14 -> 15 -> 30 -> 31
*/