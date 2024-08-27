#include <bits/stdc++.h>
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }
    
    if (negative) result += '-';
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Overload << operator for __int128
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    return os << to_string(value);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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

template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
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
// #define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int m,q;
vt<int> v;
vt<int> nx;//next one of same number
vt<int> lastPoss;//at position i it is not possible to delete all instances of v[i] from i to lastPoss[i]+1
vt<int> activeRangeFirst;
int goodNums;
int l=0, r=-1;
vt<int> an;
int uniqs = 0, working = 0;
void query(vt<int> qw) {
    while(r<qw[1]) {
        r++;
        //add r
        if(activeRangeFirst[v[r]]==-1) {
            activeRangeFirst[v[r]]=r;
            uniqs++;
            working++;
        } else {
            if(lastPoss[activeRangeFirst[v[r]]]==r-1) {
                working--;
            }
        }
        // cout << "r MOVED RIGHT " << l << " " << r << " " << activeRangeFirst << " " << working << " " << uniqs << endl;
    }
    while(r>qw[1]) {
        if(activeRangeFirst[v[r]]==r) {
            activeRangeFirst[v[r]]=-1;
            uniqs--;
            working--;
        } else {
            if(lastPoss[activeRangeFirst[v[r]]]==r-1) {
                working++;
            }
        }
        r--;
        // cout << "r MOVED LEFT " << l << " " << r << " " << activeRangeFirst << " " << working << " " << uniqs << endl;
    }
    while(l<qw[2]) {
        //activeRangeFirst[v[l]]=l
        if(r>=nx[l]&&nx[l]!=-1) {
            activeRangeFirst[v[l]]=nx[l];
            if(lastPoss[l]<r&&lastPoss[nx[l]]>=r) {
                working++;
            }
        } else {
            activeRangeFirst[v[l]]=-1;
            uniqs--;
            working--;
        }
        l++;
        // cout << "l MOVED RIGHT " << l << " " << r << " " << activeRangeFirst << " " << working << " " << uniqs << endl;
    }
    while(l>qw[2]) {
        l--;
        if(activeRangeFirst[v[l]]==-1) {
            uniqs++;
            working++;
        } else {
            if(lastPoss[activeRangeFirst[v[l]]]>=r&&lastPoss[l]<r) {
                working--;
            }
        }
        activeRangeFirst[v[l]]=l;
        // cout << "l MOVED LEFT " << l << " " << r << " " << activeRangeFirst << " " << working << " " << uniqs << endl;
    }
    // cout << "LINE 187: " << qw << l << " " << r << " " << activeRangeFirst << " " << working << " " << uniqs << endl;
    if(working==0) {
        an[qw[3]]=1+uniqs;
    } else {
        an[qw[3]]=uniqs;
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    cin >> m;
    int MAXN = 1e5+2;
    // vt<int> v(m);
    v.resize(m);
    nx.resize(m);
    lastPoss.resize(m, inf);
    activeRangeFirst.resize(MAXN, -1);
    goodNums=0;
    F0R(i, m) cin >> v[i];
    vt<int> last(MAXN, -1);
    R0F(i, m) {
        if(last[v[i]]==-1) {
            nx[i]=-1;
            lastPoss[i]=inf;
        } else {
            nx[i]=last[v[i]];
            if(nx[nx[i]]==-1) {
                lastPoss[i]=inf;
            } else if(nx[nx[i]]-nx[i]==nx[i]-i) {
                lastPoss[i]=lastPoss[nx[i]];
            } else {
                lastPoss[i]=nx[nx[i]]-1;
            }
        }
        last[v[i]]=i;
    }
    const int sqr = 320;    
    cin >> q;
    vt<vt<int>> queries(q, vt<int>(4));

    an.assign(q,0);
    F0R(i, q) {
        cin >> queries[i][2] >> queries[i][1];
        queries[i][1]--;
        queries[i][2]--;
        queries[i][3]=i;
        queries[i][0]=queries[i][2]/sqr;
    }   
    sort(begin(queries),end(queries));
    // cout << queries << endl;
    trav(x, queries) {
        query(x);
    }
    // cout << an << endl;
    // cout << nx << lastPoss << endl;
    trav(x, an) cout << x << endl;
    return 0;
}
/*
in each query:
- is it possible to remove all of one number in 1 move?
Yes: #uniq
No: #uniq+1
*/