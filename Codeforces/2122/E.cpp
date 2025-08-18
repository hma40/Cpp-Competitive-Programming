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
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// int dp[500][250000];
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
        vt<vt<int>> a(2,vt<int>(n));
        F0R(i, n) cin >> a[0][i];
        F0R(i, n) cin >> a[1][i];
        int ans = 1;
        if(a[0][0]==-1) ans*=k;
        if(a[1][n-1]==-1) ans*=k;
        vt<int> pdp(k+1);
        pdp[k]=1;
        vt<int> thing(2*k+5);
        FOR(i, 1, k+1) {
            FOR(j, 1, k+1) {
                int diff = i-j+k+2;
                thing[diff]++;
            }
        }
        FOR(i, 1, n) {
            vt<int> ndp(k+1);
            if(a[0][i]==-1 && a[1][i-1]==-1) {
                F0R(x, 2*k+5) {
                    if(thing[x]==0) continue;
                    int diff = x-k-2;
                    if(diff<0) {
                        F0R(j, k+1) {
                            ndp[-diff]+=pdp[j]*thing[x];
                            ndp[-diff]%=mod;
                        }
                    } else {
                        F0R(j, k) {
                            int ndiff = j-diff;
                            if(ndiff<0) continue;
                            ndp[ndiff]+=pdp[j]*thing[x];
                            ndp[ndiff]%=mod;
                        }
                        ndp[k]+=pdp[k]*thing[x];
                        ndp[k]%=mod;
                    }
                }
            } else if(a[0][i]==-1) {
                FOR(x, 1, k+1) {
                    if(a[1][i-1]>x) {
                        F0R(j, k+1) {
                            ndp[a[1][i-1]-x]+=pdp[j];
                            ndp[a[1][i-1]-x]%=mod;
                        }
                    } else {
                        F0R(j, k) {
                            int ndiff = j-(x-a[1][i-1]);
                            if(ndiff<0) continue;
                            ndp[ndiff]+=pdp[j];
                            ndp[ndiff]%=mod;
                        }
                        ndp[k]+=pdp[k];
                        ndp[k]%=mod;
                    }
                }
            } else if(a[1][i-1]==-1) {
                FOR(x, 1, k+1) {
                    if(x>a[0][i]) {
                        F0R(j, k+1) {
                            ndp[x-a[0][i]]+=pdp[j];
                            ndp[x-a[0][i]]%=mod;
                        }
                    } else {
                        F0R(j, k) {
                            int ndiff = j-(a[0][i]-x);
                            if(ndiff<0) continue;
                            ndp[ndiff]+=pdp[j];
                            ndp[ndiff]%=mod;
                        }
                        ndp[k]+=pdp[k];
                        ndp[k]%=mod;
                    }
                }
            } else {
                if(a[1][i-1]>a[0][i]) {
                    F0R(j, k+1) {
                        ndp[a[1][i-1]-a[0][i]]+=pdp[j];
                        ndp[a[1][i-1]-a[0][i]]%=mod;
                    }
                } else {
                    F0R(j, k) {
                        int ndiff = j-(a[0][i]-a[1][i-1]);
                        if(ndiff<0) continue;
                        ndp[ndiff]+=pdp[j];
                        ndp[ndiff]%=mod;
                    }
                    ndp[k]+=pdp[k];
                    ndp[k]%=mod;
                }
            }
            ndp.swap(pdp);
        }
        int an = 0;
        F0R(i, k+1) {
            an+=pdp[i];
            an%=mod;
        }
        cout << an*ans%mod << enld;
    }
    return 0;
}
/*
dp[i][j] = ways to color up to (0,i) and (1,i-1) such that the smallest difference of bottom-top = j
*/