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
#define enld "\n"
#define double long double
const ll mod = 998244353;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int maxSubarraySum(vt<int> &v) {
    int minPref = 0;
    int sum = 0;
    int ans = 0;
    trav(x, v) {
        sum+=x;
        ans=max(ans, sum-minPref);
        minPref=min(minPref, sum);
    }
    return ans;
}
int maxSuffixSum(vt<int> &v) {
    int sum = 0;
    int ans = 0;
    R0F(i, v.size()) {
        sum+=v[i];
        ans=max(ans, sum);
    }
    return ans;
}
int maxPrefixSum(vt<int> &v) {
    int sum = 0;
    int ans = 0;
    F0R(i, v.size()) {
        sum+=v[i];
        ans=max(ans, sum);
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,k;
        string s;
        cin >> n >> k >> s;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        if(k<=0) {
            F0R(i, n) if(s[i]=='0') a[i]=k;
            int mx = -inf;
            F0R(i, n) mx = max(mx, a[i]);
            if(mx==k) {
                cout << "YES" << endl;
                F0R(i, n) cout << a[i] << " ";
                cout << endl;
            } else {
                cout << "NO" << endl;
            }
        } else {
            vt<vt<int>> parts;
            vt<pair<int,int>> pos;
            F0R(i, n) {
                if(s[i]=='1') {
                    if(i==0 || s[i-1]=='0') {
                        parts.add(vector<int>());
                        pos.add({i, i});
                    }
                    parts.back().add(a[i]);
                    pos.back().s=i;
                } 
            }
            if(parts.size()==0) {
                cout << "YES" << endl;
                cout << k << " ";
                FOR(i, 1, n) cout << -k << " ";
                cout << endl;
                continue;
            }
            // cout << parts << pos << endl;
            if(parts.size()==1) {
                if(pos[0].f==0 && pos[0].s==n-1) {
                    if(maxSubarraySum(a)==k) {
                        // assert(maxSubarraySum(a)==k);
                        cout << "YES" << endl;
                        trav(x, a) cout << x << " ";
                        cout << endl;
                    } else {
                        cout << "NO" << endl;
                    }
                    continue;
                } else if(pos[0].f==0) {
                    auto sm = max(maxSuffixSum(parts[0]),maxSubarraySum(parts[0]));
                    sm=max(sm, 0LL);
                    if(sm>k) {
                        cout << "NO" << endl;
                        continue;
                    }
                    int sum = maxSuffixSum(parts[0]);
                    // trav(x, parts[0]) sum+=x;
                    a.back()=k-sum;
                    // cout << a << endl;
                    // return 0;
                    // assert(maxSubarraySum(a)==k);
                    cout << "YES" << endl;
                    trav(x, a) cout << x << " ";
                    cout << endl;
                } else {
                    auto sm = max(maxPrefixSum(parts[0]),maxSubarraySum(parts[0]));
                    sm=max(sm, 0LL);
                    if(sm>k) {
                        cout << "NO" << endl;
                        continue;
                    }
                    int sum = maxPrefixSum(parts[0]);
                    a[0]=k-sum;
                    // cout << a << endl;
                    // return 0;
                    // assert(maxSubarraySum(a)==k);
                    cout << "YES" << endl;
                    trav(x, a) cout << x << " ";
                    cout << endl;
                }
            } else {
                bool ok = true;
                trav(x, parts) {
                    if(maxSubarraySum(x)>k) ok=false;
                }
                if(!ok) {
                    cout << "NO" << endl;
                    continue;
                }   
                int sum0 = maxSuffixSum(parts[0]), sum1 = maxPrefixSum(parts[1]);
                // cout << sum0 << " " << sum1 << endl;
                F0R(i, n) {
                    if(s[i]=='1') continue;
                    if(i==pos[0].s+1) {
                        a[i]=(k-sum0-sum1);
                    } else if(i>pos[0].s && i<pos[1].f) a[i]=0;
                    else a[i]=-1e18;
                }
                // assert(maxSubarraySum(a)==k);   
                cout << "YES" << endl;
                trav(x, a) cout << x << " ";
                cout << endl;
            }
        }
    }
    return 0;
}