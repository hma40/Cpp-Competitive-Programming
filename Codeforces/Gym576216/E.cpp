#pragma GCC optimize("O3,unroll-loops")
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
const ll mod = 1000000007;
const ll inf = 8e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,x,y;
        cin >> n >> x >> y;
        vt<int> a(n),b(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) cin >> b[i];
        vt<vt<array<int,3>>> dp(n+1,vt<array<int,3>>(2*n+5,{-inf,-inf,-inf}));
        vt<vt<array<int,2>>> tooBig(n+1,vt<array<int,2>>(2*n+5,{-inf,-inf}));
        // vt<vt<vt<int>>> dp(n+1,vt<vt<int>>(2*n+10,array<int,3>)), tooBig(n+1, vt<vt<int>>(2*n+5, vt<int>(2, -inf)));
        if(x>y) swap(x,y);
        if(x+1==y) {
            dp[0][0][1]=0;
        } else if(x+2==y) {
            dp[0][0][2]=0;
        } else if(x==y) {
            dp[0][0][0]=0;
        } else {
            tooBig[0][0][0]=0;
        }
        F0R(i, n) {
            F0R(ad, 2*i+1) {
                // cout << i << " " << ad << " " << dp[i][ad][0] << " " << dp[i][ad][1] << " " << dp[i][ad][2] << " " << tooBig[i][ad][0] << " " << tooBig[i][ad][1] << endl;

                //transition from dp[i][ad][0]
                int xx = x+ad, yy;
                yy = xx;
                dp[i+1][ad][0]=max(dp[i+1][ad][0], dp[i][ad][0]+xx*yy*b[i]);
                xx+=a[i];
                if(xx>yy) swap(xx,yy);
                // cout << "LINE 181 " << xx << " " << yy << endl;
                if(xx+2==yy) {
                    dp[i+1][xx-x][2]=max(dp[i+1][xx-x][2], dp[i][ad][0]);
                } else if(xx+1==yy) {
                    dp[i+1][xx-x][1]=max(dp[i+1][xx-x][1], dp[i][ad][0]);
                } else {
                    dp[i+1][xx-x][0]=max(dp[i+1][xx-x][0], dp[i][ad][0]);
                }
                // cout << "LINE 193 " << dp[2][1][1] << endl;
                //transition from dp[i][ad][1]
                xx = x+ad;
                yy = xx+1;
                dp[i+1][ad][1]=max(dp[i+1][ad][1], dp[i][ad][1]+xx*yy*b[i]);
                xx+=a[i];
                if(xx>yy) swap(xx,yy);
                if(xx+2==yy) {
                    dp[i+1][xx-x][2]=max(dp[i+1][xx-x][2], dp[i][ad][1]);
                } else if(xx+1==yy) {
                    dp[i+1][xx-x][1]=max(dp[i+1][xx-x][1], dp[i][ad][1]);
                } else {
                    dp[i+1][xx-x][0]=max(dp[i+1][xx-x][0], dp[i][ad][1]);
                }
                if(a[i]==1) {
                    xx = x+ad;
                    yy = xx+1;
                    dp[i+1][ad][2]=max(dp[i+1][ad][2], dp[i][ad][1]);
                }
                // cout << "LINE 206 " << dp[2][1][1] << endl;
                //transition from dp[i][ad][2]
                xx = x+ad;
                yy = xx+2;
                dp[i+1][ad][2]=max(dp[i+1][ad][2], dp[i][ad][2]+xx*yy*b[i]);
                xx+=a[i];
                if(xx>yy) swap(xx,yy);
                if(xx+2==yy) {
                    dp[i+1][xx-x][2]=max(dp[i+1][xx-x][2], dp[i][ad][2]);
                } else if(xx+1==yy) {
                    dp[i+1][xx-x][1]=max(dp[i+1][xx-x][1], dp[i][ad][2]);
                } else {
                    dp[i+1][xx-x][0]=max(dp[i+1][xx-x][0], dp[i][ad][2]);
                }
                // cout << "LINE 219 " << dp[2][1][1] << endl;
                //transition from tooBig[i][ad][0]
                xx = x+ad;
                yy = y;
                if(xx+2<yy) {
                    tooBig[i+1][ad][0]=max(tooBig[i+1][ad][0], tooBig[i][ad][0]+xx*yy*b[i]);
                    if(a[i]==1) {
                        tooBig[i+1][ad][1]=max(tooBig[i+1][ad][1], tooBig[i][ad][0]);
                    }
                    xx+=a[i];
                    assert(xx<yy);
                    if(xx+2>=y) {
                        if(xx+2==yy) dp[i+1][xx-x][2]=max(dp[i+1][xx-x][2], tooBig[i][ad][0]);
                        else if(xx+1==yy) dp[i+1][xx-x][1]=max(dp[i+1][xx-x][1], tooBig[i][ad][0]);
                        else dp[i+1][xx-x][0]=max(dp[i+1][xx-x][0], tooBig[i][ad][0]);
                    } else {
                        tooBig[i+1][xx-x][0]=max(tooBig[i+1][xx-x][0], tooBig[i][ad][0]);
                    }
                } 
                xx = x+ad;
                yy = y+1;
                if(xx+2<yy) {
                    tooBig[i+1][ad][1]=max(tooBig[i+1][ad][1], tooBig[i][ad][1]+xx*yy*b[i]);
                    xx+=a[i];
                    if(xx+2>=y) {
                        if(xx+2==yy) dp[i+1][xx-x][2]=max(dp[i+1][xx-x][2], tooBig[i][ad][1]);
                        else if(xx+1==yy) dp[i+1][xx-x][1]=max(dp[i+1][xx-x][1], tooBig[i][ad][1]);
                        else dp[i+1][xx-x][0]=max(dp[i+1][xx-x][0], tooBig[i][ad][1]);
                    } else {
                        tooBig[i+1][xx-x][1]=max(tooBig[i+1][xx-x][1], tooBig[i][ad][1]);
                    }
                }
            }
        }
        int ans = 0;
        F0R(i, 2*n+5) {
            F0R(j, 3) ans=max(ans, dp[n][i][j]);
            F0R(j, 2) ans=max(ans, tooBig[n][i][j]);
        }
        cout << ans << endl;
    }
    return 0;
}
/*
1
6 6 1
1 2 2 2 2 1 
7 3 5 5 10 5 
*/