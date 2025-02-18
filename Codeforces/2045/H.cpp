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
    string s;
    cin >> s;
    int n = s.size();
    /*
    cases: s[i...j]<s[j+1...j+i-1] - impossible (set to -1)
    otherwise always optimal to take shortest one possible (first one that is different)
    */
    vt<vt<int>> firstDiff(n, vt<int>(n));
    F0R(i, n-1) {
        if(s[i]==s[n-1]) {
            firstDiff[i][n-1]=-1;
        } else {
            firstDiff[i][n-1]=0;
        }
    }
    R0F(i, n-1) {
        F0R(j, i) {
            if(s[i]==s[j]) {
                if(firstDiff[j+1][i+1]==-1) firstDiff[j][i]=-1;
                else firstDiff[j+1][i+1]=firstDiff[j][i]+1;
            }
        }
    }
    vt<vt<int>> dp(n, vt<int>(n));//dp[i][j] = max parts for j+1...n if last one is i...j
    dp[n-1][n-1]=1;
    vt<int> suffMax(n, 1);
    suffMax[n-1]=1;
    F0R(i, n-1) {
        dp[i][n-1]=1;
    }
    R0F(j, n-1) {
        F0R(i, j+1) {
            int diff = firstDiff[i][j+1];
            if(diff==-1) {
                int leastEnd = j+1+(j-i)+1;
                if(leastEnd>=n) {
                    dp[i][j]=-1;
                    continue;
                }
                dp[i][j]=1+suffMax[leastEnd];
                suffMax[i]=max(suffMax[i], dp[i][j]);
                continue;
            }
            int idx1 = i+diff, idx2 = j+1+diff;
            if(idx1>=j+1) {
                dp[i][j]=-1;
                continue;
            }
            if(s[idx1]>s[idx2]) {
                dp[i][j]=-1;
                continue;
            }
            dp[i][j]=1+suffMax[j+1];
            suffMax[i]=max(suffMax[i], dp[i][j]);
            /*
            take dp[j+1][idx2] through dp[j+1][n-1]
            */
        }
    }
    // cout << dp << endl;
    int mx = 0;
    pair<int,int> move = {0,0};
    F0R(i, n) {
        if(dp[0][i]>mx) {
            mx=dp[0][i];
            move={0,i};
        }
    }
    cout << mx << endl;
    cout << s.substr(0,move.s+1) << endl;
    if(mx==1) return 0;
    while(true) {
        FOR(j, move.s+1, n) {
            if(dp[move.s+1][j]==mx-1) {
                mx--;
                move={move.s+1, j};
                break;
            }
        }
        cout << s.substr(move.f, move.s-move.f+1) << endl;
        // cout << move << mx << dp <<  endl;
        if(mx==1) break;

    }
    return 0;
}