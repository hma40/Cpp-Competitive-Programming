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
int other(int x, int y) {
    if(min(x,y)==0&&max(x,y)==1) return 2;
    else if(min(x,y)==0) return 1;
    else if(min(x,y)==1) return 0;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vt<int> ops;
        vt<int> cnt(3);
        F0R(i, n) if(s[i]=='L') {
            cnt[0]++;
            s[i]='0';
        } else if(s[i]=='I') {
            cnt[1]++;
            s[i]='1';
        } else {
            cnt[2]++;
            s[i]='2';
        }
        if(cnt[0]==n || cnt[1]==n || cnt[2]==n) {
            cout << -1 << endl;
            continue;
        }
        auto ins = [&s](int x)->void{
            int o = other(s[x]-'0',s[x+1]-'0');
            string nw;
            F0R(i, x) nw+=s[i];
            nw+=char('0'+o);
            FOR(i, x, s.size()) nw+=s[i];
            swap(s,nw);
        };
        while(cnt[0]!=cnt[1] || cnt[1]!=cnt[2] || cnt[0]!=cnt[2]) {
            vt<int> cop = cnt;
            // cout << cnt << s << endl;
            sort(begin(cop),end(cop));
            bool done = false;
            FOR(i, 1, n) {
                if(s[i]!=s[i-1]) {
                    int o = other(s[i-1]-'0',s[i]-'0');
                    if(cnt[o]==cop[0]) {
                        ops.add(i);
                        done=true;
                        cnt[o]++;
                        ins(i);
                        break;
                    }
                }
            }
            if(done) continue;
            FOR(i, 1, n) {
                if(s[i]!=s[i-1]) {
                    int o = other(s[i-1]-'0',s[i]-'0');
                    if(cnt[o]==cop[1]) {
                        ops.add(i);
                        cnt[o]++;
                        ins(i);
                        break;
                    }
                }
            }
        }
        cout << ops.size() << endl;
        trav(x, ops) cout << x << endl;
    }
    return 0;
}