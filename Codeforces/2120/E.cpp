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
#define endl "\n"
#define enld "\n"
#define double long double
// const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
double solve(double mx, int k, vt<double> a) {
    double ans = 0, remv = 0;
    int n = a.size();
    F0R(i, n) {
        remv+=max((double)0, a[i]-mx);
    }
    ans=remv*k;
    double sum = 0;
    F0R(i, n) {
        sum+=a[i];
        if((sum+remv)/(i+1)>a[i+1]) {
            continue;
        } else {
            // cout << "LINE 164 " << i << " " << remv << " " << sum << endl;
            F0R(j, i+1) {
                a[j]=(sum+remv)/(i+1);
            }
            break;
        } 
    }
    F0R(i, n) {
        double here = min(mx, a[i]);
        ans+=here*(here+1)/2;
    }
    // cout << mx << " " << a << " " << ans << endl;
    return ans;
}
int solveint(int mx, int k, vt<int> a) {
    int ans = 0, remv = 0, sum=0;
    int n = a.size();
    F0R(i, n) sum+=a[i];
    if((sum+n-1)/n>mx) {
        return inf;
    }
    F0R(i, n) {
        remv+=max(0LL, a[i]-mx);
    }
    ans=remv*k;
    // double sum = 0;
    sum=0;
    if(remv) {
    F0R(i, n) {
        sum+=a[i];
        //if ceil>next, then its better to give to next as well
        if((sum+remv+i)/(i+1)>a[i+1]) {
            continue;
        } else {
            int div = (sum+remv)/(i+1);
            int mod = (sum+remv)%(i+1);
            if(mod==0) {
                F0R(j, i+1) {
                    a[j]=div;
                }
            } else {
                F0R(j, i+1) {
                    if(j<mod) a[j]=div+1;
                    else a[j]=div;
                }
            }
            break;
        } 
    }
}
    F0R(i, n) {
        int here = min(mx, a[i]);
        ans+=here*(here+1)/2;
    }
    // cout << mx << " " << a << " " << ans << endl;
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> a(n);
        int sum = 0;
        F0R(i, n) {
            cin >> a[i];
            sum+=a[i];
        }

        sort(begin(a),end(a));        
        vt<double> cpya;
        F0R(i, n) cpya.add(a[i]);
        double lo = (sum+0.0)/n, hi = a.back();
        // solveint(7,k,a);
        while(lo+5<hi) {
            double mid0 = (2*lo+hi)/3, mid1 = (lo+2*hi)/3;
            auto f0 = solve(mid0,k, cpya);
            auto f1 = solve(mid1,k, cpya);
            if(f0>f1) {
                lo=mid0;
            } else {
                hi=mid1;
            }
        }
        int ans = inf;
        for(int i = (int)(lo-1); i <= (int)(hi+1); i++) {
            ans=min(ans, solveint(i, k, a));
        }
        cout << ans << endl;
    }
    return 0;
}
/*
2 4 5 10 13, max=7
6 6 7 7 7
*/