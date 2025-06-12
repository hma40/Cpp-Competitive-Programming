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
        q.pop_front();
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
// #define endl "\n"
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
    int n;
    cin >> n;
    vt<int> a(n), b(n);
    F0R(i, n) cin >> a[i];
    F0R(i, n) cin >> b[i];
    set<pair<int,int>> s;
    vt<pair<int,int>> ops;
    auto solve_three = [&ops](int start, vt<int> a, vt<int> b)->void{
        // cout << a << endl << b << endl << "LINE 163" << endl;
        map<vt<int>,int> mp;
        int n = a.size();
        map<vt<int>,pair<int,int>> process;
        map<vt<int>,vt<int>> mp2;
        mp[a]=0;
        deque<vt<int>> dq;
        vt<pair<int,int>> ret;
        dq.add(a);
        while(dq.size()) {
            auto tp = dq.front();
            dq.pop_front();
            if(tp==b) break;
            F0R(i, n) {
                FOR(j, i+1, n) {
                    // cout << "LINE 178 " << i << " " << j << endl;
                    auto cpy = tp;
                    cpy[i]=tp[j]-1;
                    cpy[j]=tp[i]+1;
                    if(mp.count(cpy)) continue;
                    mp[cpy]=mp[tp]+1;
                    process[cpy]={i+start, j+start};
                    mp2[cpy]=tp;
                    dq.push_back(cpy);
                }
            }
        }
        // cout << "GOT TO LINE 190" << endl;
        if(mp.count(b)) {
            while(b!=a) {
                ret.add(process[b]);
                b=mp2[b];
            }
            reverse(begin(ret),end(ret));
        }
        // cout << "GOT TO LINE 198" << endl;
        trav(x, ret) ops.add(x);
        // cout << "GOT TO LINE 200" << endl;
    };
    auto operate = [&](int x, int y)->void{
        if(x==y) return;
        s.erase({a[x],x});
        s.erase({a[y],y});
        swap(a[x],a[y]);
        a[x]--;
        a[y]++;
        s.insert({a[x],x});
        s.insert({a[y],y});
        ops.add({x+1,y+1});
    };
    if(n==2) {
        if(a==b) {
            cout << "Yes" << endl << 0 << endl;
        } else if(b[0]==a[1]-1 && b[1]==a[0]+1) {
            cout << "Yes" << endl << 1 << endl << "1 2" << endl;
        } else {
            cout << "No" << endl;
        }
        return 0;
    } else {
        int sum_a = 0, sum_b = 0;
        F0R(i, n) {
            sum_a+=a[i];
            sum_b+=b[i];
        }
        if(sum_a!=sum_b) {
            cout << "No" << endl;
            return 0;
        }
        cout << "Yes" << endl;

        F0R(i, n) s.insert({a[i],i});
        for(int i = 0; i < n-3; i++) {
            auto lower = s.lower_bound({b[i],0});
            auto lower2 = lower;
            if(lower2!=s.begin()) --lower2;
            if(lower==s.end()) --lower;
            auto can1 = *lower, can2 = *lower2;
            if(abs(can1.f-b[i])<=abs(can2.f-b[i])) {
                //swap with can1
                operate(i, can1.s);
            } else {
                operate(i, can2.s);
            }
            while(a[i]>b[i]) {
                operate(i, i+2);
                operate(i+1,i+2);
                operate(i,i+1);
            }
            while(a[i]<b[i]) {
                operate(i,i+1);
                operate(i+1,i+2);
                operate(i,i+2);
            }
            s.erase({a[i],i});
        }
        solve_three(n-2, {a[n-3],a[n-2],a[n-1]}, {b[n-3],b[n-2],b[n-1]});
        assert(ops.size()<=31000);
        cout << ops.size() << endl;
        F0R(i, ops.size()) {
            cout << ops[i].f << " " << ops[i].s << endl;
        }
    }
    return 0;
}
/*

*/