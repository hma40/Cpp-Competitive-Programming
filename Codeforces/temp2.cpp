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
struct TestCase {
    int n,m;
    vt<string> v;
};
void print_TC(TestCase tc) {
    cout << tc.n << " " << tc.m << " " << tc.v << endl;
}
TestCase randTC() {
    TestCase t;
    t.n=20;
    t.m=20;
    t.v.resize(t.n);
    F0R(i, t.n) {
        F0R(j, t.m) {
            t.v[i]+='0'+rand()%2;
        }
    }
    return t;
}
struct WrongSol {
    pair<int,string> solve(TestCase tc) {
        int n = tc.n, m = tc.m;
        vt<string> v = tc.v;
        vt<vt<int>> on(n, vt<int>(m, 1)), off(n, vt<int>(m, 1));
        F0R(i, n) {
            F0R(j, m) {
                F0R(kekw, 4) {
                    on[i][j]*=rand();
                    on[i][j]%=mod;
                    off[i][j]*=rand();
                    off[i][j]%=mod;
                }
            }
        }
        vt<int> noChange(n), change(n);
        F0R(i, n) {
            F0R(j, m) {
                if(v[i][j]=='0') {
                    noChange[i]^=off[i][j];
                    change[i]^=on[i][j];
                } else {
                    noChange[i]^=on[i][j];
                    change[i]^=off[i][j];
                }
            }
        }
        map<int,int> mp;
        F0R(i, m) {
            //fix 0,i to be the only 1 in this col
            int hash = 0;
            if(v[0][i]=='1') {
                hash^=noChange[0];
            } else {
                hash^=change[0];
            }
            FOR(j, 1, n) {
                if(v[j][i]=='0') {
                    hash^=noChange[j];
                } else {
                    hash^=change[j];
                }
            }
            mp[hash]++;
            FOR(j, 1, n) {
                hash^=noChange[j-1];
                hash^=change[j-1];
                hash^=noChange[j];
                hash^=change[j];
                mp[hash]++;
            }
        }
        // cout << mp << endl;
        int best = 0, hVal = 0;
        trav(x, mp) {
            if(x.s>best) {
                best=x.s;
                hVal=x.f;
            }
        }
        string ans = "";
        bool done = false;
        F0R(i, m) {
            //fix 0,i to be the only 1 in this col
            int hash = 0;
            if(v[0][i]=='1') {
                hash^=noChange[0];
            } else {
                hash^=change[0];
            }
            FOR(j, 1, n) {
                if(v[j][i]=='0') {
                    hash^=noChange[j];
                } else {
                    hash^=change[j];
                }
            }
            if(hash==hVal) {
                if(v[0][i]=='1') {
                    ans+='0';
                } else {
                    ans+='1';
                }
                FOR(j, 1, n) {
                    if(v[j][i]=='1') {
                        ans+='1';
                    } else {
                        ans+='0';
                    }
                }
                done=true;
            }
            if(done) break;
            FOR(j, 1, n) {
                hash^=noChange[j-1];
                hash^=change[j-1];
                hash^=noChange[j];
                hash^=change[j];
                if(hash==hVal) {
                    // cout << j << " " << i << endl;
                    F0R(k, j) {
                        if(v[k][i]=='0') {
                            ans+='0';
                        } else {
                            ans+='1';
                        }
                    }
                    if(v[j][i]=='1') {
                        ans+='0';
                    } else {
                        ans+='1';
                    }
                    FOR(k, j+1, n) {
                        if(v[k][i]=='0') {
                            ans+='0';
                        } else {
                            ans+='1';
                        }
                    }
                    done=true;
                    break;
                }
            }
            if(done) break;
        }
        return {best,ans};
    }
};
struct CorrectSol {
    pair<int,string> solve(TestCase tc) {
        int n = tc.n, m = tc.m;
        vt<vt<bool>> table(n,vt<bool>(m));
        for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c = tc.v[i][j];
            table[i][j] = c - '0';
        }
    }
    vector<long long> rands(n), rands2(n);
    for (int i = 0; i < n; ++i) {
        rands[i] = rand();
        rands2[i] = rand();
    }
    map<pair<long long, long long>, int> ans;
    int res = 0;
    pair<int, int> ind_ans = {0, 0};
    for (int j = 0; j < m; ++j) {
        long long summ = 0, summ2 = 0;
        for (int i = 0; i < n; ++i) {
            if (table[i][j]) {
                summ ^= rands[i];
                summ2 ^= rands2[i];
            }
        }
        for (int i = 0; i < n; ++i) {
            summ ^= rands[i];
            summ2 ^= rands2[i];
            ans[{summ, summ2}]++;
            if (res < ans[{summ, summ2}]) {
                res = ans[{summ, summ2}];
                ind_ans = {j, i};
            }
            summ ^= rands[i];
            summ2 ^= rands2[i];
        }
    }
    // cout << res << "\n";
    string inds(n, '0');
    for (int i = 0; i < n; ++i) {
        if (table[i][ind_ans.first]) {
            if (i != ind_ans.second) {
                inds[i] = '1';
            }
        } else if (ind_ans.second == i) {
            inds[i] = '1';
        }
    }
        return {res,inds};
    }       
};
bool check(pair<int,string> wa, pair<int,string> cor, TestCase t) {
    // return false;
    if(wa.f!=cor.f) return false;
    auto str = t.v;
    F0R(i, t.n) {
        if(wa.s[i]=='0') {

        } else {
            F0R(j, t.m) {
                if(str[i][j]=='0') str[i][j]='1';
                else str[i][j]='0';
            }
        }
    }
    // cout << "LINE 266 " << t.v << " " << wa.s << " " << str << endl;
    int count = 0;
    F0R(i, t.m) {
        int here = 0;
        F0R(j, t.n) {
            if(str[j][i]=='1') here++;
        }
        if(here==1) count++;
    }
    if(count==wa.f) return true;
    return false;
}
signed main() {
    while(true) {
        TestCase tc = randTC();
        WrongSol w;
        CorrectSol c;
        auto wa = w.solve(tc);
        auto cor = c.solve(tc);
        if(check(wa,cor,tc)) {
            cout << "PASSED" << endl;
            // print_TC(tc);
            // cout << wa << endl << cor << endl;
        } else {
            cout << "WRONG ANSWER" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
            break;
        }
    }
    return 0;
}