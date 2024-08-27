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
#define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
vt<int> pref;
vt<int> a;
int n,k;
vt<vt<int>> dp;
vt<vt<int>> something;
bool poss(int tr) {
    F0R(i, n) {
        pref[i+1]=pref[i]+(a[i]>=tr);
    }
    F0R(i, dp[0].size()) {
        dp[0][i]=pref[i];
        if(dp.size()!=1) {
            something[0][i]=dp[0][i]-pref[i+k];
        }
    }
    //recurrence: dp[i][j]=dp[i-1][j]+constant-pref[something]
    //precalc dp[i-1][j]-pref[something]
    //what is something? 
    // cout << tr << dp[0] << something[0] << pref << endl;
    FOR(i, 1, dp.size()) {
        int mx = 0;
        dp[i][0]=pref[i*k]-pref[i*k];
        //dp[1][0]=0
        //dp[1][1]=max(dp[0][0]+pref[4]-pref[3], dp[0][1]+pref[4]-pref[4])
        mx=something[i-1][0];
        FOR(j, 1, dp[i].size()) { 
            mx=max(mx, something[i-1][j]);         
            dp[i][j]=pref[i*k+j]+mx;

        }
        if(i!=dp.size()-1) {
            F0R(j, dp[i].size()) {
                something[i][j]=dp[i][j]-pref[i*k+j+k];
            }
        }
    }
    // cout << tr << dp << endl;
    // cout << tr << " " << dp[1] << endl;
    return dp.back().back()*2>(dp[0].size()-1);
    // return false;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        // int n,k;
        cin >> n >> k;
        // vt<int> a(n);
        a.assign(n, 0);
        pref.assign(n+1, 0);
        if(n%k==0) {
            dp.assign((n+k-1)/k, vt<int>(k+1, 0));
        } else {
            dp.assign((n+k-1)/k, vt<int>(n%k+1, 0));
        }
        something.assign(dp.size(), vt<int>(dp[0].size()));
        //dp[i][j]: first i groups, j selected = max score
        // cout << dp << endl;
        F0R(i, n) cin >> a[i];
        int lo = 1, hi = 1e9+1;
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            if(poss(mid)) {
                lo=mid;
            } else {
                hi=mid;
            }
        }
        cout << lo << endl;
        // poss(3);
        // poss(4);
        // poss(5);
        // poss(6);
        // poss(7);
    }
    return 0;
}
/*
dp[i][j] = max(dp[i-1][j-x]+(how many in this group works from j-x to j))
dp[i][j]=dp[i-1][j]+pref[something]-pref[]
first i groups of k selected
j numbers selected already
*/