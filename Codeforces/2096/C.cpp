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
        int n;cin >> n;
        vt<vt<int>> a(n, vt<int>(n));
        F0R(i, n) F0R(j, n) cin >> a[i][j];
        vt<bool> badRow(n-1), badCol(n-1);
        F0R(i, n-1) {
            F0R(j, n) if(a[i][j]==a[i+1][j]) badRow[i]=true;
            F0R(j, n) if(a[j][i]==a[j][i+1]) badCol[i]=true;
        }
        // assert(false);
        vt<bool> firstNotSecondRow(n-1, true), secondNotFirstRow(n-1, true), firstNotSecondCol(n-1, true), secondNotFirstCol(n-1, true);
        F0R(i, n-1) {
            F0R(j, n) {
                if(a[i][j]==a[i+1][j]-1) {
                    firstNotSecondRow[i]=false;
                } 
                if(a[i][j]==a[i+1][j]+1) {
                    secondNotFirstRow[i]=false;
                }
                if(a[j][i]==a[j][i+1]-1) {
                    firstNotSecondCol[i]=false;
                }
                if(a[j][i]==a[j][i+1]+1) {
                    secondNotFirstCol[i]=false;
                }
            }
        }
        // cout << badRow << badCol << endl;
        // cout << firstNotSecondRow << secondNotFirstRow << firstNotSecondCol << secondNotFirstCol << endl;
        vt<int> rCost(n), cCost(n);
        F0R(i, n) cin >> rCost[i];
        F0R(i, n) cin >> cCost[i];
        vt<array<int,2>> dpRow(n, {inf,inf}), dpCol(n, {inf,inf});
        dpRow[0][0]=0;
        dpRow[0][1]=rCost[0];
        FOR(i, 1, n) {
            //yes, no
            if(firstNotSecondRow[i-1]) {
                dpRow[i][0]=min(dpRow[i][0], dpRow[i-1][1]);
            }
            //no, yes
            if(secondNotFirstRow[i-1]) {
                dpRow[i][1]=min(dpRow[i][1], dpRow[i-1][0]+rCost[i]);
            }
            //yes yes
            if(!badRow[i-1]) {
                dpRow[i][1]=min(dpRow[i][1], dpRow[i-1][1]+rCost[i]);
            }
            //no no
            if(!badRow[i-1]) {
                dpRow[i][0]=min(dpRow[i][0], dpRow[i-1][0]);
            }
        }
        dpCol[0][0]=0;
        dpCol[0][1]=cCost[0];
        FOR(i, 1, n) {
            //yes, no
            if(firstNotSecondCol[i-1]) {
                dpCol[i][0]=min(dpCol[i][0], dpCol[i-1][1]);
            }
            //no, yes
            if(secondNotFirstCol[i-1]) {
                dpCol[i][1]=min(dpCol[i][1], dpCol[i-1][0]+cCost[i]);
            }
            //yes yes
            if(!badCol[i-1]) {
                dpCol[i][1]=min(dpCol[i][1], dpCol[i-1][1]+cCost[i]);
            }
            //no no
            if(!badCol[i-1]) {
                dpCol[i][0]=min(dpCol[i][0], dpCol[i-1][0]);
            }
        }
        // cout << dpRow << endl << dpCol << endl;
        if(min(dpRow.back()[0], dpRow.back()[1])+min(dpCol.back()[0], dpCol.back()[1])>=inf) {
            cout << -1 << endl;
        } else {
            cout << min(dpRow.back()[0], dpRow.back()[1])+min(dpCol.back()[0], dpCol.back()[1]) << endl;
        }
    }
    return 0;
}
/*
1 2 1 2
3 2 1 2
1 2 1 1
1 3 1 2

2 3 2 3
3 2 1 2
2 3 2 2
1 3 1 2
*/