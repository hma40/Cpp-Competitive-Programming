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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n;
    string s,t;
    cin >> n >> s >> t;
    vt<int> sNum(n),tNum(n);
    F0R(i, n) sNum[i]=s[i]-'a';
    F0R(i, n) tNum[i]=t[i]-'a';
    /*
    type 1: x->x
    type 2: x->25-x
    type 3: x->13+x
    type 4: x->12-x
    x==25-x (mod 26) -> no sol
    x==13+x (mod 26) -> no sol
    x==12-x (mod 26) -> x==6 (uh oh)
    25-x==13+x (mod 26) x==6
    25-x==12-x -> no sol
    13+x==12-x -> no sol
    */
    vt<int> operations(n);//1-4, 5=6->19
    F0R(i, n) {
        if((sNum[i]==6&&tNum[i]==19)||(tNum[i]==19&&sNum[i]==6)) {
            operations[i]=5;
        } else {
            if(sNum[i]==tNum[i]) operations[i]=1;
            if(sNum[i]==25-tNum[i]) operations[i]=2;
            if(tNum[i]==(13+sNum[i])%26) operations[i]=3;
            if(tNum[i]==(38-sNum[i])%26) operations[i]=4;
        }
    }
    F0R(i, n) {
        if(operations[i]==0) {
            cout << -1 << endl;
            return 0;
        }
    }
    /*
    
    */
    vt<vt<int>> dp(n, vt<int>(5, inf));
    if(operations[0]==1) {
        dp[0][1]=0;
        dp[0][2]=2;
        dp[0][3]=2;
        dp[0][4]=4;
    } else if(operations[0]==2) {
        dp[0][2]=1;
        dp[0][4]=3;
    } else if(operations[0]==3) {
        dp[0][3]=1;
        dp[0][4]=3;
    } else if(operations[0]==4) {
        dp[0][4]=2;
    } else {
        dp[0][2]=dp[0][3]=1;
        dp[0][4]=3;
    }
    for(int i = 1; i < n; i++) {
        if(operations[i]==1) {
            dp[i][1]=min({dp[i-1][1], dp[i-1][2], dp[i-1][3], dp[i-1][4]});
            dp[i][2]=min({dp[i-1][1]+2, dp[i-1][2]+1, dp[i-1][3]+2, dp[i-1][4]+1});
            dp[i][3]=min({dp[i-1][1]+2, dp[i-1][2]+2, dp[i-1][3]+1, dp[i-1][4]+1});
            dp[i][4]=min({dp[i-1][1]+4, dp[i-1][2]+3, dp[i-1][3]+3, dp[i-1][4]+2});
        } else if(operations[i]==2) {
            dp[i][2]=min({dp[i-1][1]+1, dp[i-1][2], dp[i-1][3]+1, dp[i-1][4]});
            dp[i][4]=min({dp[i-1][1]+3, dp[i-1][2]+2, dp[i-1][3]+2, dp[i-1][4]+1});
        } else if(operations[i]==3) {
            dp[i][3]=min({dp[i-1][1]+1, dp[i-1][2]+1, dp[i-1][3], dp[i-1][4]});
            dp[i][4]=min({dp[i-1][1]+3, dp[i-1][2]+2, dp[i-1][3]+2, dp[i-1][4]+1});
        } else if(operations[i]==4) {
            dp[i][4]=min({dp[i-1][1]+2, dp[i-1][2]+1, dp[i-1][3]+1, dp[i-1][4]});
        } else {
            dp[i][2]=min({dp[i-1][1]+1, dp[i-1][2], dp[i-1][3]+1, dp[i-1][4]});
            dp[i][3]=min({dp[i-1][1]+1, dp[i-1][2]+1, dp[i-1][3], dp[i-1][4]});
            dp[i][4]=min({dp[i-1][1]+3, dp[i-1][2]+2, dp[i-1][3]+2, dp[i-1][4]+1});
        }
    }
    // cout << dp.back() << endl;
    cout << min({dp.back()[1], dp.back()[2], dp.back()[3], dp.back()[4]}) << endl;
    return 0;
}