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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        map<int, set<int>> invFreq;
        vt<int> freq(n);
        vt<int> a(n);
        F0R(i, n) {
            cin >> a[i];
            a[i]--;
            freq[a[i]]++;
        }
        F0R(i, n) {
            if(freq[i]!=0) invFreq[freq[i]].insert(i);
        }
        while(q--) {
            int i,x;
            cin >> i >> x;
            i--;
            x--;
            int bef = freq[a[i]];
            invFreq[bef].erase(a[i]);
            if(invFreq[bef].size()==0) invFreq.erase(bef);
            freq[a[i]]--;
            if(freq[a[i]]!=0) invFreq[freq[a[i]]].insert(a[i]);
            bef=freq[x];
            invFreq[bef].erase(x);
            if(invFreq[bef].size()==0) invFreq.erase(bef);
            a[i]=x;
            freq[x]++;
            invFreq[freq[x]].insert(x);
            int most = (*invFreq.rbegin()).f;
            auto l = invFreq.begin();
            auto r = invFreq.rbegin();
            // l++;
            int mn = inf, mx = -inf;
            int ans = 0;
            while((*l).f<=(*r).f) {
                while((*l).f+(*r).f>=most) {
                    mn=min(mn, *((*r).s.begin()));
                    mx = max(mx, *((*r).s).rbegin());
                    if((*r).f!=(*invFreq.begin()).f) {
                        ++r;
                    } else {
                        break;
                    }
                }
                if((*l).f+(*r).f<most) {
                    r--;
                }
                ans=max(ans, (*(*l).s.rbegin())-mn);
                ans=max(ans, mx-*((*l).s.begin()));
                l++;
                if(l==invFreq.end()) break;
            }
            cout << ans << endl;
        }
    }
    return 0;
}
/*
8 1 4 1 8 4 4 4
*/