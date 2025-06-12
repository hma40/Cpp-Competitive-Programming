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

template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> std::ostream& operator<<(std::ostream& os, min_pq<T> q) {
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
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        pair<int,int> p = {-1,-1};
        map<int,int> mp;
        F0R(i, n) {
            if(mp.count(k-a[i])) {
                p={mp[k-a[i]], i};
                break;
            }
            mp[a[i]]=i;
        }
        if(p.f==-1) {
            if(is_sorted(begin(a),end(a))) {
                cout << 0 << endl;
                continue;
            } else {
                cout << -1 << endl;
                continue;
            }
        }
        if(a[0]+a.back()==k) {
            p = {0, n-1};
        }
        // cout << p << endl;
        vt<array<int,3>> ops;
        if(p.f!=0 && p.s!=n-1) {
            if(a[0]+a[p.f]<k) {
                int change = k-a[0]-a[p.f];
                ops.add({p.s+1, p.f+1, change});
                a[p.f]+=change;
                a[p.s]-=change;
                p = {0, p.f};
            } else {
                int change = -k+a[0]+a[p.f];
                ops.add({p.f+1, p.s+1, change});
                a[p.s]+=change;
                a[p.f]-=change;
                p = {0, p.f};
            }
        }
        if(p.f==0 && p.s!=n-1) {
            if(a[0]+a.back()<k) {
                //increase a[0]
                int change = k-a.back()-a[0];
                ops.add({p.s+1, 1, k-a.back()-a[0]});
                a[0]+=change;
                a[p.s]-=change;
            } else {
                //decrease a[0]
                int change = a.back()+a[0]-k;
                ops.add({1, p.s+1, change});
                a[0]-=change;
                a[p.s]+=change; 
            }
        } else if(p.s==n-1 && p.f!=0) {
            if(a[0]+a.back()<k) {
                //increase a.back()
                int change = k-a.back()-a[0];
                ops.add({p.f+1, p.s+1, change});
                a[p.s]+=change;
                a[p.f]-=change;
            } else {
                //decrease a[0]
                int change = a.back()+a[0]-k;
                ops.add({p.s+1, p.f+1, change});
                a[p.s]-=change;
                a[p.f]+=change; 
            }
        }
        // cout << "LINE 229 " << ops << endl;
        // cout << ops << a << endl;
        set<pair<int,int>> pq;
        FOR(i, 1, n-1) pq.insert({a[i],i});
        // int nxt = n-2;
        auto swap = [&a, &ops, &k, &n](int i, int j)->void{
            /*
            a c d b
            a+b-c c d c
            a+b-d d d c
            a+b-c d c c
            */
            if(a[0]+a[i]<k) {
                int change = k-a[0]-a[i];
                ops.add({n, 1, k-a[0]-a[i]});
                a[0]+=change;
                a.back()-=change;
            } else if(a[0]+a[i]>k) {
                int change = a[0]+a[i]-k;
                ops.add({1, n, change});
                a[0]-=change;
                a.back()+=change;
            }
            if(a[i]>a[j]) {
                int change = a[i]-a[j];
                ops.add({i+1, 1, change});
                a[i]-=change;
                a[0]+=change;
                ops.add({1, j+1, change});
                a[j]+=change;
                a[0]-=change;
            } else if(a[i]<a[j]) {
                int change = a[j]-a[i];
                ops.add({1, i+1, change});
                a[0]-=change;
                a[i]+=change;
                ops.add({j+1, 1, change});
                a[j]-=change;
                a[0]+=change;
            }

        };
        int pos = n-2;
        while(pq.size()) {
            auto tp = *pq.rbegin();
            pq.erase(tp);
            if(tp.s==pos) {
                pos--;
                continue;
            } else {
                pq.erase({a[pos], pos});
                swap(tp.s, pos);
                pq.insert({a[tp.s], tp.s});
                pos--;
            }
        }
        // cout << a << endl;
        if(a[0]!=0) {
            ops.add({1, n, a[0]});
        }
        cout << ops.size() << endl;
        trav(x, ops) cout << x[0] << " " << x[1] << " " << x[2] << endl;
    }

    return 0;
}
/*
4 3
1 3 1 0
1 2 1 1
*/