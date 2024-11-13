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
// #define endl "\n"
#define double long double
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
typedef __uint128_t L;
ll mod = 1000000007;
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
string line, line2;
FastMod fs(mod);
vt<int> mp1(1000001), mp2(1000001);
map<int, set<int>> h1, h2;
vt<int> pref, pref2;
vt<int> hsh(1000001);
int dfs(int beg, int end) {
    // cout << "DFS CALLED " << beg << " " << end << endl;
    string name = "";
    int bruh = -1;
    FOR(i, beg, end+1) {
        if(line[i]=='(') {
            bruh=i;
            break;
        } else {
            name+=line[i];
        }
    }
    int nm = stoi(name);
    // cout << "LINE 168 " << nm << " " << hsh[nm] << endl;
    mp1[nm]^=hsh[nm];
    bruh--;
    if(bruh<0) {
        // cout << nm << " " << mp1[nm] << endl;
        // cout << "RETURNING " << name << endl;
        return nm;
    }
    while(bruh!=end) {
        int pf = pref[bruh+1];
        int nxt = *(h1[pf].upper_bound(bruh+1));
        nxt--;
        mp1[nm]^=hsh[dfs(bruh+2, nxt-1)];
        bruh=nxt;
        // cout << beg << " " << end << " " << bruh << endl;
    }
    // cout << "LINE 183 " << nm << " " << mp1[nm] << endl;
    return nm;
}
int dfs2(int beg, int end) {
    // cout << "DFS CALLED " << beg << " " << end << endl;
    string name = "";
    int bruh = -1;
    FOR(i, beg, end+1) {
        if(line2[i]=='(') {
            bruh=i;
            break;
        } else {
            name+=line2[i];
        }
    }
    int nm = stoi(name);
    mp2[nm]^=hsh[nm];
    bruh--;
    if(bruh<0) {
        // cout << "RETURNING " << name << endl;
        return nm;
    }
    while(bruh!=end) {
        int pf = pref2[bruh+1];
        int nxt = *(h2[pf].upper_bound(bruh+1));
        nxt--;
        mp2[nm]^=hsh[dfs2(bruh+2, nxt-1)];
        bruh=nxt;
        // cout << beg << " " << end << " " << bruh << endl;
    }
    return nm;
}
signed main() {
    F0R(i, 1000001) {
        hsh[i]=rnd();
    }
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    getline(cin, line);
    getline(cin, line2);
    int nxt = 0;
    F0R(i, line.size()) {
        if(line[i]!=' ') {
            line[nxt++]=line[i];
        }
    }
    while(line.size()>nxt) line.pop_back();
    nxt=0;
    F0R(i, line2.size()) {
        if(line2[i]!=' ') {
            line2[nxt++]=line2[i];
        }
    }
    while(line2.size()>nxt) line2.pop_back();
    // vt<int> pref(line.size()+1), pref2(line2.size()+1);
    pref.resize(line.size()+1);
    pref2.resize(line2.size()+1);
    F0R(i, line.size()) {
        if(line[i]=='(') {
            pref[i+1]=pref[i]+1;
        } else if(line[i]==')'){
            pref[i+1]=pref[i]-1;
        } else {
            pref[i+1]=pref[i];
        }
    }
    F0R(i, line2.size()) {
        if(line2[i]=='(') {
            pref2[i+1]=pref2[i]+1;
        } else if(line2[i]==')'){
            pref2[i+1]=pref2[i]-1;
        } else {
            pref2[i+1]=pref2[i];
        }
    }
    // cout << line << pref << endl;
    F0R(i, pref.size()) {
        h1[pref[i]].insert(i);
    }
    F0R(i, pref2.size()) {
        h2[pref2[i]].insert(i);
    }
    dfs(0, line.size()-1);
    dfs2(0, line.size()-1);
    bool bad = false;
    F0R(i, 1000001) {
        if(mp1[i]!=mp2[i]) {
            // cout << i << " " << mp1[i] << " " << mp2[i] << endl;
            bad=true;
        
        }
    }
    if(bad) cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}