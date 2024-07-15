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
    
    int n;
    int d;
    vt<pair<int,int>> sex;
};
void print_TC(TestCase tc) {
    cout << tc.n << " " << tc.d << tc.sex << endl;
}
TestCase randTC() {
    TestCase tc;
    tc.n=5;
    tc.d=rand()%10+tc.n;
    tc.sex.resize(tc.n);
    F0R(i, tc.n) {
        tc.sex[i].f=rand()%15+1;
        tc.sex[i].s=rand()%20+1;
    }
    return tc;
}
struct WrongSol {
    string solve(TestCase tc) {
        int n=tc.n,d=tc.d;
        vt<pair<int,int>> children = tc.sex;
        // F0R(i, n) cin >> children[i].f >> children[i].s;
        multiset<int> firstTime;
        F0R(i, n) {
            firstTime.insert(children[i].f);
        }
        int firstIndex = 0;
        // cout << firstTime << endl;
        priority_queue<vt<int>> pq;
        //priority, -time, index
        vt<vt<int>> wait(d+1);
        int time = 1;
        bool done = false;
        while(time<=d) {
            // cout << time << " " << wait << " " << firstTime << " " << firstIndex << endl;
            trav(x, wait[time]) {
                pq.push({children[x].f, -children[x].s, x});
            }
            if(pq.size()) {
                auto top = pq.top();
                // cout << top << endl;
                if(*(firstTime.rbegin())<top[0]) {
                    //serve this guy instead
                    pq.pop();
                    if(time-top[1]+1<=d) {
                        wait[time-top[1]+1].add(top[2]);
                    }
                    time++;
                    continue;
                } 
            }
            //serve firstTimer
            firstTime.erase(firstTime.find(children[firstIndex].f));
            if(time+children[firstIndex].s+1<=d) {
                wait[time+children[firstIndex].s+1].add(firstIndex);
            
            }
            firstIndex++;
            if(firstTime.size()==0) {
                done=true;
                break;
            }
            time++;
        }
        if(done) {
            return to_string(time);
        } else {
            // cout << -1 << endl;
            return "-1";
        }
    }
};
struct CorrectSol {
    const int MAX_N = 12;
    const int MAX_D = 30;

    struct Student {
        int k;
        int s;
        int tin = 0;

        bool operator<(const Student& other) const {
            if (k == other.k) {
                if (tin == other.tin) {
                    return s > other.s;
                }
                return tin > other.tin;
            }
            return k < other.k;
        }
    };

    int n, D, x;
    Student qu1[12];
    int sufMax[12];
    vector<Student> eat[30];

    int check() {
        int origPos = 0;
        priority_queue<Student> qu2;
        for (int i = 0; i < D && origPos < n; ++i) {
            if (qu2.empty() || qu2.top().k <= sufMax[origPos]) {
                ll nxtTime = ll(i) + ll(x) * ll(qu1[origPos].s);
                if (nxtTime < D) {
                    eat[nxtTime].push_back(qu1[origPos]);
                }

                ++origPos;
                if (origPos == n) {
                    for (int tm = 0; tm < D; ++tm) {
                        eat[tm].clear();
                    }

                    return i + 1;
                }
            } else {
                ll nxtTime = ll(i) + ll(x) * ll(qu2.top().s);
                if (nxtTime < D) {
                    eat[nxtTime].push_back(qu2.top());
                }
                qu2.pop();
            }

            for (const auto& student : eat[i]) {
                qu2.push({student.k, student.s, i});
            }
        }

        for (int i = 0; i < D; ++i) {
            eat[i].clear();
        }

        return -1;
    }

    string solve(TestCase tc) {
        n = tc.n;
        D = tc.d;
        // cin >> n >> D;
        x = 1;
        for (int i = 0; i < n; ++i) {
            // cin >> qu1[i].k >> qu1[i].s;
            qu1[i].k=tc.sex[i].f;
            qu1[i].s=tc.sex[i].s;
        }

        sufMax[n - 1] = qu1[n - 1].k;
        for (int i = n - 2; i >= 0; --i) {
            sufMax[i] = max(qu1[i].k, sufMax[i + 1]);
        }

        // cout << check() << '\n';
        return to_string(check());
    }
};
signed main() {
    while(true) {
        TestCase tc = randTC();
        // print_TC(tc);
        // return 0;
        WrongSol w;
        CorrectSol c;
        string wa = w.solve(tc);
        string cor = c.solve(tc);
        if(wa==cor) {
            cout << "PASSED" << endl;
        } else {
            cout << "WRONG ANSWER" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
            break;
        }
    }
    return 0;
}