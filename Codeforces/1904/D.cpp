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
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
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
#define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct RMQ {
    vt<vt<int>> sparse;
    vt<int> lg;
    vt<vt<int>> sparse2;
    RMQ(vt<int> v, int log) {
        lg.resize(v.size()+5);
        FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        sparse2.resize(v.size(), vt<int>(log, -1));
        sparse.resize(v.size(), vt<int>(log, -1));
        F0R(i, v.size()) {
            sparse2[i][0]=v[i];
            sparse[i][0]=v[i];
        }
        FOR(i, 1, log) {
            F0R(j, (int)v.size()-(1LL<<i)+1) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                // cout << i << " " << j << endl;
                sparse[j][i]=max(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
                sparse2[j][i]=min(sparse2[j][i-1], sparse2[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int getMax(int lo, int hi) {
        int log = lg[hi-lo+1];
        return max(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
    int getMin(int lo, int hi) {
        int log = lg[hi-lo+1];
        return min(sparse2[lo][log], sparse2[hi-(1<<log)+1][log]);
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n),b(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) cin >> b[i];
        RMQ ar(a,20);
        RMQ br(b,20);
        vt<set<int>> v(n+1);
        F0R(i, n) {
            v[a[i]].insert(i);
        }
        F0R(i, n+1) {
            v[i].insert(-1);
            v[i].insert(inf);
        }
        vt<int> bef(n),aft(n);
        F0R(i, n) {
            auto bruh = v[b[i]].lower_bound(i);
            aft[i]=*bruh;
            bruh--;
            bef[i]=*bruh;
        }
        bool good = true;
        priority_queue<pair<int,int>> pq;
        F0R(i, n) {
            pq.push({-b[i], i});
        }

        // cout << bef << aft << endl;
        while(pq.size()) {
            good=false;
            auto f = pq.top();
            pq.pop();
            if(aft[f.s]!=inf) {
                if(aft[f.s]==f.s) {
                    good=true;
                    continue;
                }
                if(ar.getMax(f.s, aft[f.s])==b[f.s]&&br.getMin(f.s+1, aft[f.s])>=b[f.s]) {
                    // cout << "LINE 202 " << f << aft[f.s] << endl;
                    good=true;
                }
            }
            if(bef[f.s]!=-1) {
                // cout << "LINE 221 " << f << bef[f.s] << " " << br.getMin(bef[f.s], f.s-1) << " " << ar.getMax(bef[f.s], f.s) << endl;
                if(ar.getMax(bef[f.s], f.s)==b[f.s]&&br.getMin(bef[f.s], f.s-1)>=b[f.s]) {
                    // cout << "LINE 208 " << f << bef[f.s] << endl;
                    good=true;
                }
            }
            if(!good) break;
        }
        if(good) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}