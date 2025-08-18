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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n,m;
    cin >> n >> m;
    vt<int> ans(m);
    vt<array<int,3>> ivs(m);
    F0R(i, m) {
        cin >> ivs[i][0] >> ivs[i][1];
        ivs[i][2]=i;
    }
    //check for 1
    bool done = false;
    F0R(i, m) {
        if(ivs[i][0]==1 && ivs[i][1]==n) {
            ans[i]=1;
            done=true;
            break;
        }
    }
    if(done) {
        cout << 1 << endl;
        F0R(i, m) cout << ans[i] << " ";
        cout << endl;
        return 0;
    }
    //check for two that goes to (1,n)
    int onebeg = -1, nend = n+1;
    F0R(i, m) {
        if(ivs[i][0]==1) {
            onebeg=max(onebeg, ivs[i][1]);
        }
        if(ivs[i][1]==n) {
            nend=min(nend, ivs[i][0]);
        }
    }
    if(onebeg+1>=nend) {
        bool doneone = false, donen = false;
        // cout << 2 << endl;
        F0R(i, m) {
            if(ivs[i][0]==1 && ivs[i][1]==onebeg && !doneone) {
                doneone=true;
                ans[i]=1;
            }
            if(ivs[i][0]==nend && ivs[i][1]==n && !donen) {
                donen=true;
                ans[i]=1;
            }
        }
        cout << 2 << endl;
        F0R(i, m) cout << ans[i] << " ";
        cout << endl;
        return 0;
    }
    //check for two disjoint
    sort(begin(ivs),end(ivs));
    int mxend = inf;
    done=false;
    F0R(i, m) {
        if(mxend<ivs[i][0]) {
            done=true;
            ans[ivs[i][2]]=2;
            break;
        }
        mxend=min(mxend, ivs[i][1]);
    }
    if(done) {
        F0R(i, m) if(ivs[i][1]==mxend) {
            ans[ivs[i][2]]=2;
            break;
        }
        cout << 2 << endl;
        F0R(i, m) cout << ans[i] << " ";
        cout << endl;
        return 0;
    }
    //check for one in another
    mxend=-inf;
    F0R(i, m) {
        if(mxend>=ivs[i][1]) {
            done=true;
            ans[ivs[i][2]]=2;
            break;
        }
        mxend=max(mxend, ivs[i][1]);
    }
    if(done) {
        F0R(i, m) {
            if(ivs[i][1]==mxend) {
                ans[ivs[i][2]]=1;
                break;
            }
        }
        cout << 2 << endl;
        F0R(i, m) {
            cout << ans[i] << " ";
            // cout << endl;
        }   
        cout << endl;
        return 0;
    }
    if(m<=2) {
        cout << -1 << endl;
        return 0;
    } else {
        cout << 3 << endl;
        ans[ivs[0][2]]=1;
        ans[ivs[2][2]]=1;
        ans[ivs[1][2]]=2;
        F0R(i, m) cout << ans[i] << " ";
        cout << enld;
    }
    return 0;
}
/*
if two intervals are disjoint, you can pick 2 on both of them to win
if one interval is inside another, you can pick the smaller one as 1, and the larger one as 2

*/