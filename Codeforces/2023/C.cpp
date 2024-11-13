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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
__int128_t mod = (1LL<<61)-1;
vt<__int128_t> pw;
int sd = 0;
struct Hash {
    vt<__int128_t> hsh;
    Hash(string s) {
        hsh.resize(s.size()+1);
        F0R(i, s.size()) {
            hsh[i+1]=hsh[i]*sd;
            hsh[i+1]+=s[i];
            hsh[i+1]%=mod;
        }
    }
    Hash(vt<int> s) {
        hsh.resize(s.size()+1);
        F0R(i, s.size()) {
            hsh[i+1]=hsh[i]*sd;
            hsh[i+1]+=s[i];
            hsh[i+1]%=mod;
        }
        // cout << hsh << endl;
    }
    int getHash(int left, int right) {
        __int128_t raw = hsh[right+1]-hsh[left]*pw[right-left+1];
        raw%=mod;
        raw+=mod;
        raw%=mod;
        return (ll)raw;
    }
};
void initialize() {
    sd = rnd()%mod;
    pw.add(1);
    F0R(i, 200050) {
        pw.add(pw.back()*sd%mod);
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    initialize();
    int t = 1;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> a(n),b(n);
        F0R(i, n) cin >> a[i];
        vt<vt<int>> aadj(n), badj(n);
        int m;
        cin >> m;
        F0R(i, m) {
            int x,y;
            cin >> x >> y;
            x--;
            y--;
            aadj[x].add(y);
        }
        F0R(i, n) cin >> b[i];
        cin >> m;
        F0R(i, m) {
            int x,y;
            cin >> x >> y;
            x--;
            y--;
            badj[x].add(y);
        }
        int c = 0, cc=0;
        F0R(i, n) if(a[i]) c++;
        F0R(i, n) if(b[i]) cc++;
        if(c+cc!=n) {
            cout << "NO" << endl;
            continue;
        }
        if(c==0||c==n) {
            cout << "YES" << endl;
            continue;
        }
        vt<int> color(n, -1), color2(n, -1);
        color[0]=0;
        stack<int> s;
        s.push(0);
        while(s.size()) {
            auto f = s.top();
            // cout << f << " " << color[f] << endl;
            s.pop();
            trav(x, aadj[f]) {
                if(color[x]==-1) {
                    color[x]=(color[f]+1)%k;
                    s.push(x);
                }
            }
        }
        color2[0]=0;
        s.push(0);
        while(s.size()) {
            auto f = s.top();
            s.pop();
            trav(x, badj[f]) {
                if(color2[x]==-1) {
                    color2[x]=(color2[f]+1)%k;
                    s.push(x);
                }
            }
        }
        // cout << color << color2 << endl;
        vt<int> giveNeed(k), recNeed(k), giveHave(k), recHave(k);
        F0R(i, n) {
            if(b[i]==1) {
                giveHave[color2[i]]++;
            } else {
                recHave[color2[i]]++;
            }
            if(a[i]==1) {
                recNeed[(color[i]+1)%k]++;

            } else {
                giveNeed[(color[i]+k-1)%k]++;
            }
        }
        F0R(i, k) {
            giveHave.add(giveHave[i]);
            recHave.add(recHave[i]);
        }
        Hash gnh(giveNeed), rnh(recNeed), ghh(giveHave), rhh(recHave);
        bool w = false;
        F0R(i, k+1) {
            if(gnh.getHash(0, k-1)==ghh.getHash(i, i+k-1)&&rnh.getHash(0, k-1)==rhh.getHash(i, i+k-1)) {
                w=true;
            }
        }
        if(w) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
/*
1
4 4
1 1 0 0 
4
1 2
2 3
3 4
4 1
0 1 1 0 
4
1 4
2 1
3 2
4 3

*/